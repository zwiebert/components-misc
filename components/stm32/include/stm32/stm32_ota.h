/**
 * \file       stm32_ota.h
 * \brief      download stm32 firmware.bin and flash it to the STM32 via UART using the stm32 boot-loader
 * \author     bertw
 */

#pragma once

#include <stdbool.h>

#define STM32_FW_FILE_NAME "/spiffs/rv.bin"  ///<  file path to store firmware image by \ref stm32ota_doUpdate

/**
 * \brief    State of running or stopped over the air update task
 */
typedef enum {
  stm32ota_NONE, ///< no OTA task was started
  stm32ota_RUN,  ///< OTA task is currently running
  stm32ota_FAIL, ///< OTA task has failed and terminated
  stm32ota_DONE ///< OTA task has succeeded and terminated
} stm32ota_state_T;

#ifdef __cplusplus
  extern "C" {
#endif

/**
 * \brief  get current state of the over the air update process
 *
 * \return  \ref stm32ota_state_T "ota process state"
 */
stm32ota_state_T stm32ota_getState();

///
/**
 * \brief              update the STM32 firmware from internal file system
 *
 *                     This takes a long time, so it should be called in dedicated task/thread
 *
 * \param file_name    Path of the file holding the firmware.bin file for the STM32
 * \return             success
 */
bool stm32Ota_firmwareUpdate(const char *file_name);

/**
 * \brief              download (firmware) to internal file system  using HTTP
 *
 * \param url          URL of the file. https URLs are currently not supported.
 * \param file_name    PATH to store the downloaded file to
 * \return             success
 */
bool stm32Ota_firmwareDownload(const char *url, const char *file_name);

/**
 * \brief               Start a task which does the complete STM32 firmware update from given URL
 *
 *                      This still needs an internal file system to store the firmware.bin. The file path is in STM32_FW_FILE_NAME
 *
 * \param firmware_url  URL of the file. http only. https scheme is currently not supported.
 * \return              success
 */
bool stm32ota_doUpdate(const char *firmware_url);

#ifdef __cplusplus
  }
#endif
