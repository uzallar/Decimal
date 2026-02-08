#include "test.h"

START_TEST(float_to_decimal_1) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 123.456f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 123456);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(get_scale(dst), 3);
  ck_assert_int_eq(get_sign(dst), 0);
}
END_TEST

START_TEST(float_to_decimal_2) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = -123.456f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 123456);
  ck_assert_int_eq(get_scale(dst), 3);
  ck_assert_int_eq(get_sign(dst), 1);
}
END_TEST

START_TEST(float_to_decimal_3) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 0.0f;
  int result = s21_from_float_to_decimal(src, &dst);

  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(get_scale(dst), 0);
  ck_assert_int_eq(get_sign(dst), 0);
}
END_TEST

START_TEST(float_to_decimal_5) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = -99999.9999f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 100000);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(float_to_decimal_6) {
  float a = 1.2e-19;
  float b = 0.0;
  int error = 0;
  int func_error = 0;
  s21_decimal dec = {{0}};
  func_error = s21_from_float_to_decimal(a, &dec);
  s21_from_decimal_to_float(dec, &b);
  ck_assert_int_eq(error, func_error);
  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(float_to_decimal_7) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 0.000123f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x00FF0000, 0x00060000);
}
END_TEST

START_TEST(float_to_decimal_8) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = -0.000123f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 123);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x00FF0000, 0x00060000);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(float_to_decimal_9) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 792281625142643375935439503360.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(float_to_decimal_10) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 0.0f / 0.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(float_to_decimal_11) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 1.0f / 0.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(float_to_decimal_12) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = -10000000.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 10000000);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(float_to_decimal_13) {
  s21_decimal dst = {{0, 0, 0, 0}};
  float src = 123456789.0f;
  int result = s21_from_float_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 123456800);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

Suite* suite_s21_float_to_decimal(void) {
  Suite* s = suite_create("suite_float_decimal");
  TCase* tc = tcase_create("tc_float_decimal");

  tcase_add_test(tc, float_to_decimal_1);
  tcase_add_test(tc, float_to_decimal_2);
  tcase_add_test(tc, float_to_decimal_3);
  tcase_add_test(tc, float_to_decimal_5);
  tcase_add_test(tc, float_to_decimal_6);
  tcase_add_test(tc, float_to_decimal_7);
  tcase_add_test(tc, float_to_decimal_8);
  tcase_add_test(tc, float_to_decimal_9);
  tcase_add_test(tc, float_to_decimal_10);
  tcase_add_test(tc, float_to_decimal_11);
  tcase_add_test(tc, float_to_decimal_12);
  tcase_add_test(tc, float_to_decimal_13);

  suite_add_tcase(s, tc);
  return s;
}