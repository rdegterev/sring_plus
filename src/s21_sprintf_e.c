#include "s21_string.h"
/**
 * Научная нотация (мантисса/экспонента) с использованием символа e (вывод
 * чисел должен совпадать с точностью до e-6)
 * Возвратит размер приращения
 */
s21_size_t s21_append_science(double src, char *dest, specifier_options *opt,
                              short trim_z) {
  s21_size_t result_len = 0;
  s21_size_t isPositive = src >= 0 || s21_isnan(src);  // nan always positive

  src = s21_fabs(src);
  int rank = s21_science_rank(&src, opt);

  char buffer[FLEN] = {};
  s21_ftoa(src, (char *)buffer, opt);
  s21_size_t bare_digits = s21_strlen((char *)buffer);

  if (trim_z && !(opt->flag.sharp) && (NULL != s21_strchr(buffer, '.'))) {
    /* Когда есть решетка не отбрасываем нули несмотря на trim_z */

    s21_size_t len = bare_digits;
    short trim_repeat = TRUE;

    while (len > 0 && trim_repeat) {
      if (buffer[len - 1] == '0' || buffer[len - 1] == '.') {
        buffer[len - 1] = 0;
        len -= 1;
      } else {
        trim_repeat = FALSE;
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
    if ('e' == *(opt->finish) || 'g' == *(opt->finish)) {
      s21_strcat((char *)buffer, "e");
    } else {
      s21_strcat((char *)buffer, "E");
    }
    if (rank >= 0) {
      s21_strcat((char *)buffer, "+");
      char bare_digit[DIGIT_LEN] = {};
      s21_u_itoa(rank, (char *)bare_digit, 10, 0);
      if (rank < 10) {
        s21_strcat((char *)buffer, "0");
      }
      s21_strcat((char *)buffer, (const char *)bare_digit);  // rank
    } else {
      rank = -rank;
      s21_strcat((char *)buffer, "-");
      char bare_digit[DIGIT_LEN] = {};
      s21_u_itoa(rank, (char *)bare_digit, 10, 0);
      if (rank < 10) {
        s21_strcat((char *)buffer, "0");
      }
      s21_strcat((char *)buffer, (const char *)bare_digit);  // rank
    }
    bare_digits = s21_strlen((char *)buffer);
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

int s21_science_rank(double *src, specifier_options *opt) {
  int rank = 0;

  unsigned long ceil = *src;
  if (s21_isinf(1.0 / *src)) {
    *src = 0.0;
  } else if (0 == opt->precision && s21_isnormal(*src)) {
    while (0 == ceil) {
      rank--;
      *src = s21_fabs(*src);
      *src *= 10.0;
      ceil = *src;
    }
    *src = s21_round(*src);
    ceil = *src;

    while (10 <= ceil) {
      rank++;
      *src = s21_fabs(*src);
      *src /= 10.0;
      *src = s21_round(*src);
      ceil = *src;
    }
    // ================================
  } else if (s21_isnormal(*src)) {
    while (0 == ceil && !s21_isinf(*src * 10.0)) {
      rank--;
      *src = s21_fabs(*src);
      *src *= 10.0;
      ceil = *src;
    }
    while (10 <= ceil || *src > 10.0) {
      rank++;
      *src = s21_fabs(*src);
      *src /= 10.0;
      ceil = *src;
    }
  }
  return rank;
}
