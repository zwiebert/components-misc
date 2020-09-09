/*
 * http_server.c
 *
 *  Created on: 26.03.2019
 *      Author: bertw
 */
#include "app_config/proj_app_cfg.h"
#ifdef USE_HTTP
#include "net/http/server/http_server.h"
#include <string.h>
#include "cli/cli.h"
#include "cli/mutex.hh"
#include "debug/dbg.h"

void (*ws_print_json_cb)(const char *json);
void (*hts_register_uri_handlers_cb)(void *server_handle);

static bool isJson(const char *s, int s_len) {
  int i;
  for (i=0; i < s_len; ++i) {
    if (s[i] == ' ')
      continue;
    return s[i] == '{';
  }
  return false;
}

///////// public ///////////////////
void hts_query0(hts_query_t qtype, char *qstr) {
  if (isJson(qstr, strlen(qstr))) {
    { LockGuard lock(cli_mutex); 
      cli_process_json(qstr, SO_TGT_HTTP);
    }
  }
}
#include <misc/cstring_utils.hh>
void hts_query(hts_query_t qtype, const char *qstr, int qstr_len) {
  { LockGuard lock(cli_mutex); 
    if (isJson(qstr, qstr_len)) {
      if (auto buf = csu(qstr, qstr_len)) {
        cli_process_json(buf, SO_TGT_HTTP);
      }
    }
  }
}

void hts_setup(struct cfg_http *config) {
  hts_enable_http_server(config);
}

void ws_print_json(const char *json) {
  if (ws_print_json_cb)
    ws_print_json_cb(json);
}

#endif

