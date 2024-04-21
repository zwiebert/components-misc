/**
 * \file        stm32/stm32_uart_if.hh
 * \brief       interface for accessing STM32 for communication and firmware update
 * \author      bertw
 */

#pragma once

#include <stdint.h>

/**
 * \brief   abstract/interface class for accessing STM32 for communication and firmware update
 *
 */
class Stm32_Uart_if {

public:
/**
 * \brief write data to stm32 when stm32 runs firmware
 *
 * \param src        byte data to write
 * \param src_len    byte data length to write
 * \return           number of bytes written, or -1 for failure
 */
  virtual int stm32_write(const char *src, unsigned src_len) = 0;

/**
 * \brief read data from stm32 when stm32 runs firmware
 *
 * \param dst       byte buffer to read into
 * \param dst_size  size of buffer
 * \return          number of bytes read or -1 for failure
 */
  virtual int stm32_read(char *dst, unsigned dst_size) = 0;

/**
 * \brief read line from stm32
 *
 * \param dst       byte buffer to read into
 * \param dst_size  size of buffer
 * \param wait_ms   time to wait for data (block) before returning
 * \return          number of bytes read or -1 for failure
 */
  virtual int stm32_read_line(char *dst, unsigned dst_size, unsigned wait_ms) = 0;

/**
 * \brief           get bytee from STM32 (with optional blocking)
 *
 * \param block     if true, block until a byte can be read or internal timeout is reached
 * \return          character we got, or -1 for failure
 */
  virtual int stm32_getc(bool block) = 0;

/**
 * \brief write data to stm32 when stm32 runs boot-loader
 *
 * \param src        byte data to write
 * \param src_len    byte data length to write
 * \return           number of bytes written, or -1 for failure
 */
  virtual int stm32_write_bl(const unsigned char *src, unsigned src_len) = 0;
/**
 * \brief read data from stm32 when stm32 runs boot-loader
 *
 * \param dst       byte buffer to read into
 * \param dst_size  size of buffer
 * \return          number of bytes read or -1 for failure
 */
  virtual int stm32_read_bl(unsigned char *dst, unsigned dst_size) = 0;

/// \brief  Restart STM32 into bootloader
  virtual void stm32_runBootLoader() = 0;

/// \brief Restart STM32 into firmware
  virtual void stm32_runFirmware() = 0;

/// \brief Restart STM32
  virtual void stm32_reset() = 0;

/// \brief Check if the STM32 is currently running the firmware
  virtual bool stm32_isFirmwareRunning(void) = 0;

/**
 * \brief     Pause this task
 *
 * \param ms  time to pause in milli-seconds
 */
  virtual void task_delay(unsigned ms) = 0;
};

