#include "check_s21_string.h"

void verify_memchr(const void *str, int c, s21_size_t n) {
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}

void verify_memcmp(const void *s1, const void *s2, s21_size_t n) {
  if (memcmp(s1, s2, n) > 0) ck_assert_int_ge(s21_memcmp(s1, s2, n), 1);
  if (memcmp(s1, s2, n) < 0) ck_assert_int_le(s21_memcmp(s1, s2, n), -1);
  if (memcmp(s1, s2, n) == 0) ck_assert_int_eq(s21_memcmp(s1, s2, n), 0);
}

void verify_memcpy(const void *src, s21_size_t n) {
  char dest1[MANY];
  char dest2[MANY];
  /**
   * Суть проблемы в том что библиотечная функция не гарантирует окончание
   * строки если mem ограничение сработало раньше, чтобы убедиться в одинаковом
   * поведении выделяем память с запасом и заполняем одинаковыми символами,
   * таким образом можем гарантировать что ни библиотечная ни наша функция не
   * залезли в память правее ограничения
   */
  for (s21_size_t i = 0; i < MANY; i++) {
    char filler = (MANY - 1 == i) ? '\0' : '_';
    dest1[i] = dest2[i] = filler;
  }
  ck_assert_str_eq(s21_memcpy(dest1, src, n), memcpy(dest2, src, n));
}

void verify_memmove(const void *src, s21_size_t n) {
  char dest1[MANY];
  char dest2[MANY];
  for (s21_size_t i = 0; i < MANY; i++) {
    char filler = (MANY - 1 == i) ? '\0' : '_';
    dest1[i] = dest2[i] = filler;
  }
  ck_assert_str_eq(s21_memmove(dest1, src, n), memmove(dest2, src, n));
}

void verify_memset(const void *src, int c, s21_size_t n) {
  char testdata1[MANY] = {0};
  char testdata2[MANY] = {0};

  ck_assert_str_eq(s21_memset(testdata1, c, n), memset(testdata2, c, n));
}

void verify_strcat(char *dest, const char *src) {
  void *testdata1 = prepared_copy(dest);
  void *testdata2 = prepared_copy(dest);

  ck_assert_str_eq(s21_strcat(testdata1, src), strcat(testdata2, src));

  free(testdata1);
  free(testdata2);
}

void verify_strncat(char *dest, const char *src, s21_size_t n) {
  void *testdata1 = prepared_copy(dest);
  void *testdata2 = prepared_copy(dest);

  ck_assert_str_eq(s21_strncat(testdata1, src, n), strncat(testdata2, src, n));

  free(testdata1);
  free(testdata2);
}

void verify_strchr(const char *str, int c) {
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));
}

void verify_strcmp(const char *left, const char *right) {
  if (strcmp(left, right) > 0) ck_assert_int_ge(s21_strcmp(left, right), 1);
  if (strcmp(left, right) < 0) ck_assert_int_le(s21_strcmp(left, right), -1);
  if (strcmp(left, right) == 0) ck_assert_int_eq(s21_strcmp(left, right), 0);
}

void verify_strncmp(const char *l, const char *r, s21_size_t n) {
  if (strncmp(l, r, n) > 0) ck_assert_int_ge(s21_strncmp(l, r, n), 1);
  if (strncmp(l, r, n) < 0) ck_assert_int_le(s21_strncmp(l, r, n), -1);
  if (strncmp(l, r, n) == 0) ck_assert_int_eq(s21_strncmp(l, r, n), 0);
}

void verify_strcspn(const char *str, const char *char_set) {
  ck_assert_int_eq(s21_strcspn(str, char_set), strcspn(str, char_set));
}

void verify_strcpy(const char *src) {
  char *testdata1 = malloc((strlen(src) + 1) * sizeof(char));
  char *testdata2 = malloc((strlen(src) + 1) * sizeof(char));

  ck_assert_str_eq(s21_strcpy(testdata1, src), strcpy(testdata2, src));

  free(testdata1);
  free(testdata2);
}

void verify_strncpy(const char *src, s21_size_t n) {
  char *testdata1 = calloc(MANY, sizeof(char));
  char *testdata2 = calloc(MANY, sizeof(char));

  ck_assert_pstr_eq(s21_strncpy(testdata1, src, n), strncpy(testdata2, src, n));

  free(testdata1);
  free(testdata2);
}

void verify_strerror(int errnum) {
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}

void verify_strlen(const char *str) {
  ck_assert_int_eq(s21_strlen(str), strlen(str));
}

void verify_strpbrk(const char *str, const char *char_set) {
  ck_assert_ptr_eq(s21_strpbrk(str, char_set), strpbrk(str, char_set));
}

void verify_strrchr(const char *str, int chr) {
  ck_assert_ptr_eq(s21_strrchr(str, chr), strrchr(str, chr));
}

void verify_strspn(const char *str, const char *char_set) {
  ck_assert_int_eq(s21_strspn(str, char_set), strspn(str, char_set));
}

void verify_strstr(const char *haystack, const char *needle) {
  ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}

