/*
 * cmdline_process_cli.c
 *
 *  Created on: 18.03.2020
 *      Author: bertw
 */

#include <cli/cli.h>
#include <cli/cli_types.h>
#include "utils_misc/bcd.h"
#include "cli_private.h"
#include "uout/uo_types.h"
#include "uout/uo_callbacks.h"
#include "cli/cli_out.hh"
#include "cli/mutex.h"
#include "uout/uout_builder_json.hh"
#include "debug/log.h"
#include "jsmn/jsmn.h"
#include "jsmn/jsmn_iterate.hh"
#include <string.h>

#ifdef CONFIG_CLI_DEBUG
#define DEBUG
#define D(x) x
#define L(x) x
#else
#define D(x)
#define L(x) x
#endif
#define logtag "cli"

bool (*cli_hook_checkPassword)(clpar p[], int len, class UoutWriter &td);
bool (*cli_hook_process_json)(char *json);
bool (*cli_hook_process_json_obj)(class UoutWriter &td,Jsmn_String::Iterator &it);
bool (*cli_hook_process_txt)(char *txt);


/////////////////////////////////private/////////////////////////////////////////////////////////
static bool parse_and_process_jsmn(Jsmn_String::Iterator &it, class UoutWriter &td, process_parm_cb proc_parm) {

  // "json" object is allowed to have nested content
  if (it.keyIsEqual("json", JSMN_OBJECT)) {
    if (cli_hook_process_json_obj) {
      // pass iterator by value copy
      auto it_copy = it;
      cli_hook_process_json_obj(td, ++it_copy);
    }
    // skip the json object

    it.skip_key_and_value();
    return true;
  }

  // handle any objects here. The command names of CLI handlers are not know by this component
  // nested objects or arrays are not allowed
  if (it.keyIsEqual(nullptr, JSMN_OBJECT)) {
    int err = 0;
    auto count = it[1].size;
    const int par_len = 20;
    int par_idx = 0;
    clpar par[par_len] = { };
     (par[par_idx].key = it.getValueAsString()) || ++err;;
    par[par_idx++].val = "";

    for (it += 2; count > 0 && it; --count) {
      (par[par_idx].key = it++.getValueAsString()) || ++err;
      (par[par_idx++].val = it++.getValueAsString()) || ++err;
    }

    if (err) {
     db_loge(logtag, "%s: failed no nested objects allowed in cli commands", __func__);
    }
    if (auto res = proc_parm(par, par_idx, td); res < 0) {
      db_loge(logtag, "%s: handler for <%s> returned <%d>", __func__, par[0].key, res);
    }
    return true;
  }

  // eat up any non object tokens (e.g. from":"wapp")
  it.skip_key_and_value();
  return true;
}

static bool parse_and_process_json(char *json, class UoutWriter &td, process_parm_cb proc_parm) {
 // L(db_logi(logtag, "process_json: %s", json));

  auto jsmn = Jsmn_String(json, 128);//Jsmn<128, char *>(json);
  if (!jsmn)
    return false;
  auto it = jsmn.begin();

  int err = 0;
  auto count = it->size;
  for (++it; count > 0 && it; --count) {
     parse_and_process_jsmn(it, td, proc_parm);
  }
  return !err;
}

//////////////////////////////public//////////////////////////////////////////////////////

int cli_processParameters(clpar p[], int len, class UoutWriter &td) {
  assert(len > 0);

  if (!cli_parmHandler_find_cb)
    return -1;

  const char *parm = p[0].key;
  if (auto handler = cli_parmHandler_find_cb(parm)) {
    return handler->process_parmX(p, len, td);
  }

  return -1;
}

void cli_process_json(char *json, class UoutWriter &td, process_parm_cb proc_parm) {
  L(db_logi(logtag, "process_json: %s", json));

  if (cli_hook_process_json && cli_hook_process_json(json))
    return;

#ifdef CONFIG_CLI_JSON_ROOT_OBJECT
  if (td.sj().open_root_object("cli")) {
#endif
    parse_and_process_json(json, td, proc_parm);
#ifdef CONFIG_CLI_JSON_ROOT_OBJECT
    td.sj().close_root_object();
  }
#endif

  if (so_tgt_test(SO_TGT_CLI)) {
    td.sj().writeln_json();
  }
  if (so_tgt_test(SO_TGT_WS)) {
    td.sj().write_json();
  }
}

void cli_process_cmdline(char *line, class UoutWriter &td, process_parm_cb proc_parm) {
  L(db_logi(logtag, "process_cmdline: %s", line));

  if (cli_hook_process_txt && cli_hook_process_txt(line))
    return;

  clpar par[20] = { };
  struct cli_parm clp = { .par = par, .size = 20 };

  int n = cli_parseCommandline(line, &clp);
  if (n < 0) {
    cli_replyFailure(td);
  } else if (n > 0) {

    if (cli_hook_checkPassword && !cli_hook_checkPassword(clp.par, n, td))
      return;

    if (td.so().root_open("cli")) {
      proc_parm(clp.par, n, td);
      td.so().root_close();
#ifdef CONFIG_APP_USE_WS
      if (so_tgt_test(SO_TGT_WS)) {
        uoCb_publish_wsJson(td.sj().get_json());
      }
#endif
    }
  }
}
