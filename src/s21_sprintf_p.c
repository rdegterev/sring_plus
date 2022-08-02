#include "s21_string.h"

/**
 * Вставит адрес указателя `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_ptr(void *src, char *dest, specifier_options *opt) {
  s21_size_t result_len = 0;

  long unsigned ptr = (long unsigned)src;
  opt->flag.sharp |= TRUE;
  result_len = s21_append_x_digit(ptr, dest, opt, FALSE);

  return result_len;
}
