#include "test.h"

START_TEST(less_1) {
  s21_decimal value_1 = {{456, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_2) {
  s21_decimal value_1 = {{789, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_3) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  s21_decimal value_2 = {{123, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_4) {
  s21_decimal value_3 = {{0, 0, 0, 0}};
  s21_decimal value_4 = {{0, 0, 0, 0}};
  int result2 = s21_is_less(value_3, value_4);
  ck_assert_int_eq(result2, FALSE);
}
END_TEST

START_TEST(less_5) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, PLUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_6) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_7) {
  s21_decimal value_1 = {{456, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_8) {
  s21_decimal value_1 = {{123, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{456, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_9) {
  s21_decimal value_1 = {{0, 0, 0, UINT_MAX / 2 + 1}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{UINT_MAX, 0, 0, 0}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(less_10) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{123, 0, 0, 0}};
  set_scale(&value_2, 0);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(less_11) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0xE0000}};
  s21_decimal value_2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(less_12) {
  s21_decimal value_1 = {{0x1, 0x0, 0x0, 0x1C0000}};
  s21_decimal value_2 = {{0x9B10D401, 0x8F08DC74, 0xB4D8B8B7, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(less_13) {
  s21_decimal value_1 = {{0x1, 0x0, 0x0, 0}};
  set_scale(&value_1, 28);
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(less_14) {
  s21_decimal value_1 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x00000000}};
  set_scale(&value_1, 1);
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x9B10D401, 0x8F08DC74, 0xB4D8B8B7, 0x00000000}};
  set_sign(&value_2, MINUS);
  set_scale(&value_2, 10);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(less_15) {
  s21_decimal value_1 = {{0x9B10D401, 0x8F08DC74, 0xB4D8B8B7, 0x00000000}};
  set_sign(&value_1, MINUS);
  set_scale(&value_1, 10);
  s21_decimal value_2 = {{0x99999999, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_less(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

Suite* suite_s21_is_less(void) {
  Suite* s = suite_create("suite_less");
  TCase* tc = tcase_create("tc_less");

  tcase_add_test(tc, less_1);
  tcase_add_test(tc, less_2);
  tcase_add_test(tc, less_3);
  tcase_add_test(tc, less_4);
  tcase_add_test(tc, less_5);
  tcase_add_test(tc, less_6);
  tcase_add_test(tc, less_7);
  tcase_add_test(tc, less_8);
  tcase_add_test(tc, less_9);
  tcase_add_test(tc, less_10);
  tcase_add_test(tc, less_11);
  tcase_add_test(tc, less_12);
  tcase_add_test(tc, less_13);
  tcase_add_test(tc, less_14);
  tcase_add_test(tc, less_15);

  suite_add_tcase(s, tc);
  return s;
}