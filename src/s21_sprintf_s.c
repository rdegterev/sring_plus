#include "s21_string.h"

/**
 * Вставит строку `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_str(char *src, char *dest, specifier_options *opt) {
  s21_size_t result_len = 0;
  int trim_len = s21_strlen(src);
  if (opt->precision) trim_len = s21_min(s21_strlen(src), (opt->precision));
  s21_size_t space = opt->width - trim_len;
  if (opt->width > trim_len) {
    if (opt->flag.minus) {
      s21_strnput(&dest, src, trim_len, &result_len);
      result_len += s21_put_nchar(&dest, ' ', space);
    } else {
      result_len += s21_put_nchar(&dest, ' ', space);
      s21_strnput(&dest, src, trim_len, &result_len);
    }
  } else {
    s21_strnput(&dest, src, trim_len, &result_len);
  }
  return result_len;
}