void verify_strtok(char *str, const char *delim) {
  char *testdata1 = prepared_copy(str);
  char *testdata2 = prepared_copy(str);

  ck_assert_pstr_eq(s21_strtok(testdata1, delim), strtok(testdata2, delim));
  ck_assert_pstr_eq(s21_strtok(testdata1, delim), strtok(testdata2, delim));

  free(testdata1);
  free(testdata2);
}

/**
 * Из-за side effects большинства функций приходится делать глубокие копии плюс
 * для надежности тестов расширять и заполнять служебными символами
 *
 * пример:
 *    prepared_copy("dog") => "dog\0___________________________\0"
 *
 * !!! НЕ ЗАБЫВАТЬ !!! делать free
 */
void *prepared_copy(const void *src) {
  void *res = calloc(MANY, sizeof(char));

  for (s21_size_t i = 0; i < (MANY / 2); i++) ((char *)res)[i] = '_';

  s21_strcpy(res, src);
  return res;
}

// ----------------------- SPRINTF -----------------------

void verify_sprintf_int(const char *format, int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_long_int(const char *format, long int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_short_int(const char *format, short int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_u_long_int(const char *format, unsigned long int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_u_short_int(const char *format, unsigned short int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_d_with_star(const char *format, int star, int num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, star, num);
  int len2 = sprintf(expected, format, star, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_char(const char *format, char sym) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, sym);
  int len2 = sprintf(expected, format, sym);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_str(const char *format, char *str) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, str);
  int len2 = sprintf(expected, format, str);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_float(const char *format, double num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_long_double(const char *format, long double num) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, num);
  int len2 = sprintf(expected, format, num);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

void verify_sprintf_ptr(const char *format, void *p1, void *p2) {
  char actual[MANY];
  char expected[MANY];
  int len1 = s21_sprintf(actual, format, p1, p2, (unsigned long)0xDEADBEEF);
  int len2 = sprintf(expected, format, p1, p2, (unsigned long)0xDEADBEEF);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
}

/**
 * (!) На маке null-poiter принтится как 0x0, а linux как nil
 * Чтобы стабилизировать тесты задаем ожидание в явном виде
 */
void verify_sprintf_ptr_e(const char *format, void *p, const char *expected) {
  char actual[MANY];
  s21_sprintf(actual, format, p);
  ck_assert_str_eq(actual, expected);
}

void verify_sprintf_n(const char *format) {
  char actual[MANY];
  char expected[MANY];

  s21_size_t a1 = 0;
  s21_size_t b1 = 0;
  s21_size_t c1 = 0;
  s21_size_t a2 = 0;
  s21_size_t b2 = 0;
  s21_size_t c2 = 0;

  int len1 = s21_sprintf(actual, format, LOREM_IPSUM, &a1, &b1, &c1);
  int len2 = sprintf(expected, format, LOREM_IPSUM, &a2, &b2, &c2);

  ck_assert_str_eq(actual, expected);
  ck_assert_int_eq(len1, len2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}

// ----------------------- SSCANF -----------------------

void verify_sscanf_int(const char *input, const char *format) {
  int num_actual = 404;
  int num_expected = 404;

  int len_actual = s21_sscanf(input, format, &num_actual);
  int len_expected = sscanf(input, format, &num_expected);

  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_long_int(const char *input, const char *format) {
  long num_actual = 404;
  long num_expected = 404;

  int len_actual = s21_sscanf(input, format, &num_actual);
  int len_expected = sscanf(input, format, &num_expected);

  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_short_int(const char *input, const char *format) {
  short num_actual = 404;
  short num_expected = 404;

  int len_actual = s21_sscanf(input, format, &num_actual);
  int len_expected = sscanf(input, format, &num_expected);

  ck_assert_int_eq(num_actual, num_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_float(const char *input, const char *format) {
  float num_a1 = 0.;
  float num_a2 = 0.;

  float num_e1 = 0.;
  float num_e2 = 0.;

  int len_actual = s21_sscanf(input, format, &num_a1, &num_a2);
  int len_expected = sscanf(input, format, &num_e1, &num_e2);

  ck_assert_float_eq(num_a1, num_e1);
  ck_assert_float_eq(num_a2, num_e2);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_double(const char *input, const char *format) {
  double num_a1 = 0.;
  double num_a2 = 0.;

  double num_e1 = 0.;
  double num_e2 = 0.;

  int len_actual = s21_sscanf(input, format, &num_a1, &num_a2);
  int len_expected = sscanf(input, format, &num_e1, &num_e2);

  ck_assert_double_eq(num_a1, num_e1);
  ck_assert_double_eq(num_a2, num_e2);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_long_double(const char *input, const char *format) {
  long double num_a1 = 0.;
  long double num_a2 = 0.;

  long double num_e1 = 0.;
  long double num_e2 = 0.;

  int len_actual = s21_sscanf(input, format, &num_a1, &num_a2);
  int len_expected = sscanf(input, format, &num_e1, &num_e2);

  ck_assert_ldouble_eq(num_a1, num_e1);
  ck_assert_ldouble_eq(num_a2, num_e2);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_lu(const char *input, const char *format) {
  unsigned long num_actual = 404;
  unsigned long num_expected = 404;

  int len_actual = s21_sscanf(input, format, &num_actual);
  int len_expected = sscanf(input, format, &num_expected);

  ck_assert_uint_eq(num_actual, num_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_percent(const char *input, const char *format) {
  int num_actual1 = 404;
  int num_actual2 = 404;
  int num_expected1 = 404;
  int num_expected2 = 404;

  int len_actual = s21_sscanf(input, format, &num_actual1, &num_actual2);
  int len_expected = sscanf(input, format, &num_expected1, &num_expected2);

  ck_assert_int_eq(num_actual1, num_expected1);
  ck_assert_int_eq(num_actual2, num_expected2);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_none(const char *input, const char *format) {
  int num_actual1 = 404;
  int num_actual2 = 404;
  int num_expected1 = 404;
  int num_expected2 = 404;
  int none_act = 0;
  int none_exp = 0;

  int len_actual =
      s21_sscanf(input, format, &num_actual1, &none_act, &num_actual2);
  int len_expected =
      sscanf(input, format, &num_expected1, &none_exp, &num_expected2);

  ck_assert_int_eq(num_actual1, num_expected1);
  ck_assert_int_eq(num_actual2, num_expected2);
  ck_assert_int_eq(none_act, none_exp);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_unsign(const char *input, const char *format) {
  unsigned num_actual = 404;
  unsigned num_expected = 404;

  int len_actual = s21_sscanf(input, format, &num_actual);
  int len_expected = sscanf(input, format, &num_expected);

  ck_assert_uint_eq(num_actual, num_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_ptr(const char *input, const char *format) {
  int q = 777;
  int w = 777;

  void *ptr11 = &q;
  void *ptr12 = &q;
  void *ptr21 = &w;
  void *ptr22 = &w;

  int len1 = s21_sscanf(input, format, &ptr11, &ptr21);
  int len2 = sscanf(input, format, &ptr12, &ptr22);

  ck_assert_ptr_eq(ptr11, ptr12);
  ck_assert_ptr_eq(ptr21, ptr22);
  ck_assert_int_eq(len1, len2);
}

void verify_sscanf_char(const char *input, const char *format) {
  char char_actual = '?';
  char char_expected = '?';

  int len_actual = s21_sscanf(input, format, &char_actual);
  int len_expected = sscanf(input, format, &char_expected);

  ck_assert_int_eq(char_actual, char_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_str(const char *input, const char *format) {
  char str_actual[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_expected[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};

  int len_actual = s21_sscanf(input, format, str_actual);
  int len_expected = sscanf(input, format, str_expected);

  ck_assert_pstr_eq(str_actual, str_expected);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_strs(const char *input, const char *format) {
  char str_actual1[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_actual2[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_actual3[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_expected1[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_expected2[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};
  char str_expected3[MANY] = {'i', 'n', 'i', 't', 'i', 'a', 'l', 0};

  int len_actual =
      s21_sscanf(input, format, str_actual1, str_actual2, str_actual3);
  int len_expected =
      sscanf(input, format, str_expected1, str_expected2, str_expected3);

  ck_assert_pstr_eq(str_actual1, str_expected1);
  ck_assert_pstr_eq(str_actual2, str_expected2);
  ck_assert_pstr_eq(str_actual3, str_expected3);
  ck_assert_int_eq(len_actual, len_expected);
}

void verify_sscanf_ints(const char *input, const char *format) {
  int nums_actual[5] = {};
  int nums_expected[5] = {};

  int *a = &nums_actual[0];
  int *e = &nums_expected[0];

  int len_actual = s21_sscanf(input, format, a, a + 1, a + 2, a + 3, a + 4);
  int len_expected = sscanf(input, format, e, e + 1, e + 2, e + 3, e + 4);

  for (int i = 0; i < 5; i++) {
    ck_assert_int_eq(nums_actual[i], nums_expected[i]);
  }
  ck_assert_int_eq(len_actual, len_expected);
}

// ----------------------- BONUS -----------------------

void verify_to_lower(const char *str, const char *expected) {
  char *actual = s21_to_lower(str);
  ck_assert_pstr_eq(actual, expected);
  if (NULL != actual) free(actual);
}

void verify_to_upper(const char *str, const char *expected) {
  char *actual = s21_to_upper(str);
  ck_assert_pstr_eq(actual, expected);
  if (NULL != actual) free(actual);
}

void verify_insert(const char *src, const char *insertion, s21_size_t n,
                   const char *expected) {
  char *actual = s21_insert(src, insertion, n);
  ck_assert_pstr_eq(actual, expected);
  if (NULL != actual) free(actual);
}

void verify_trim(const char *str, const char *trim_c, const char *expected) {
  char *actual = s21_trim(str, trim_c);
  ck_assert_pstr_eq(actual, expected);
  if (NULL != actual) free(actual);
}
