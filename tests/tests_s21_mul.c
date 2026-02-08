#include "test.h"

START_TEST(mul_1) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal value_1 = {{500, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{3, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_sign(result), PLUS);
  ck_assert_int_eq(result.bits[0], 1500);
}
END_TEST

START_TEST(mul_3) {
  int num1 = -32768;
  int num2 = 2;
  int res_origin = -65536;
  s21_decimal a = {0};
  s21_decimal b = {0};
  s21_from_int_to_decimal(num1, &a);
  s21_from_int_to_decimal(num2, &b);
  s21_decimal res_dec = {0};
  int res_int = 0;
  s21_mul(a, b, &res_dec);
  s21_from_decimal_to_int(res_dec, &res_int);
  ck_assert_int_eq(res_int, res_origin);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 2);
  // ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  set_scale(&value_2, 3);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_scale(result), 5);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal value_1 = {{5, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(mul_8) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(mul_9) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  set_scale(&value_1, 28);
  s21_decimal value_2 = {{0x17FFFFFF, 0x602F7FC3, 0xFCC4D1C3, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {{0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(mul_10) {
  s21_decimal value_1 = {{0x19, 0x0, 0x0, 0}};
  set_scale(&value_1, 25);
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x5, 0x0, 0x0, 0}};
  set_scale(&value_2, 25);
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(mul_11) {
  s21_decimal value_1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  s21_decimal value_2 = {{0x55555555, 0x55555555, 0x55555555, 0}};
  set_scale(&value_2, 21);
  s21_decimal result = {{0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(mul_12) {
  s21_decimal value_1 = {{0x55555555, 0x0, 0x55555555, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x55555555, 0x0, 0x0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0}};
  int status = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

Suite* suite_s21_mul(void) {
  Suite* s = suite_create("suite_mul");
  TCase* tc = tcase_create("tc_mul");

  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);
  tcase_add_test(tc, mul_4);
  tcase_add_test(tc, mul_5);
  tcase_add_test(tc, mul_6);
  tcase_add_test(tc, mul_7);
  tcase_add_test(tc, mul_8);
  tcase_add_test(tc, mul_9);
  tcase_add_test(tc, mul_10);
  tcase_add_test(tc, mul_11);
  tcase_add_test(tc, mul_12);

  suite_add_tcase(s, tc);
  return s;
}