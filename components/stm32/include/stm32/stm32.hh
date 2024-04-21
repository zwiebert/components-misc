/**
 * \file        stm32/stm32.hh
 * \brief       object pointer and all headers
 * \author      bertw
 */

#pragma once


#include <stm32/stm32.h>
#include <stm32/stm32_uart_if.hh>
#include <stm32/mutex.hh>

/**
 *  \brief pointer to object interface initialized by  \ref stm32_setup
 */
extern Stm32_Uart_if *stm32_uart;
