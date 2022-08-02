#include "check_s21_string.h"

START_TEST(test_s21_memchr) {
  verify_memchr("", 'q', 10);
  verify_memchr("", '\0', 10);
  verify_memchr("1234567890", '4', 10);
  verify_memchr("1234567890", 'a', 10);
  verify_memchr("stri \n ng", '\0', 10);
  verify_memchr("\0 broken string", 'g', 10);
  verify_memchr(" long string", 's', 4);
  verify_memchr("find space", 32, 100);
  verify_memchr("uppeCaseAlso works", 'C', 100);
  verify_memchr("uppeCaseAlso works", 67, 100);
  verify_memchr("%%test", 'e', 100);
  verify_memchr("123 321", ' ', 100);
  verify_memchr("eeeeeeeeeetteeeee", 'e', 10);
  verify_memchr(LOREM_IPSUM, '*', 1000);
  verify_memchr(LOREM_IPSUM, 'e', 1000);
}
END_TEST

START_TEST(test_s21_memcmp) {
  verify_memcmp("aboba", "aboba", 15);
  verify_memcmp("aboba", "aabik", 15);
  verify_memcmp("aboba", "aabik", 2);
  verify_memcmp("shor", "loooooond and usless ", 2);
  verify_memcmp("shor", "loooooond and usless ", 15);
  verify_memcmp("shor", "loooooond and usless ", 50);
  verify_memcmp("\0", "", 10);
  verify_memcmp("a", "b", 10);
  verify_memcmp(" ", " ", 0);
  verify_memcmp("backslash \n en", "backslash \n en", 0);
  verify_memcmp("left", " RIGHT", 0);
  verify_memcmp("\0be", "\0not be", 12);
  verify_memcmp(LOREM_IPSUM, LOREM_IPSUM_UP, 12);
}
END_TEST

START_TEST(test_s21_memcpy) {
  verify_memcpy("Please", 2);
  verify_memcpy("Please works", 15);
  verify_memcpy("Please works \n correct", 15);
  verify_memcpy("\0broken", 15);
  verify_memcpy("         ", 15);
  verify_memcpy(" \t*102# ", 15);
  verify_memcpy("The quick brown fox jumps over the lazy dog", 15);
  verify_memcpy("The quick brown fox jumps over the lazy dog", 50);
  verify_memcpy(LOREM_IPSUM, 1000);
}
END_TEST

START_TEST(test_s21_memmove) {
  verify_memmove("Please", 2);
  verify_memmove("Please works", 15);
  verify_memmove("Please works \n correct", 15);
  verify_memmove("\0broken", 15);
  verify_memmove("         ", 15);
  verify_memmove(" \t*102# ", 15);
  verify_memmove("The quick brown fox jumps over the lazy dog", 15);
  verify_memmove("The quick brown fox jumps over the lazy dog", 50);
  verify_memmove(LOREM_IPSUM, 1000);
  verify_memmove("", 1);
  char dest1[25];
  char dest2[25];
  s21_strcpy(dest1, "some text for memmove");
  s21_strcpy(dest2, "some text for memmove");
  ck_assert_str_eq(s21_memmove(&dest1[3], &dest1[5], 3),
                   memmove(&dest2[3], &dest2[5], 3));
}
END_TEST

START_TEST(test_s21_memset) {
  verify_memset("Normal case", '/', 5);
  verify_memset("When N > than `src` len", '+', 40);
  verify_memset("Escape it all", '\0', 5);
  verify_memset("", 'z', 5);
  verify_memset("Backslash en", '\n', 4);
  verify_memset("Lorem ipsum dolor sit amet", 6, 10);  // `6` invisible char
}
END_TEST

START_TEST(test_s21_strcat) {
  verify_strcat("Pupa", "Lupa");
  verify_strcat("Base+", "long tail \t with \n special \0 caracters");
  verify_strcat("", "Add to nothing");
  verify_strcat("Nothing was added", "");
}
END_TEST

START_TEST(test_s21_strncat) {
  verify_strncat("Biba", "Boba", 0);
  verify_strncat("Biba", "Boba", 2);
  verify_strncat("Biba", "Boba", 4);
  verify_strncat("Biba", "Boba", 40);
  verify_strncat("", "Abducet praedam, qui accurrit prior.", 5);
  verify_strncat("Absit invidia", "", 40);
  verify_strncat("Some string", LOREM_IPSUM, 100);
}
END_TEST

