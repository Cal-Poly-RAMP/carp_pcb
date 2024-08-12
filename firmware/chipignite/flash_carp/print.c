#include "print.h"
#include <stub.h>



void print_str(char* s);

__attribute__((format(printf, 1, 2))) int printk(const char* fmt, ...) {
    // initialize structures for variable number of arguments
    va_list args;
    va_start(args, fmt);

    const char* curr_char = fmt;
    while (*curr_char) {
        if (*curr_char == '%') {
            // format specifier
            print_format(&curr_char, args);

            // if curr_char == NULL print_format errored, exit
            if (!curr_char) return -1;
        } else {
            // normal character, just print the string
            print_char(*curr_char);
            curr_char++;
        }
    }

    va_end(args);

    return 0;
}

void print_format(const char** format_str, va_list args) {
    bool format_str_end = false; // have we finished with this format specifier
    int num_bytes = 4;           // length of value to print (char, short, etc)

    while (!format_str_end) {
        (*format_str)++; // increment the pointer

        switch (**format_str) {
        case '%':
            // print the percent literal
            print_char('%');
            format_str_end = true;
            break;

        case 'd':
            // print a signed decimal number
            print_kdec(va_arg(args, unsigned long), num_bytes, true);
            format_str_end = true;
            break;

        case 'u':
            // print an unsigned decimal number
            print_kdec(va_arg(args, unsigned long), num_bytes, false);
            format_str_end = true;
            break;

        case 'x':
            // print the number in hex
            print_khex(va_arg(args, unsigned long), num_bytes, false);
            format_str_end = true;
            break;

        case 'c':
            // print a character
            print_char(va_arg(args, int));
            format_str_end = true;
            break;

        case 'p':
            // print a pointer
            print_khex(va_arg(args, unsigned long), 8, true);
            format_str_end = true;
            break;

        case 'h':
            num_bytes = 1;
            break; // print an 8-bit value
        case 'l':
            num_bytes = 2;
            break; // print a 16-bit value
        case 'q':
            num_bytes = 8;
            break; // print a 64-bit value

        case 's':
            // print a string
            print_str(va_arg(args, char*));
            format_str_end = true;
            break;

        default:
            // unsupported, error and set the pointer to NULL
            print_str("Unsupported format specifier");
            print_char(**format_str);
            *format_str = NULL;
        }
    }
    (*format_str)++; // increment the pointer
}

void print_char(char c) {
    putchar(c);
}

void print_str(char* s) {
    for (char* c = s; *c != 0; c++) {
        print_char(*c);
    }
}

void print_kdec(long num, int num_bytes, bool is_signed) {
    print_dec(num);
    return;
    // // if it's signed, record that and print a negative sign if nessecary
    // if (is_signed && IS_NEG(num, num_bytes)) {
    //     num = -num;
    //     print_char('-');
    // }

    // // truncate the number if nessecary
    // long trunc_num = 0;
    // for (int i = 0; i < num_bytes; i++) { trunc_num |= num & (0xFF << i * 8); }

    // // record if we've started printing the character
    // bool print_start = false;
    // for (int i = 19; i >= 0; i--) {
    //     // get rid of all leading digits
    //     int curr_digit = trunc_num % int_pow(10, i + 1);

    //     // get rid of all the trailing digits
    //     ucurr_digit -= trunc_num % int_pow(10, i);
    //     curr_digit /= int_pow(10, i);

    //     // print the digit
    //     if (print_start || curr_digit) {
    //         print_char(INT_TO_CHAR(curr_digit));
    //         print_start = true;
    //     }
    // }

    // // print zero if nothing has been printed yet
    // if (!print_start) print_char('0');
}

void print_khex(unsigned long num, int num_bytes, bool print_leading) {
    print_hex(num, 8);
    return;
    // // if print_leading print all the leading zeros
    // bool print_start = print_leading;

    // // iterate through all the digits
    // for (int i = (num_bytes << 1) - 1; i >= 0; i--) {
    //     long bitmask = (long)0xF << (i<<2);
    //     int hex_digit = ((num & bitmask) >> 4) * i;

    //     // if we are printing then display the character
    //     if (print_start || hex_digit) {
    //         print_char(INT_TO_HEX(hex_digit));
    //         print_start = true;
    //     }
    // }

    // // print a 0 if nothing has been already printed
    // if (!print_start) print_char('0');
}

/************************************/
/*********Helper Functions***********/
/************************************/
long int_pow(long a, long b) {
    int result = 1;
    while (b) {
        result *= a;
        b--;
    }
    return result;
}
