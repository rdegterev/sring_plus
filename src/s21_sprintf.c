#include "s21_string.h"

/**
 * Отправляет форматированный вывод в строку, на которую указывает str
 */
int s21_sprintf(char *str, const char *format, ...) {
  int output_len = 0;  // счетчик, сколько букв уже напихали в str

  va_list args;
  va_start(args, format);

  char *cur = (char *)format;  // курсор которым будем идти по форматной строке
  specifier_options *opt = calloc(1, sizeof(specifier_options));

  while (*cur) {
    if (*cur == SPECIFIER) {
      s21_reset_options(opt);
      opt->start = cur;
      cur++;
      s21_read_p_options(cur, opt, args);
      cur = opt->finish;

      output_len += s21_build_fragment(str + output_len, opt, args, output_len);

    } else {
      str[output_len] = *cur;
      output_len++;
    }

    cur++;
  }
  str[output_len] = '\0';

  va_end(args);
  free(opt);

  return output_len;
}

/**
 * Сбрасывает поля структуры в начальное состояние
 */
void s21_reset_options(specifier_options *opts) {
  opts->flag.minus = 0;
  opts->flag.plus = 0;
  opts->flag.space = 0;
  opts->flag.sharp = 0;
  opts->flag.zero = 0;

  opts->width = 0;
  opts->precision = -1;
  opts->len = 0;
  opts->start = NULL;
  opts->finish = NULL;
}

/**
 * Собирает в структуру все от знака процента до спецификатора
 * Учитывает правила формирования спецификаторов для print
 */
void s21_read_p_options(const char *str, specifier_options *opt, va_list args) {
  char *pos = (char *)str;
  int segment_length = s21_strcspn(pos, SPECIFICATORS);
  opt->finish = pos + segment_length;

  if (segment_length) {
    /* для простых случаев вида `%d` можно дальше не искать */

    const s21_size_t flags_len = s21_strspn(pos, FLAGS);

    for (s21_size_t i = 0; i < flags_len; i++) {
      s21_set_flag(pos[i], opt);
    }
    pos += flags_len;  // флаги считаны идем дальше

    /* Если юзер ввел жесть, приоритет отдаем звезде */
    const int width_len = s21_strspn(pos, DIGITS_N_STAR);
    if (S21_NULL == s21_memchr(pos, '*', width_len)) {
      opt->width = s21_atoi(pos, width_len);
    } else {
      opt->width = va_arg(args, unsigned);
    }
    pos += width_len;

    if (*pos == '.') {
      pos++;
      const int precision_len = s21_strspn(pos, DIGITS_N_STAR);
      /* Если юзер ввел жесть, приоритет отдаем звезде */
      if (S21_NULL == s21_memchr(pos, '*', precision_len)) {
        opt->precision = s21_atoi(pos, precision_len);
      } else {
        opt->precision = va_arg(args, unsigned);
      }
      pos += precision_len;
    }

    if (pos < (opt->finish)) {
      /* считаем, что буква длинны лишь одна */
      const int length_len = s21_strspn(pos, LENGTH);
      opt->len = (length_len) ? *pos : 0;
    }
  }
}

/**
 * У скана другая логика обработки звездочки и точности
 * чтобы не усложнять выделил в отдельный метод
 */
void s21_read_s_options(const char *str, specifier_options *opt) {
  char *pos = (char *)str;
  int segment_length = s21_strcspn(pos, SPECIFICATORS);
  opt->finish = pos + segment_length;

  if (segment_length) {
    /* для простых случаев вида `%d` можно дальше не искать */

    const s21_size_t flags_len = s21_strspn(pos, FLAGS);

    for (s21_size_t i = 0; i < flags_len; i++) {
      s21_set_flag(pos[i], opt);
    }
    pos += flags_len;

    const int width_len = s21_strspn(pos, DIGITS_N_STAR);
    if (S21_NULL == s21_memchr(pos, '*', width_len)) {
      opt->width = s21_atoi(pos, width_len);
    } else {
      /* мета-признак что считывание должно быть пропущено */
      opt->width = -1;
    }
    pos += width_len;

    if (*pos == '.') {
      /* точность неприменима для sscanf дальше можно не стараться */
      opt->precision = 1;
    } else if (pos < (opt->finish)) {
      const int length_len = s21_strspn(pos, LENGTH);
      opt->len = (length_len) ? *pos : 0;
    }
  }
}

/**
 * У разных типов разные флаги по-умолчанию. Метод учитывающий.
 */
void s21_apply_default(specifier_options *opts) {
  if (opts->precision == -1) {
    if (S21_NULL != s21_strchr("feEgG", *(opts->finish))) {
      opts->precision = 6;
    } else {
      opts->precision = 0;
    }
  }
}

/**
 * Точка входа. В зависимости от типа вызовет нужную функцию
 * и заполнит строку по объявленным правилам
 *
 * @param output выходная строка
 * @param opt структура хранящая знание о спецификаторах-модификаторах
 * @param arg va_list откуда можно вынуть аргумент и привести к желаемому типу
 * @return size_t длинна результирующей вставки
 */
