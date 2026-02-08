#include "test.h"

int test(Suite *function) {
  int number_failed;
  Suite *s = function;
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(void) {
  Suite *functions[] = {suite_s21_add(),
                        suite_s21_sub(),
                        suite_s21_mul(),
                        suite_s21_div(),
                        suite_s21_is_less(),
                        suite_s21_is_less_or_equal(),
                        suite_s21_is_greater(),
                        suite_s21_is_greater_or_equal(),
                        suite_s21_is_equal(),
                        suite_s21_is_not_equal(),
                        suite_s21_int_to_decimal(),
                        suite_s21_float_to_decimal(),
                        suite_s21_decimal_to_int(),
                        suite_s21_decimal_to_float(),
                        suite_s21_floor(),
                        suite_s21_round(),
                        suite_s21_truncate(),
                        suite_s21_negate(),
                        NULL};
  int count = 0;
  for (Suite **current_test = functions; *current_test != NULL;
       current_test++) {
    if (test(*current_test) == EXIT_FAILURE) {
      printf("Test %d failed\n", count + 1);
    }
    count++;
  }
  return 0;
}