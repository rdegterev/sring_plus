#include "check_s21_string.h"

START_TEST(test_s21_to_lower) {
  verify_to_lower(LOREM_IPSUM, LOREM_IPSUM_LOW);
  verify_to_lower(LOREM_IPSUM_UP, LOREM_IPSUM_LOW);
  verify_to_lower(LOREM_IPSUM_LOW, LOREM_IPSUM_LOW);
  verify_to_lower("QwE", "qwe");
  verify_to_lower("Q", "q");
  verify_to_lower(NULL, NULL);
}
END_TEST

START_TEST(test_s21_to_upper) {
  verify_to_upper(LOREM_IPSUM, LOREM_IPSUM_UP);
  verify_to_upper(LOREM_IPSUM_UP, LOREM_IPSUM_UP);
  verify_to_upper(LOREM_IPSUM_LOW, LOREM_IPSUM_UP);
  verify_to_upper("asd", "ASD");
  verify_to_upper("z", "Z");
  verify_to_upper(NULL, NULL);
}
END_TEST

START_TEST(test_s21_insert) {
  verify_insert("qwe", "jjj", 2, "qwjjje");
  verify_insert(
      "C , procedural computer programming language", "is a general-purpose", 2,
      "C is a general-purpose, procedural computer programming language");
  verify_insert("qwe", "jjj", 4, NULL);
  verify_insert(NULL, "jjj", 4, NULL);
  verify_insert("N_U_L_L", NULL, 2, NULL);
  verify_insert(NULL, NULL, 2, NULL);
}
END_TEST

START_TEST(test_s21_trim) {
  verify_trim("22211112334334qwe121333", "123", "4334qwe");
  verify_trim("123321qwe121333", "123", "qwe");
  verify_trim("123321q111222333we121333", "123", "q111222333we");
  verify_trim("111222333444qwe323232", "123", "444qwe");
  verify_trim("segamegadrives", "es", "gamegadriv");
  verify_trim(" \v  sosylki\n\t", "", "sosylki");
  verify_trim(" \v  te\nst\n\t", "", "te\nst");
  verify_trim(" \v  te\nst\n\t", NULL, "te\nst");
  verify_trim("you don t know the dark side power", "you",
              " don t know the dark side power");
  verify_trim(NULL, NULL, NULL);
}
END_TEST

TCase *string_bonus_tests(void) {
  TCase *t_case = tcase_create("Bonus_functions");

  tcase_add_test(t_case, test_s21_to_lower);
  tcase_add_test(t_case, test_s21_to_upper);
  tcase_add_test(t_case, test_s21_insert);
  tcase_add_test(t_case, test_s21_trim);
  return t_case;
}
