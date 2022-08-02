#include "s21_string.h"

#define MAX_PRECISION (16)
static const double rounders[MAX_PRECISION + 1] = {
    0.5,                  // 0
    0.05,                 // 1
    0.005,                // 2
    0.0005,               // 3
    0.00005,              // 4
    0.000005,             // 5
    0.0000005,            // 6
    0.00000005,           // 7
    0.000000005,          // 8
    0.0000000005,         // 9
    0.00000000005,        // 10
    0.000000000005,       // 11
    0.0000000000005,      // 12
    0.00000000000005,     // 13
    0.000000000000005,    // 14
    0.0000000000000005,   // 15
    0.00000000000000005,  // 16
};

/**
 * Превратит float в строку
 * Без знака
 * Предельня точность 16
 */
char *s21_ftoa(double f, char *buf, specifier_options *opt) {
  short f_is_normal = TRUE;

  if (s21_isnan(f)) {
    buf[0] = 'n';
    buf[1] = 'a';
    buf[2] = 'n';
    buf[3] = '\0';
    f_is_normal *= FALSE;
  }

  if (s21_isinf(f)) {
    buf[0] = 'i';
    buf[1] = 'n';
    buf[2] = 'f';
    buf[3] = '\0';
    f_is_normal *= FALSE;
  }

  if (f_is_normal) {
    char *buf_ptr = buf;

    long integer_part;

    f = s21_fabs(f);

    int precision = opt->precision;
    // корректное округление до MAX_PRECISION, дальше без гарантий
    if (precision >= 0 && precision <= MAX_PRECISION) f += rounders[precision];

    integer_part = f;   // целая часть
    f -= integer_part;  // десятичная часть

    buf_ptr += s21_itoa(integer_part, buf_ptr);

    if (precision || opt->flag.sharp) {
      *buf_ptr++ = '.';

      while (precision-- > 0) {
        // сдвигаем на разряд и читаем первый байт
        f *= 10.0;
        char letter = f;
        *buf_ptr++ = '0' + letter;
        f -= letter;
      }
    }

    *buf_ptr = 0;  // конец строки
  }
  return buf;
}
