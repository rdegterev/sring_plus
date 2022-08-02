#include "s21_string.h"

/**
 * Число в строку, без знака (!)
 *
 * @param num число
 * @param str указатель на место вставки
 * @param base основание системы счисления
 * @param isUpper использовать ли заглавные буквы для хексов
 * @return size_t ширина получившегося "текста" (без учета конца строки)
 */
s21_size_t s21_itoa(long long num, char *dest) {
  char *first_letter = dest;

  s21_size_t result_len = 0;

  if (num == 0) {
    s21_put_char(dest, '0');
    dest++;
    result_len++;
  } else {
    while (num != 0) {
      int reminder = num % 10;
      if (reminder < 0) reminder = -reminder;
      s21_put_char(dest, reminder + '0');
      dest++;
      result_len++;
      num = num / 10;
    }

    s21_reverse(first_letter, 0, result_len - 1);
  }
  s21_put_char(dest, '\0');
  return result_len;
}

s21_size_t s21_u_itoa(unsigned long num, char *dest, int base, short isUpper) {
  char *first_letter = dest;

  s21_size_t result_len = 0;

  if (num == 0) {
    s21_put_char(dest, '0');
    dest++;
    result_len++;
  } else {
    while (num != 0) {
      int reminder = num % base;
      char letter = (isUpper) ? 'A' : 'a';
      s21_put_char(dest,
                   (reminder > 9) ? (reminder - 10) + letter : reminder + '0');

      dest++;
      result_len++;
      num = num / base;
    }

    s21_reverse(first_letter, 0, result_len - 1);
  }
  s21_put_char(dest, '\0');
  return result_len;
}
