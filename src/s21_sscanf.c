#include "s21_string.h"

/**
 * Считывает форматированный ввод из строки
 * @param str пользовательский ввод
 * @param format формат по которому пытаемся вести разбор
 */
int s21_sscanf(const char *str, const char *format, ...) {
  //-----------------------------------------------------//

  int was_scanned = 0;
  int should_repeat = 1;

  va_list args;
  va_start(args, format);

  char *s_cur = (char *)str;
  char *f_cur = (char *)format;
  specifier_options *opt = calloc(1, sizeof(specifier_options));

  while (*f_cur && should_repeat) {
    if ('%' == *f_cur) {
      s21_reset_options(opt);
      opt->start = f_cur;
      f_cur++;
      s21_read_s_options(f_cur, opt);

      if ('%' == *opt->finish) {
        f_cur = opt->finish;
        should_repeat = s21_eq_or_whitespaces(&s_cur, &f_cur);
        was_scanned -= (*str == '\0');
      } else {
        f_cur = opt->finish + 1;

        void *variable = (opt->width == -1) ? NULL : va_arg(args, void *);

        if (s21_scan_is_legal(opt)) {
          short scan_is_ok = FALSE;

          if ('d' == *(opt->finish)) {
            scan_is_ok = (s21_scan_d(&s_cur, opt, variable, 10) > 0);
          } else if ('i' == *(opt->finish)) {
            scan_is_ok = (s21_scan_d(&s_cur, opt, variable, 0) > 0);
          } else if ('o' == *(opt->finish)) {
            scan_is_ok = (s21_scan_u(&s_cur, opt, variable, 010) > 0);
          } else if ('x' == *(opt->finish) || 'X' == *(opt->finish)) {
            scan_is_ok = (s21_scan_u(&s_cur, opt, variable, 0x10) > 0);
          } else if ('n' == *(opt->finish)) {
            if (NULL != variable) *(int *)variable = s_cur - (char *)str;
            scan_is_ok = 1;
            was_scanned -= 1;
          } else if ('u' == *(opt->finish)) {
            scan_is_ok = (s21_scan_u(&s_cur, opt, variable, 10) > 0);
          } else if ('c' == *(opt->finish)) {
            if (*s_cur != '\0') {
              if (NULL != variable) *(char *)variable = *s_cur;
              s_cur += 1;
              scan_is_ok = 1;
            }
          } else if ('s' == *(opt->finish)) {
            scan_is_ok = (s21_scan_s(&s_cur, opt, variable) > 0);
            was_scanned -= (!scan_is_ok && !was_scanned && *s_cur == '\0');
          } else if (s21_strspn(opt->finish, FLOATSPEC)) {
            if (opt->len == 'L') {
              scan_is_ok = (s21_scan_long_double(&s_cur, opt, variable) > 0);
            } else if (opt->len == 'l') {
              scan_is_ok = (s21_scan_double(&s_cur, opt, variable) > 0);

            } else {
              scan_is_ok = (s21_scan_float(&s_cur, opt, variable) > 0);
            }
          } else if ('p' == *(opt->finish)) {
            opt->len = 'l';
            scan_is_ok = (s21_scan_u(&s_cur, opt, variable, 0x10) > 0);
          }
          should_repeat = scan_is_ok;
          was_scanned += (scan_is_ok && (NULL != variable)) - (*str == '\0');
        }
      }
      // ======================================================================
    } else {
      should_repeat = s21_eq_or_whitespaces(&s_cur, &f_cur);
    }
  }

  free(opt);
  va_end(args);
  if (was_scanned < 0) was_scanned = -1;  // corner case 1
  if (*format == '\0') was_scanned = 0;   // corner case 2
  return was_scanned;
}

short s21_eq_or_whitespaces(char **s_cur, char **f_cur) {
  short is_ok = TRUE;

  if (s21_is_white_space(*f_cur)) {
    while (s21_is_white_space(*s_cur)) (*s_cur) += 1;
    (*f_cur) += 1;
  } else if (**s_cur == **f_cur) {
    (*s_cur) += 1;
    (*f_cur) += 1;
  } else {
    is_ok = FALSE;
  }

  return is_ok;
}

short s21_scan_is_legal(specifier_options *opt) {
  short success = TRUE;

  short no_flags =
      !(opt->flag.minus + opt->flag.plus + opt->flag.sharp + opt->flag.space);
  success *= no_flags;
  short precision_is_default = (opt->precision == -1);
  success *= precision_is_default;

  return success;
}

