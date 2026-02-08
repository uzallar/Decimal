#include "test.h"

START_TEST(greater_1) {
  s21_decimal value_1 = {{458, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_2) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{456, 0, 0, 0}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_3) {
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  int result = s21_is_greater(value_3, value_4);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_4) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, UINT_MAX / 2 + 1}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_5) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_6) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, PLUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_7) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{461, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_8) {
  s21_decimal value_1 = {{461, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_9) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_10) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 0);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_11) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(greater_12) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(greater_13) {
  s21_decimal value_1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x130000}};
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0xE0000}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(greater_14) {
  s21_decimal value_1 = {{0xAAAAAAA9, 0xAAAAAAAA, 0x0, 0x00130000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0xE0000}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(greater_15) {
  s21_decimal value_1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0x0, 0x130000}};
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0xE0000}};
  int result = s21_is_greater(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

Suite* suite_s21_is_greater(void) {
  Suite* s = suite_create("suite_greater");
  TCase* tc = tcase_create("tc_greater");

  tcase_add_test(tc, greater_1);
  tcase_add_test(tc, greater_2);
  tcase_add_test(tc, greater_3);
  tcase_add_test(tc, greater_4);
  tcase_add_test(tc, greater_5);
  tcase_add_test(tc, greater_6);
  tcase_add_test(tc, greater_7);
  tcase_add_test(tc, greater_8);
  tcase_add_test(tc, greater_9);
  tcase_add_test(tc, greater_10);
  tcase_add_test(tc, greater_11);
  tcase_add_test(tc, greater_12);
  tcase_add_test(tc, greater_13);
  tcase_add_test(tc, greater_14);
  tcase_add_test(tc, greater_15);

  suite_add_tcase(s, tc);
  return s;
}