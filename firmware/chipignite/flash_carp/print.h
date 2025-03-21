#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef PRINT_H_
#define PRINT_H_

#define NULL ((void*)0)

// macros
#define INT_TO_CHAR(i) ((i) + '0')
#define INT_TO_HEX(i) ((i) > 9 ? (i) - 10 + 'a' : (i) + '0')
#define IS_NEG(i, nb) ((i) & ((long)1 << ((nb) * 8 - 1)))

// print functions
void print_init();
int printk(const char* fmt, ...);
void print_format(const char** format_str, va_list args);
void print_char(char c);
void print_kdec(long num, int num_bytes, bool is_signed);
void print_khex(unsigned long num, int num_bytes, bool print_leading);

// random helper functions
long int_pow(long a, long b);

#endif // PRINT_H_
