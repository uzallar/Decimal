#include "test.h"

START_TEST(less_or_equal_1) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{456, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_2) {
  s21_decimal value_1 = {{456, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_or_equal_3) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_4) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, PLUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_or_equal_5) {
  s21_decimal value_1 = {{456, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_6) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_or_equal_7) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_8) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_9) {
  s21_decimal value_3 = {{123, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_or_equal_10) {
  s21_decimal value_5 = {{0, 0, 0, 0}};
  s21_decimal value_6 = {{0, 0, 0, 0}};
  int result = s21_is_less_or_equal(value_5, value_6);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_11) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  set_scale(&value_2, 0);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_12) {
  s21_decimal value_3 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, UINT_MAX / 2 + 1}};
  set_sign(&value_4, MINUS);
  int result = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_or_equal_13) {
  s21_decimal value_3 = {{12345, 0, 0, 0}};
  set_scale(&value_3, 2);
  s21_decimal value_4 = {{124, 0, 0, 0}};
  set_scale(&value_4, 0);
  int result = s21_is_less_or_equal(value_3, value_4);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_or_equal_14) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0xE0000}};
  s21_decimal value_2 = {{0xCE5807BC, 0xF2D773B6, 0x4DB98FD2, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(less_or_equal_15) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0xE0000}};
  s21_decimal value_2 = {{0xE333C1D3, 0xC173E715, 0x631797E3, 0xF0000}};
  int result = s21_is_less_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

Suite* suite_s21_is_less_or_equal(void) {
  Suite* s = suite_create("suite_less_or_equal");
  TCase* tc = tcase_create("tc_less_or_equal");

  tcase_add_test(tc, less_or_equal_1);
  tcase_add_test(tc, less_or_equal_2);
  tcase_add_test(tc, less_or_equal_3);
  tcase_add_test(tc, less_or_equal_4);
  tcase_add_test(tc, less_or_equal_5);
  tcase_add_test(tc, less_or_equal_6);
  tcase_add_test(tc, less_or_equal_7);
  tcase_add_test(tc, less_or_equal_8);
  tcase_add_test(tc, less_or_equal_9);
  tcase_add_test(tc, less_or_equal_10);
  tcase_add_test(tc, less_or_equal_11);
  tcase_add_test(tc, less_or_equal_12);
  tcase_add_test(tc, less_or_equal_13);
  tcase_add_test(tc, less_or_equal_14);
  tcase_add_test(tc, less_or_equal_15);

  suite_add_tcase(s, tc);
  return s;
}