START_TEST(test_s21_strchr) {
  verify_strchr("String has target N time", ' ');
  verify_strchr("Only \n one match", '\n');
  verify_strchr("String without expected char", 'W');
  verify_strchr("\0\0\0whynot???", '?');
  verify_strchr("", '\0');
  verify_strchr("Aloe", '\0');
  verify_strchr(LOREM_IPSUM, 'd');
}
END_TEST

START_TEST(test_s21_strcmp) {
  verify_strcmp("Android", "Android");
  verify_strcmp("Android", "Apple");
  verify_strcmp("", "Not empty");
  verify_strcmp("Not empty", "");
  verify_strcmp("21", "42");
  verify_strcmp("\0 21", "\n 42");
  verify_strcmp("    ", "  \t  ");
  verify_strcmp(LOREM_IPSUM, LOREM_IPSUM_UP);
}
END_TEST

START_TEST(test_s21_strncmp) {
  verify_strncmp("A", "Z", 0);
  verify_strncmp("A", "Z", 1);
  verify_strncmp("Has aboba", "Has sega", 3);
  verify_strncmp("Has aboba", "Has sega", 5);
  verify_strncmp("Has aboba", "Has sega", 50);
  verify_strncmp("\n456789", "300", 50000);
  verify_strncmp(LOREM_IPSUM, LOREM_IPSUM_UP, 1000);
  verify_strncmp(LOREM_IPSUM, LOREM_IPSUM, 1000);
}
END_TEST

START_TEST(test_s21_strcpy) {
  verify_strcpy("Please");
  verify_strcpy("Please works");
  verify_strcpy("Please works \n correct");
  verify_strcpy("\0broken");
  verify_strcpy("         ");
  verify_strcpy(" \t*102# ");
  verify_strcpy("The quick brown fox jumps over the lazy dog");
  verify_strcpy(LOREM_IPSUM_UP);
}
END_TEST

START_TEST(test_s21_strncpy) {
  verify_strncpy("Please", 5);
  verify_strncpy("Please works", 10);
  verify_strncpy("Please works \n correct", 15);
  verify_strncpy("\0broken", 5);
  verify_strncpy("         ", 2);
  verify_strncpy(" \t*102# ", 3);
  verify_strncpy("The quick brown fox jumps over the lazy dog", 10);
  verify_strncpy("The quick brown fox jumps over the lazy dog", 50);
  verify_strncpy(LOREM_IPSUM_UP, 1000);
}
END_TEST

START_TEST(test_s21_strcspn) {
  verify_strcspn("Android", "Android");
  verify_strcspn("android", "and");
  verify_strcspn("", "Not empty");
  verify_strcspn("Not empty", "");
  verify_strcspn("      Not empty\t\t\t\t", "");
  verify_strcspn("  \n    Not\nempty\t\t\t\t", "");
  verify_strcspn("\0 21", "\n");
  verify_strcspn("    ", "  \t  ");
  verify_strcspn(LOREM_IPSUM, LOREM_IPSUM_UP);
}
END_TEST

START_TEST(test_s21_strerror) {
  for (int i = -1; i < S21_ERROR_COUNT; i++) verify_strerror(i);
}
END_TEST

START_TEST(test_s21_strlen) {
  verify_strlen("Please");
  verify_strlen("Please works");
  verify_strlen("Please works \n correct");
  verify_strlen("\0broken");
  verify_strlen("         ");
  verify_strlen(" \t*102# ");
  verify_strlen("The quick brown fox jumps over the lazy dog");
  verify_strlen(LOREM_IPSUM);
}
END_TEST

START_TEST(test_s21_strpbrk) {
  verify_strpbrk("Android", "Android");
  verify_strpbrk("android", "and");
  verify_strpbrk("", "Not empty");
  verify_strpbrk("Not empty", "");
  verify_strpbrk("      Not empty\t\t\t\t", "");
  verify_strpbrk("  \n    Not\nempty\t\t\t\t", "");
  verify_strpbrk("\0 21", "\n");
  verify_strpbrk("    ", "  \t  ");
  verify_strpbrk(LOREM_IPSUM_UP, LOREM_IPSUM);
}
END_TEST

