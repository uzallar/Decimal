#include "test.h"

START_TEST(not_equal_1) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(not_equal_2) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  set_scale(&value_2, 2);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(not_equal_3) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{456, 0, 0, 0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_4) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, PLUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_5) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_6) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(not_equal_7) {
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  int result2 = s21_is_not_equal(value_3, value_4);
  ck_assert_int_eq(result2, 0);
}
END_TEST

START_TEST(not_equal_8) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, UINT_MAX / 2 + 1}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_9) {
  s21_decimal value_3 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_4 = {{UINT_MAX, 0, 0, 0}};
  int result = s21_is_not_equal(value_3, value_4);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(not_equal_10) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  set_scale(&value_2, 0);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_11) {
  s21_decimal value_3 = {{12345, 0, 0, 0}};
  set_scale(&value_3, 2);
  s21_decimal value_4 = {{12345, 0, 0, 0}};
  set_scale(&value_4, 2);
  int result2 = s21_is_not_equal(value_3, value_4);
  ck_assert_int_eq(result2, 0);
}
END_TEST

START_TEST(not_equal_12) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, PLUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(not_equal_13) {
  s21_decimal value_1 = {{0x3457D829, 0xF89B5A0D, 0xC5E4317, 0x000E0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x5554D320, 0x8235, 0x0, 0x80050000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(not_equal_14) {
  s21_decimal value_1 = {{0x3457D829, 0xF89B5A0D, 0xC5E4317, 0x000E0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(not_equal_15) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_not_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

Suite* suite_s21_is_not_equal(void) {
  Suite* s = suite_create("suite_not_equa");
  TCase* tc = tcase_create("tc_not_equa");

  tcase_add_test(tc, not_equal_1);
  tcase_add_test(tc, not_equal_2);
  tcase_add_test(tc, not_equal_3);
  tcase_add_test(tc, not_equal_4);
  tcase_add_test(tc, not_equal_5);
  tcase_add_test(tc, not_equal_6);
  tcase_add_test(tc, not_equal_7);
  tcase_add_test(tc, not_equal_8);
  tcase_add_test(tc, not_equal_9);
  tcase_add_test(tc, not_equal_10);
  tcase_add_test(tc, not_equal_11);
  tcase_add_test(tc, not_equal_12);
  tcase_add_test(tc, not_equal_13);
  tcase_add_test(tc, not_equal_14);
  tcase_add_test(tc, not_equal_15);

  suite_add_tcase(s, tc);
  return s;
}