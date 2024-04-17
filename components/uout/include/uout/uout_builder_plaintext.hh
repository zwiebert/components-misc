#pragma once
/**
 * \file cli/cli_out.hh
 * \brief Textual output for console CLI
 */

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief  Print key value pairs as text lines with limited length
 */
class UoutBuilderPlaintext {
  void  cli_out_entry(const char *key, const char *val, int len);
  void cli_out_start_reply();
public:
  UoutBuilderPlaintext(class UoutWriter &td): myTd(td) {}
public:

  /**
   * \brief set the tag, which is later printed at start of each output line
   */
  void cli_out_set_x(const char *obj_tag);

  /**
   * \brief                prints out a key value pair. If line has become to long start a new one.
   * \param key,val        key value pair
   * \param len            (obsolete) used to provide the length of characters written outside of this function
   *                       so it can be added to internally stored line length (used to calculate when to start a new line)
   */
  void cli_out_x_reply_entry(const char *key, const char *val, int len = 0);
  /**
   * \brief         end the current printing. Writes line terminator and line feed.
   */
  void cli_out_close();

private:
  int myLength = 0;
  class UoutWriter &myTd;
  char Obj_tag[16] = "";
};

