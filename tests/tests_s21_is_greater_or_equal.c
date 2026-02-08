#include "test.h"

START_TEST(greater_or_equal_1) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{6789, 0, 0, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_or_equal_2) {
  s21_decimal value_1 = {{6789, 0, 0, 0}};
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_or_equal_3) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_or_equal_4) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_or_equal_5) {
  s21_decimal value_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal value_2 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_or_equal_6) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{5789, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_or_equal_7) {
  s21_decimal value_1 = {{0, 0, 0, 0xFFFFFFFF}};
  s21_decimal value_2 = {{0, 0, 0, 0xFFFFFFFF}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(greater_or_equal_8) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{1234500, 0, 0, 0}};
  set_scale(&value_2, 4);
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_or_equal_9) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{12344, 0, 0, 0}};
  set_scale(&value_2, 2);
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(greater_or_equal_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(greater_or_equal_11) {
  s21_decimal value_1 = {{0xDB6476FA, 0x9C33420F, 0xA78F3B0F, 0x110000}};
  s21_decimal value_2 = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(greater_or_equal_12) {
  s21_decimal value_1 = {{0x5554D320, 0x8235, 0x0, 0x50000}};
  s21_decimal value_2 = {{0x8A5D3486, 0x8A87F668, 0xED66924A, 0x00070000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(greater_or_equal_13) {
  s21_decimal value_1 = {{0x5554D320, 0x8235, 0x0, 0x00050000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};
  int result = s21_is_greater_or_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

Suite* suite_s21_is_greater_or_equal(void) {
  Suite* s = suite_create("suite_greater_or_equal");
  TCase* tc = tcase_create("tc_greater_or_equal");

  tcase_add_test(tc, greater_or_equal_1);
  tcase_add_test(tc, greater_or_equal_2);
  tcase_add_test(tc, greater_or_equal_3);
  tcase_add_test(tc, greater_or_equal_4);
  tcase_add_test(tc, greater_or_equal_5);
  tcase_add_test(tc, greater_or_equal_6);
  tcase_add_test(tc, greater_or_equal_7);
  tcase_add_test(tc, greater_or_equal_8);
  tcase_add_test(tc, greater_or_equal_9);
  tcase_add_test(tc, greater_or_equal_10);
  tcase_add_test(tc, greater_or_equal_11);
  tcase_add_test(tc, greater_or_equal_12);
  tcase_add_test(tc, greater_or_equal_13);

  suite_add_tcase(s, tc);
  return s;
}