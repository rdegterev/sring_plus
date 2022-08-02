
#include "s21_string.h"

/**
 * Вставит float число `src` в позицию `dest`, учитывая настройки из `opt`
 * Возвратит размер приращения
 */
s21_size_t s21_append_float(double src, char *dest, specifier_options *opt,
                            short trim_z) {
  s21_size_t result_len = 0;
  s21_size_t isPositive = src >= 0 || s21_isnan(src);  // nan always positive

  char buffer[FLEN] = {};
  s21_ftoa(src, (char *)buffer, opt);
  s21_size_t bare_digits = s21_strlen((char *)buffer);

  if (trim_z && !(opt->flag.sharp) && (NULL != s21_strchr(buffer, '.'))) {
    /* Когда есть решетка не отбрасываем нули несмотря на trim_z */

    s21_size_t len = bare_digits;
    short repeat = TRUE;
    while (len > 0 && repeat) {
      if (buffer[len - 1] == '.') {
        buffer[len - 1] = 0;
        len -= 1;
        repeat = FALSE;
      } else if (buffer[len - 1] == '0') {
        buffer[len - 1] = 0;
        len -= 1;
        opt->precision -= 1;
      } else {
        repeat = FALSE;
      }
    }
    bare_digits = len;
  }

  if (!s21_isnormal(src)) { /* special values: nan or inf */
    if (!isPositive && !opt->flag.minus) bare_digits++;
    s21_size_t more = s21_positive_diff(opt->width, bare_digits);
    result_len += s21_put_nchar(&dest, ' ', more * !opt->flag.minus);
    more -= s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
    if (!isPositive && !opt->flag.minus) bare_digits--;
    s21_strnput(&dest, (char *)buffer, bare_digits, &result_len);
    result_len += s21_put_nchar(&dest, ' ', more * opt->flag.minus);

  } else {
    short extra = (opt->width) - s21_max(bare_digits, opt->precision);
    if (extra > 0) {
      /* нужен сдвиг */
      if (opt->flag.minus) {
        /* по левому краю */
        extra -= s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
        s21_precission_correction(&dest, bare_digits, opt, &result_len);
        s21_strnput(&dest, (char *)buffer, bare_digits, &result_len);
        result_len += s21_put_nchar(&dest, ' ', extra);
      } else {
        /* по правому краю */
        if (opt->flag.zero) {
          extra -=
              s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
          result_len += s21_put_nchar(&dest, '0', extra);
          s21_strnput(&dest, (char *)buffer, bare_digits, &result_len);
        } else {
          /* правый край, дополнение лидирующими нулями не требуется */
          result_len += s21_put_nchar(&dest, ' ', extra - 1);
          if (!s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len)) {
            result_len += s21_put_nchar(&dest, ' ', 1);
          }
          s21_precission_correction(&dest, bare_digits, opt, &result_len);
          s21_strnput(&dest, (char *)buffer, bare_digits, &result_len);
        }
      }
    } else { /* сдвиги не требуются */
      s21_insert_sign(&dest, isPositive, &(opt->flag), &result_len);
      s21_precission_correction(&dest, bare_digits, opt, &result_len);
      s21_strnput(&dest, (char *)buffer, bare_digits, &result_len);
    }
  }

  return result_len;
}
