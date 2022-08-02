#include "s21_string.h"

/**
 * Вставит число `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_digit(long long num, char *dest, specifier_options *opt) {
  s21_size_t result_len = 0;

  char *bare_digit[DIGIT_LEN];
  s21_size_t digit_len = s21_itoa(num, (char *)bare_digit);
  s21_size_t isPositive = num >= 0;
  short extra = (opt->width) - s21_max(digit_len, opt->precision);

  if (extra > 0) {
    /* нужен сдвиг */
    if (opt->flag.minus) {
      /* по левому краю */
      extra -= s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
      s21_precission_correction(&dest, digit_len, opt, &result_len);
      s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      result_len += s21_put_nchar(&dest, ' ', extra);
    } else {
      /* по правому краю */
      if (opt->flag.zero && !opt->precision) {
        extra -= s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
        result_len += s21_put_nchar(&dest, '0', extra);
        s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      } else {
        /* в остальных случаях ширина дополняется пробелами */
        result_len += s21_put_nchar(&dest, ' ', extra - 1);
        if (!s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len))
          result_len += s21_put_nchar(&dest, ' ', 1);
        s21_precission_correction(&dest, digit_len, opt, &result_len);
        s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
      }
    }
    //
  } else { /* сдвиги не требуются */
    s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
    s21_precission_correction(&dest, digit_len, opt, &result_len);
    s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
  }

  return result_len;
}