s21_size_t s21_build_fragment(char *output, specifier_options *opt,
                              va_list arg_list, int output_len) {
  s21_size_t fragment_len = 0;
  s21_apply_default(opt);
  if (*(opt->finish) == '%') {
    *output = '%';
    fragment_len = 1;
  }

  if (*(opt->finish) == 'd' || *(opt->finish) == 'i') {
    if (opt->len == 'h') {
      fragment_len +=
          s21_append_digit((short)va_arg(arg_list, int), output, opt);
    } else if (opt->len == 'l') {
      fragment_len += s21_append_digit(va_arg(arg_list, long), output, opt);
    } else {
      fragment_len += s21_append_digit(va_arg(arg_list, int), output, opt);
    }
  }

  if (*(opt->finish) == 'c') {
    fragment_len += s21_append_char(va_arg(arg_list, int), output, opt);
  }

  if (*(opt->finish) == 's') {
    fragment_len += s21_append_str(va_arg(arg_list, char *), output, opt);
  }

  if (*(opt->finish) == 'f') {
    if (opt->len == 'L') {
      fragment_len +=
          s21_append_float(va_arg(arg_list, long double), output, opt, FALSE);
    } else {
      fragment_len +=
          s21_append_float(va_arg(arg_list, double), output, opt, FALSE);
    }
  }

  if (S21_NULL != s21_strchr("eE", *(opt->finish))) {
    if (opt->len == 'L') {
      fragment_len +=
          s21_append_science(va_arg(arg_list, long double), output, opt, FALSE);
    } else {
      fragment_len +=
          s21_append_science(va_arg(arg_list, double), output, opt, FALSE);
    }
  }

  if (S21_NULL != s21_strchr("gG", *(opt->finish))) {
    // Использует кратчайший из представлений форматов %e или %f
    if (opt->len == 'L') {
      fragment_len += s21_append_g(va_arg(arg_list, long double), output, opt);
    } else {
      fragment_len += s21_append_g(va_arg(arg_list, double), output, opt);
    }
  }

  if (*(opt->finish) == 'o') {
    // Беззнаковое восьмеричное число
    if (opt->len == 'h') {
      fragment_len += s21_append_o_digit(
          (unsigned short)va_arg(arg_list, unsigned), output, opt);
    } else if (opt->len == 'l') {
      fragment_len +=
          s21_append_o_digit(va_arg(arg_list, unsigned long), output, opt);
    } else {
      fragment_len +=
          s21_append_o_digit(va_arg(arg_list, unsigned), output, opt);
    }
  }

  if (*(opt->finish) == 'u') {
    // Беззнаковое десятичное целое число
    if (opt->len == 'h') {
      fragment_len += s21_append_u_digit(
          (unsigned short)va_arg(arg_list, unsigned), output, opt);
    } else if (opt->len == 'l') {
      fragment_len +=
          s21_append_u_digit(va_arg(arg_list, unsigned long), output, opt);
    } else {
      fragment_len +=
          s21_append_u_digit(va_arg(arg_list, unsigned), output, opt);
    }
  }

  if (*(opt->finish) == 'x') {
    // Беззнаковое шестнадцатеричное целое число
    if (opt->len == 'h') {
      fragment_len += s21_append_x_digit(
          (unsigned short)va_arg(arg_list, unsigned), output, opt, FALSE);
    } else if (opt->len == 'l') {
      fragment_len += s21_append_x_digit(va_arg(arg_list, unsigned long),
                                         output, opt, FALSE);
    } else {
      fragment_len +=
          s21_append_x_digit(va_arg(arg_list, unsigned), output, opt, FALSE);
    }
  }

  if (*(opt->finish) == 'X') {
    if (opt->len == 'h') {
      fragment_len += s21_append_x_digit(
          (unsigned short)va_arg(arg_list, unsigned), output, opt, TRUE);
    } else if (opt->len == 'l') {
      fragment_len += s21_append_x_digit(va_arg(arg_list, unsigned long),
                                         output, opt, TRUE);
    } else {
      fragment_len +=
          s21_append_x_digit(va_arg(arg_list, unsigned), output, opt, TRUE);
    }
  }

  if (*(opt->finish) == 'p') {
    fragment_len += s21_append_ptr(va_arg(arg_list, void *), output, opt);
  }

  if (*(opt->finish) == 'n') {
    // Количество символов, напечатанных до появления %n
    *(int *)va_arg(arg_list, int *) = output_len;
  }

  return fragment_len;
}

/**
 * Складывает флаги в структуру
 */
void s21_set_flag(char c, specifier_options *o) {
  o->flag.minus |= ('-' == c);
  o->flag.plus |= ('+' == c);
  o->flag.space |= (' ' == c);
  o->flag.sharp |= ('#' == c);
  o->flag.zero |= ('0' == c);
}

/**
 * Возьмет первые lim символов строки и конвертирует в число
 * в случае неудачи вернет 0
 * НЕ РАБОТАЕТ С ОТРИЦАТЕЛЬНЫМИ
 */
int s21_atoi(char *str, s21_size_t lim) {
  const s21_size_t str_len = s21_strlen(str);
  const s21_size_t real_lim = (lim < str_len) ? lim : str_len;

  int res = 0;
  if (s21_strspn(str, DIGITS) == real_lim) {
    for (s21_size_t i = 0; i < real_lim; i++) {
      res = res * 10 + (str[i] - '0');
    }
  }
  return res;
}
