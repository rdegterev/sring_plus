#include "s21_string.h"

/**
 * Вставит число `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_u_digit(unsigned long num, char *dest,
                              specifier_options *opt) {
  s21_size_t result_len = 0;

  char *bare_digit[DIGIT_LEN];
  s21_size_t digit_len = s21_u_itoa(num, (char *)bare_digit, 10, 0);
  short extra = (opt->width) - s21_max(digit_len, opt->precision);

  if (extra > 0) {
    /* нужен сдвиг */
    if (opt->flag.minus) {
      /* по левому краю */
      s21_precission_correction(&dest, digit_len, opt, &result_len);
      s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      result_len += s21_put_nchar(&dest, ' ', extra);
    } else {
      /* по правому краю */
      if (opt->flag.zero && !opt->precision) {
        result_len += s21_put_nchar(&dest, '0', extra);
        s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      } else {
        /* в остальных случаях ширина дополняется пробелами */
        result_len += s21_put_nchar(&dest, ' ', extra);
        s21_precission_correction(&dest, digit_len, opt, &result_len);
        s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      }
    }
    //
  } else { /* сдвиги не требуются */
    s21_precission_correction(&dest, digit_len, opt, &result_len);
    s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
  }

  return result_len;
}
