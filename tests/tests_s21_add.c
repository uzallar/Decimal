#include "test.h"

START_TEST(add_1) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(add_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  set_scale(&value_1, 28);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(add_3) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{15, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(add_4) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(1, s21_add(value_1, value_2, &result));
}
END_TEST

START_TEST(add_5) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{4, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0}};
  ck_assert_int_eq(2, s21_add(value_1, value_2, &result));
}
END_TEST

START_TEST(add_6) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(add_7) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_scale(result), 2);
}
END_TEST

START_TEST(add_8) {
  s21_decimal src1 = {{0}};
  s21_decimal src2 = {{0}};
  int num1 = -1234;
  float num2 = -1.234;
  float res_origin = -1235.234;
  s21_from_int_to_decimal(num1, &src1);
  s21_from_float_to_decimal(num2, &src2);
  s21_decimal res_dec = {0};
  float res_float = 0.0;
  s21_add(src1, src2, &res_dec);
  s21_from_decimal_to_float(res_dec, &res_float);
  ck_assert_float_eq(res_float, res_origin);
}
END_TEST

START_TEST(add_9) {
  s21_decimal value_1 = {{3, 1, 3, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{5, 4, 8, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(result.bits[1], 3);
  ck_assert_int_eq(result.bits[2], 5);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(add_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(add_11) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(add_12) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0x9999999A, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

Suite* suite_s21_add(void) {
  Suite* s = suite_create("suite_add");
  TCase* tc = tcase_create("tc_add");

  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);
  tcase_add_test(tc, add_3);
  tcase_add_test(tc, add_4);
  tcase_add_test(tc, add_5);
  tcase_add_test(tc, add_6);
  tcase_add_test(tc, add_7);
  tcase_add_test(tc, add_8);
  tcase_add_test(tc, add_9);
  tcase_add_test(tc, add_10);
  tcase_add_test(tc, add_11);
  tcase_add_test(tc, add_12);

  suite_add_tcase(s, tc);
  return s;
}