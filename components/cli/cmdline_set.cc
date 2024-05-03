/*
 * cli_setcmdline.c
 *
 *  Created on: 16.03.2019
 *      Author: bertw
 */

#include "cli/cli.h"
#include "cli_private.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef USE_STDIO_GETCHAR
static int get_char() {
  unsigned char c;
  int n = read(0, &c, 1);
  if (n != 1)
    return -1;
  return c;
}
#endif

bool cliBuf_enlarge(struct cli_buf *buf) {
  unsigned new_size = buf->buf_size ? buf->buf_size + 32 : 64;
  void *p = realloc(buf->buf, new_size);
  if (!p)
    return false;

  buf->buf = static_cast<char *>(p);
  buf->buf_size = new_size;
  return true;
}

char* get_commandline() {
  static struct cli_buf buf;

  if (!buf.buf)
    if (!cliBuf_enlarge(&buf))
      return 0;
  for (;;) {
#ifdef USE_STDIO_GETCHAR
  clearerr(stdin);
  switch (cli_get_commandline(&buf, getchar))
#else
  switch (cli_get_commandline(&buf, get_char))
#endif
    {
    case CMDL_DONE:
      if (buf.buf[0] == '\0' || buf.buf[0] == '\r' || buf.buf[0] == '\n')
        return nullptr;
      return buf.buf;


    case CMDL_LINE_BUF_FULL:
      if (cliBuf_enlarge(&buf))
        continue;
      return nullptr;

    case CMDL_INCOMPLETE:
      return nullptr;

    case CMDL_ERROR:
      return nullptr;
    }

    return 0;
  }
  return 0;
}

