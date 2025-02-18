#pragma once

/**
 * \file cli/cli_types.h
 * \brief cli framework:  vocabulary types
 *
 */

#include "stdint.h"
#include "stdbool.h"

class UoutWriter;

/// \brief key value pair
typedef struct {
  const char *key;
  const char *val;
} clpar;

/// \brief describing a CLI parameter handler, so it can be found by the framework
struct parm_handler {
  const char *parm; ///< command name (first word of command line)
  int (*process_parmX)(clpar p[], int len, class UoutWriter &td); ///< handler for this command
  const char *help; ///< help text for this command
};

/// \brief describing an array of @ref parm_handler 
struct parm_handlers {
  const struct parm_handler *handlers; ///< array of handlers
  int count; ///< length of array
};

/// \brief buffer to read a command line into
struct cli_buf {
  char *buf; ///< byte buffer
  unsigned buf_size; ///< buffer byte size
  unsigned buf_idx; ///< position to append next character
  int quote_count; ///< helper to support quoted values
};

/// \brief describing an array of @ref clpar 
struct cli_parm {
  clpar *par; ///< array of @ref clpar 
  unsigned size; ///< length of array
};

/// \brief type of getchar function used in calls of @ref cli_get_commandline 
typedef int (*getc_funT)(void);

/// \brief status of get command line
enum cli_get_commline_retT {
  CMDL_DONE, ///< line complete
  CMDL_ERROR, ///< error occured
  CMDL_INCOMPLETE, ///< line is still incomplete
  CMDL_LINE_BUF_FULL ///< buffer full, call @ref cliBuf_enlarge 
};

/// \brief type of parameter handler function
typedef int (*process_parm_cb)(clpar parm[], int parm_len, class UoutWriter &td);


