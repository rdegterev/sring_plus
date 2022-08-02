#include <check.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

#ifndef SRC_TESTS_CHECK_S21_STRING_H_
#define SRC_TESTS_CHECK_S21_STRING_H_

#define RESERVE_RATIO 10
#define MANY 3000
#define S21_NAN 0.f / 0.f * -1
#define S21_INFINITY 1.0 / 0.0

void verify_memchr(const void *, int, s21_size_t);
void verify_memcmp(const void *, const void *, s21_size_t);
void verify_memcpy(const void *, s21_size_t);
void verify_memmove(const void *, s21_size_t);
void verify_memset(const void *, int, s21_size_t);
void verify_strcat(char *, const char *);
void verify_strncat(char *, const char *, s21_size_t);
void verify_strchr(const char *, int);
void verify_strcmp(const char *, const char *);
void verify_strncmp(const char *, const char *, s21_size_t);
void verify_strcpy(const char *);
void verify_strncpy(const char *, s21_size_t);
void verify_strcspn(const char *, const char *);
void verify_strerror(int);
void verify_strlen(const char *);
void verify_strpbrk(const char *, const char *);
void verify_strrchr(const char *, int);
void verify_strspn(const char *, const char *);
void verify_strstr(const char *, const char *);
void verify_strtok(char *, const char *);

void verify_sprintf_int(const char *, int);
void verify_sprintf_long_int(const char *, long int);
void verify_sprintf_short_int(const char *, short int);
void verify_sprintf_u_long_int(const char *, unsigned long int);
void verify_sprintf_u_short_int(const char *, unsigned short int);
void verify_sprintf_d_with_star(const char *, int, int);

void verify_sprintf_char(const char *, char);
void verify_sprintf_str(const char *, char *);
void verify_sprintf_float(const char *, double);
void verify_sprintf_long_double(const char *, long double);
void verify_sprintf_combo(const char *, int, int, char, char *, float);
void verify_sprintf_ptr(const char *, void *, void *);
void verify_sprintf_ptr_e(const char *, void *, const char *);
void verify_sprintf_n(const char *);

void verify_sscanf_int(const char *, const char *);
void verify_sscanf_long_int(const char *, const char *);
void verify_sscanf_short_int(const char *, const char *);
void verify_sscanf_float(const char *, const char *);
void verify_sscanf_double(const char *, const char *);
void verify_sscanf_long_double(const char *, const char *);
void verify_sscanf_unsign(const char *, const char *);
void verify_sscanf_percent(const char *, const char *);
void verify_sscanf_lu(const char *, const char *);
void verify_sscanf_ints(const char *, const char *);
void verify_sscanf_char(const char *, const char *);
void verify_sscanf_ptr(const char *, const char *);
void verify_sscanf_str(const char *, const char *);
void verify_sscanf_strs(const char *, const char *);
void verify_sscanf_none(const char *, const char *);

void verify_to_lower(const char *, const char *);
void verify_to_upper(const char *, const char *);
void verify_insert(const char *, const char *, s21_size_t, const char *);
void verify_trim(const char *, const char *, const char *);

void *prepared_copy(const void *);

TCase *string_base_tests(void);
TCase *string_bonus_tests(void);
TCase *sprintf_tests(void);
TCase *sscanf_tests(void);

#define LOREM_IPSUM                                                          \
  "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod " \
  "tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "    \
  "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea " \
  "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "  \
  "velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "       \
  "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "     \
  "mollit anim id est laborum."

#define LOREM_IPSUM_LOW                                                      \
  "lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod " \
  "tempor incididunt ut labore et dolore magna aliqua. ut enim ad minim "    \
  "veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea " \
  "commodo consequat. duis aute irure dolor in reprehenderit in voluptate "  \
  "velit esse cillum dolore eu fugiat nulla pariatur. excepteur sint "       \
  "occaecat cupidatat non proident, sunt in culpa qui officia deserunt "     \
  "mollit anim id est laborum."

#define LOREM_IPSUM_UP                                                       \
  "LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT, SED DO EIUSMOD " \
  "TEMPOR INCIDIDUNT UT LABORE ET DOLORE MAGNA ALIQUA. UT ENIM AD MINIM "    \
  "VENIAM, QUIS NOSTRUD EXERCITATION ULLAMCO LABORIS NISI UT ALIQUIP EX EA " \
  "COMMODO CONSEQUAT. DUIS AUTE IRURE DOLOR IN REPREHENDERIT IN VOLUPTATE "  \
  "VELIT ESSE CILLUM DOLORE EU FUGIAT NULLA PARIATUR. EXCEPTEUR SINT "       \
  "OCCAECAT CUPIDATAT NON PROIDENT, SUNT IN CULPA QUI OFFICIA DESERUNT "     \
  "MOLLIT ANIM ID EST LABORUM."

#if defined(__APPLE__) && defined(__MACH__)
#define IS_APPLE 1
#else
#define IS_APPLE 0
#endif

#endif  // SRC_TESTS_CHECK_S21_STRING_H_