START_TEST(test_s21_strrchr) {
  verify_strrchr("Android", 'o');
  verify_strrchr("android", 'd');
  verify_strrchr("", 'n');
  verify_strrchr("Not empty", ' ');
  verify_strrchr("      Not empty\t\t\t\t", 5);
  verify_strrchr("  \n    Not\nempty\t\t\t\t", '\n');
  verify_strrchr("\0 21", '\n');
  verify_strrchr("    ", '\t');
  verify_strrchr(LOREM_IPSUM, 'R');
}
END_TEST

START_TEST(test_s21_strspn) {
  verify_strspn("Android", "Android");
  verify_strspn("android", "and");
  verify_strspn("", "Not empty");
  verify_strspn("Not empty", "");
  verify_strspn("      Not empty\t\t\t\t", "");
  verify_strspn("  \n    Not\nempty\t\t\t\t", "\n");
  verify_strspn("\0 21", "\n");
  verify_strspn("    ", "  \t  ");
  verify_strspn(LOREM_IPSUM, LOREM_IPSUM);
}
END_TEST

START_TEST(test_s21_strstr) {
  verify_strstr("Apple", "Apple");
  verify_strstr("android", "and");
  verify_strstr("", "Not empty");
  verify_strstr("Not empty", "");
  verify_strstr("      Not empty\t\t\t\t", "");
  verify_strstr("  \n    Not\nempty\t\t\t\t", "\n");
  verify_strstr("\0 21", "\n");
  verify_strstr("    ", "  \t  ");
  verify_strstr(LOREM_IPSUM, "LOREM");
}
END_TEST

START_TEST(test_s21_strtok) {
  verify_strtok("androidandroidand", "and");
  verify_strtok("111....234........356....467", ".....");
  verify_strtok("111...,111...;111...]111...?111", "111");
  verify_strtok("Not empty string with spaces", " ");
  verify_strtok("     \nString\nwith\nnewlines\n", "\n");
  verify_strtok("String with only one delimeter", "one");
  verify_strtok("String with no delimeter", "qwe");
  verify_strtok("", "Not empty");
  verify_strtok("Android", "Android");
  verify_strtok("\0 21", "\n");
  verify_strtok(LOREM_IPSUM, " ");

  char *do_dna[MANY];
  s21_strcpy((char *)do_dna, "one,two,three");
  ck_assert_pstr_eq("one", s21_strtok((char *)do_dna, ","));
  ck_assert_pstr_eq("two", s21_strtok(NULL, ","));
  ck_assert_pstr_eq("three", s21_strtok(NULL, ","));
  ck_assert_pstr_eq(NULL, s21_strtok(NULL, ","));
  ck_assert_pstr_eq(NULL, s21_strtok(NULL, ","));
}
END_TEST

TCase *string_base_tests(void) {
  TCase *t_case = tcase_create("Basic_functions");

  tcase_add_test(t_case, test_s21_memchr);
  tcase_add_test(t_case, test_s21_memcmp);
  tcase_add_test(t_case, test_s21_memcpy);
  tcase_add_test(t_case, test_s21_memmove);
  tcase_add_test(t_case, test_s21_memset);
  tcase_add_test(t_case, test_s21_strcat);
  tcase_add_test(t_case, test_s21_strncat);
  tcase_add_test(t_case, test_s21_strchr);
  tcase_add_test(t_case, test_s21_strcmp);
  tcase_add_test(t_case, test_s21_strncmp);
  tcase_add_test(t_case, test_s21_strcpy);
  tcase_add_test(t_case, test_s21_strncpy);
  tcase_add_test(t_case, test_s21_strcspn);
  tcase_add_test(t_case, test_s21_strerror);
  tcase_add_test(t_case, test_s21_strlen);
  tcase_add_test(t_case, test_s21_strpbrk);
  tcase_add_test(t_case, test_s21_strrchr);
  tcase_add_test(t_case, test_s21_strspn);
  tcase_add_test(t_case, test_s21_strstr);
  tcase_add_test(t_case, test_s21_strtok);

  return t_case;
}
