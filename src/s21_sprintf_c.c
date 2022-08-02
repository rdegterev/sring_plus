#include "s21_string.h"

/**
 * Вставит char-символ `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_char(char src, char *dest, specifier_options *opt) {
  s21_size_t result_len = 0;
  if (opt->width > 0) {
    if (opt->flag.minus) {
      s21_strnput(&dest, &src, 1, &result_len);
      result_len += s21_put_nchar(&dest, ' ', opt->width - 1);
    } else {
      result_len += s21_put_nchar(&dest, ' ', opt->width - 1);
      s21_strnput(&dest, &src, 1, &result_len);
    }
  } else {
    s21_strnput(&dest, &src, 1, &result_len);
  }
  return result_len;
}
