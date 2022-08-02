#include "s21_string.h"

/**
 * Вставит число `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_o_digit(unsigned long num, char *dest,
                              specifier_options *opt) {
  s21_size_t result_len = 0;
  char *bare_digit[DIGIT_LEN];

  // flag '0' is ignored when flag '-' is present
  if (opt->flag.minus) opt->flag.zero *= FALSE;

  s21_size_t digit_len = s21_u_itoa(num, (char *)bare_digit, 8, FALSE);
  s21_size_t prefix_len = opt->flag.sharp * (num != 0);
  s21_size_t digint_n_prefix = digit_len + prefix_len;

  s21_size_t p_zeroes = s21_positive_diff(opt->precision, digint_n_prefix);
  s21_size_t w_zeroes = (opt->flag.zero && !opt->precision)
                            ? s21_positive_diff(opt->width, digint_n_prefix)
                            : 0;
  s21_size_t spaces =
      (!w_zeroes) ? s21_positive_diff(opt->width, digint_n_prefix + p_zeroes)
                  : 0;

  if (opt->flag.minus) {
    /* по левому краю */
    s21_ins_pref(&dest, &result_len, prefix_len, FALSE);
    result_len += s21_put_nchar(&dest, '0', p_zeroes);
    s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
    result_len += s21_put_nchar(&dest, ' ', spaces);
  } else {
    /* по правому краю */
    result_len += s21_put_nchar(&dest, ' ', spaces);
    s21_ins_pref(&dest, &result_len, prefix_len, FALSE);
    result_len += s21_put_nchar(&dest, '0', p_zeroes);
    result_len += s21_put_nchar(&dest, '0', w_zeroes);
    s21_strnput(&dest, (char *)bare_digit, digit_len, &result_len);
  }

  return result_len;
}
