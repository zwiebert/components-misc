#pragma once
/**
 * \file cli/cli_out.hh
 * \brief Textual output for console CLI
 */

#include <stdint.h>

void cli_warning_optionUnknown(class UoutWriter &td, const char *key);
void reply_id_message(class UoutWriter &td, uint16_t id, const char *tag, const char *msg);
void reply_message(class UoutWriter &td, const char *tag, const char *msg);

bool cli_replyResult(class UoutWriter &td, bool success);
void cli_replySuccess(class UoutWriter &td);
int cli_replyFailure(class UoutWriter &td);

/// print command prompt
void cli_msg_ready(class UoutWriter &td);
