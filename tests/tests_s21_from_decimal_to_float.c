#include "test.h"

START_TEST(decimal_to_float_1) {
  s21_decimal src = {{123456, 0, 0, 0x00050000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, 1.23456f, 0.000001f);
}
END_TEST

START_TEST(decimal_to_float_2) {
  s21_decimal src = {{123456, 0, 0, 0x80030000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, -123.456f, 0.001f);
}
END_TEST

START_TEST(decimal_to_float_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, 0.0f, 0.001f);
}
END_TEST

START_TEST(decimal_to_float_4) {
  s21_decimal src = {{123000, 0, 0, 0x00030000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, 123.0f, 0.001f);
}
END_TEST

START_TEST(decimal_to_float_5) {
  s21_decimal src = {{INT_MIN, 0, 0, 0x80000000}};
  float dst = 0.0f;
  float exp = (float)INT_MIN;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, exp, 0.00000000000000001f);
}
END_TEST

START_TEST(decimal_to_float_6) {
  s21_decimal src = {0};
  int result = 0;
  float number = 0.0;
  src.bits[0] = 23450987;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 2147745792;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(decimal_to_float_7) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  set_scale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float* dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(decimal_to_float_8) {
  s21_decimal src = {{999999999, 0, 0, 0x00090000}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, 0.999999999f, 0.000000001f);
}
END_TEST

START_TEST(decimal_to_float_9) {
  s21_decimal src = {{123, 0, 0, 0}};
  float dst = 0.0f;
  int result = s21_from_decimal_to_float(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_double_eq_tol(dst, 123.0f, 0.001f);
}
END_TEST

START_TEST(decimal_to_float_10) {
  s21_decimal src = {{123, 0, 0, 0}};
  float* dst = NULL;
  int result = s21_from_decimal_to_float(src, dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite* suite_s21_decimal_to_float(void) {
  Suite* s = suite_create("suite_decimal_float");
  TCase* tc = tcase_create("tc_decimal_float");

  tcase_add_test(tc, decimal_to_float_1);
  tcase_add_test(tc, decimal_to_float_2);
  tcase_add_test(tc, decimal_to_float_3);
  tcase_add_test(tc, decimal_to_float_4);
  tcase_add_test(tc, decimal_to_float_5);
  tcase_add_test(tc, decimal_to_float_6);
  tcase_add_test(tc, decimal_to_float_7);
  tcase_add_test(tc, decimal_to_float_8);
  tcase_add_test(tc, decimal_to_float_9);
  tcase_add_test(tc, decimal_to_float_10);

  suite_add_tcase(s, tc);
  return s;
}
