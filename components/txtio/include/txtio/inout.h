#ifndef _inout_h
#define _inout_h

#include "stdbool.h"
#include "stdint.h"

enum verbosity {
  vrbNone, vrb1, vrb2, vrb3, vrb4, vrbDebug
};


struct cfg_txtio { enum verbosity verbose; };
extern struct cfg_txtio *txtio_config;
#define TXTIO_IS_VERBOSE(lvl) (txtio_config->verbose >= (lvl))

void txtio_setup(struct cfg_txtio *cfg_txtio);


extern char *itoa(int val, char *s, int radix);
extern char *ltoa(long val, char *s, int radix);

extern int (*io_putc_fun)(char c);
extern int (*io_getc_fun)(void);
extern int (*con_printf_fun)(const char *fmt, ...);
extern int (*io_puts_fun)(const char *s);

int io_putc(char c);
int io_getc(void);
int io_putlf(void);
int io_puts(const char *s);
int io_getline(char *buf, unsigned buf_size);
int io_printf(const char *fmt, ...);

void io_print_hex_8(uint8_t n, bool comma);
void io_print_hex_16(uint16_t n, bool comma);
void io_print_hex_32(uint32_t n, bool comma);
void io_print_hex(uint32_t n, bool prefix);

void io_print_dec_8(int8_t n, bool comma);
void io_print_dec_16(int16_t n, bool comma);
void io_print_dec_32(int32_t n, bool comma);

void io_print_float(float f, int n);

void io_putn(int n, int radix);
void io_putl(int32_t n, int radix);
void io_putd(int n);
void io_putld(int32_t n);
void io_putx8(uint8_t n);



void printBCD(uint8_t bcd);
void print_array_8(const uint8_t *src, int len);
void print_array_8_inv(const uint8_t *src, int len);

bool mcu_get_buttonUpPin(void);
bool mcu_get_buttonDownPin(void);
bool mcu_get_buttonPin(void);

typedef enum mcu_pin_state { PIN_DEFAULT=0, PIN_INPUT, PIN_INPUT_PULLUP, PIN_OUTPUT, PIN_ERROR, PIN_READ, PIN_CLEAR, PIN_SET, PIN_TOGGLE, PIN_INPUT_OUTPUT } mcu_pin_state;
const char* mcu_access_pin(int gpio_number, mcu_pin_state *result, mcu_pin_state state);
bool  is_gpio_number_usable(int gpio_number, bool cli);
void gpio_get_levels(unsigned long long gpio_mask, char *buf, int buf_size);

#ifdef TEST_HOST
#include <stdio.h>
#define io_printf printf
#define con_printf printf
#elif defined MCU_ESP8266
#include <osapi.h>
#define io_printf(args...)  do { char buf[120]; if (ets_snprintf(buf, sizeof buf, args) > 0) io_puts(buf); } while(0)
#define  con_printf (*con_printf_fun)
#else
#include <stdio.h>
#define io_printf(args...)  do { char buf[120]; if (snprintf(buf, sizeof buf, args) > 0) io_puts(buf); } while(0)
#define  con_printf (*con_printf_fun)
#endif



#define io_printf_v(v, fmt, args...)   do { if(TXTIO_IS_VERBOSE(v)) io_printf(fmt, args); } while(0)
#define con_printf_v(v, fmt, args...)   do { if(TXTIO_IS_VERBOSE(v)) con_printf(fmt, args); } while(0)



#endif