short s21_scan_d(char **cur, specifier_options *opt, void *variable,
                 short base) {
  char *start_ptr = *cur;
  long parsed_digit = strtol(*cur, cur, base);
  short digit_len = *cur - start_ptr;

  if (digit_len) {
    int lim = opt->width;
    if (lim > 0 && digit_len > lim) {
      char buffer[DIGIT_LEN] = {};
      while (s21_is_white_space(start_ptr)) start_ptr += 1;
      s21_strncpy(buffer, start_ptr, lim);
      parsed_digit = strtol(buffer, NULL, base);
      *cur = start_ptr + lim;
    }

    if (NULL != variable) {
      if (opt->len == 'h') {
        *(short *)variable = parsed_digit;
      } else if (opt->len == 'l') {
        *(long *)variable = parsed_digit;
      } else {
        *(int *)variable = parsed_digit;
      }
    }
  }
  return digit_len;
}

short s21_scan_u(char **cur, specifier_options *opt, void *variable,
                 short base) {
  char *start_ptr = *cur;
  long parsed_digit = strtol(*cur, cur, base);
  short digit_len = *cur - start_ptr;

  if (digit_len) {
    int lim = opt->width;
    if (lim > 0 && digit_len > lim) {
      char buffer[DIGIT_LEN] = {};
      while (s21_is_white_space(start_ptr)) start_ptr += 1;
      s21_strncpy(buffer, start_ptr, lim);
      parsed_digit = strtol(buffer, NULL, base);
      *cur = start_ptr + lim;
    }

    if (NULL != variable) {
      if (opt->len == 'h') {
        *(short unsigned *)variable = parsed_digit;
      } else if (opt->len == 'l') {
        *(long unsigned *)variable = parsed_digit;
      } else {
        *(unsigned *)variable = parsed_digit;
      }
    }
  }
  return digit_len;
}

short s21_scan_s(char **cur, specifier_options *opt, void *variable) {
  int str_len = 0;

  if (**cur != '\0') {
    short str_width = opt->width + !(opt->width);

    while (**cur && s21_is_white_space(*cur)) *cur += 1;
    /* откусываем стартовые пробелы если справа что-то есть */

    while (**cur && !(s21_is_white_space(*cur)) && str_width) {
      if (NULL != variable) {
        *(char *)variable = **cur;
        variable = (char *)variable + 1;
      }

      *cur += 1;
      str_len++;
      if (opt->width) str_width--;
    }
    if (str_len && NULL != variable) *(char *)variable = '\0';
  }
  return str_len;
}

short s21_scan_float(char **cur, specifier_options *opt, void *variable) {
  char *start_ptr = *cur;
  float parsed_digit = strtof(*cur, cur);
  short digit_len = (*cur - start_ptr);

  int lim = opt->width;
  /* при чтении float строки управлять можем только длинной буфера чтения */
  if (lim > 0 && digit_len > lim) {
    char buffer[FLEN] = {};
    s21_strncpy(buffer, start_ptr, lim);
    parsed_digit = strtof(buffer, NULL);
    *cur = start_ptr + lim;  // переставили курсор на лимитированную позицию
  }

  if (NULL != variable) *(float *)variable = parsed_digit;

  return digit_len;
}

short s21_scan_double(char **cur, specifier_options *opt, void *variable) {
  char *start_ptr = *cur;
  double parsed_digit = strtod(*cur, cur);
  short digit_len = (*cur - start_ptr);

  int lim = opt->width;
  /* при чтении float строки управлять можем только длинной буфера чтения */
  if (lim > 0 && digit_len > lim) {
    char buffer[FLEN] = {};
    s21_strncpy(buffer, start_ptr, lim);
    parsed_digit = strtof(buffer, NULL);
    *cur = start_ptr + lim;  // переставили курсор на лимитированную позицию
  }

  if (NULL != variable) *(double *)variable = parsed_digit;

  return digit_len;
}

short s21_scan_long_double(char **cur, specifier_options *opt, void *variable) {
  char *start_ptr = *cur;
  long double parsed_digit = strtold(*cur, cur);
  short digit_len = (*cur - start_ptr);

  int lim = opt->width;
  /* при чтении float строки управлять можем только длинной буфера чтения */
  if (lim > 0 && digit_len > lim) {
    char buffer[FLEN] = {};
    s21_strncpy(buffer, start_ptr, lim);
    parsed_digit = strtold(buffer, NULL);
    *cur = start_ptr + lim;  // переставили курсор на лимитированную позицию
  }

  if (NULL != variable) *(long double *)variable = parsed_digit;

  return digit_len;
}
