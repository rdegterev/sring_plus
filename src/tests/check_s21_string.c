#include "check_s21_string.h"

int main(void) {
  int problems_count = 0;
  Suite *main_suite;
  SRunner *runner;

  main_suite = suite_create("All_tests");
  suite_add_tcase(main_suite, string_base_tests());
  suite_add_tcase(main_suite, string_bonus_tests());
  suite_add_tcase(main_suite, sprintf_tests());
  suite_add_tcase(main_suite, sscanf_tests());
  runner = srunner_create(main_suite);

  srunner_run_all(runner, CK_VERBOSE);
  problems_count = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (problems_count == 0) ? 0 : 1;
}
