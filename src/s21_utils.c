#include "s21_string.h"

int s21_min(int a, int b) {
  //
  return (a < b) ? a : b;
}

int s21_max(int a, int b) {
  //
  return (a > b) ? a : b;
}

short s21_isnan(double f) {
  //
  return (f != f);
}

short s21_isnormal(double f) {
  //
  return !(s21_isinf(f) || s21_isnan(f));
}

short s21_isinf(double f) {
  //
  return (f == 1.0 / 0.0) || (f == -1.0 / 0.0);
}

double s21_fabs(double f) {
  //
  return (f < 0) ? -f : f;
}

double s21_round(double d) {
  d += 0.5;
  d = (long int)d;
  return (double)d;
}

short s21_is_white_space(char *x) {
  //
  return (NULL != s21_strchr(WHITE_SPACES, *x));
}

s21_size_t s21_insert_sign(char **dest_ptr, s21_size_t isPositive, flags *f,
                           s21_size_t *cnt) {
  s21_size_t result = 1;
  if (isPositive) {
    if (f->plus) {
      s21_put_char(*dest_ptr, '+');
    } else if (f->space) {
      s21_put_char(*dest_ptr, ' ');
    } else {
      result = 0;
    }
  } else { /* negative */
    s21_put_char(*dest_ptr, '-');
  }
  *dest_ptr += result; /* move pointer to next char */
  *cnt += result;      /* increment external counter */
  return result;
}

s21_size_t s21_precission_correction(char **dest_ptr, s21_size_t digit_len,
                                     specifier_options *o, s21_size_t *cnt) {
  s21_size_t result = 0;

  int correction_width = o->precision - digit_len;
  if (correction_width > 0) {
    result = correction_width;

    while (correction_width--) {
      s21_put_char(*dest_ptr, '0');
      *dest_ptr += 1;
    }
  }
  *cnt += result; /* increment external counter */
  return result;
}

/**
 * Вставит (переписывая) n букв из src в dest
 * @param dest_ptr - Строка куда пишем
 * @param src - Строка с символами которые пишем
 * @param n - Сколько символов пишем
 * @param cnt - Внешний счетчик
 */
void s21_strnput(char **dest_ptr, char *src, s21_size_t n, s21_size_t *cnt) {
  short dry_run = (S21_NULL == dest_ptr) || (S21_NULL == *dest_ptr);
  while (n--) {
    if (!dry_run) {
      **dest_ptr = *src; /* скопировал букву */
      *dest_ptr += 1;    /* сдвинул адрес */
      src += 1;          /* сдвинул адрес */
    }
    *cnt += 1; /* прибавил внешний счетчик */
  }
}

/**
 * Добавляет префиксы `0` `0x` `0X`
 */
void s21_ins_pref(char **dest_ptr, s21_size_t *cnt, s21_size_t preflen,
                  short isUpper) {
  char pref[3] = {};
  pref[0] = '0';
  pref[1] = isUpper ? 'X' : 'x';
  s21_strnput(dest_ptr, pref, preflen, cnt);
}

/**
 * Вернет разницу между числами если она положительная
 * Иначе 0
 */
s21_size_t s21_positive_diff(int left, int right) {
  int diff = left - right;
  return (diff > 0) ? diff : 0;
}

/**
 * Развернет сиволы в перечислении от begin до end
 * пример:
 *    _reverse(['-','q','w','e', 'Z'], 1, 3) => ['-','e','w','q', 'Z']
 */
void s21_reverse(char *p, int begin, int end) {
  if (NULL != p) {
    int shift = 0;

    while ((p + begin + shift) < (p + end - shift)) {  // left_addr < right_addr
      char buffer = *(p + begin + shift);
      *(p + begin + shift) = *(p + end - shift);  // left
      *(p + end - shift) = buffer;                // right
      shift++;
    }
  }
}

/**
 * Вставка символа в позицию строки
 * если NULL просто сделает ничего
 */
void s21_put_char(char *place, char symbol) {
  if (NULL != place) *place = symbol;
}

/**
 * Вставка `n` символов в строку начиная с позиции `place`
 * если NULL просто сделает ничего
 */
s21_size_t s21_put_nchar(char **place_ptr, char symbol, s21_size_t count) {
  short dry_run = (NULL == place_ptr) || (NULL == *place_ptr);

  if (!dry_run) {
    for (s21_size_t i = 0; i < count; i++) {
      **place_ptr = symbol;
      *place_ptr += 1;
    }
  }
  return count;
}
