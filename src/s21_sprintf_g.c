
#include "s21_string.h"

/**
 * Использует кратчайший из представлений форматов %e или %f
 * https://bit.ly/3FShpTv
 */
s21_size_t s21_append_g(double src, char *dest, specifier_options *opt) {
  s21_size_t result_len = 0;

  int P = opt->precision;
  P = P + !P;

  double src_copy = src;
  int x = s21_science_rank(&src_copy, opt);

  if (P > x && x >= -4) {
    opt->precision = P - (x + 1);
    result_len += s21_append_float(src, dest, opt, TRUE);
  } else {
    opt->precision = P - 1;
    result_len += s21_append_science(src, dest, opt, TRUE);
  }

  return result_len;
}
