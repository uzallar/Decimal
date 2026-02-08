#include "test.h"

START_TEST(negate_0) {
  s21_decimal val = {{0, 0, 0, 0}};
  set_sign(&val, MINUS);
  s21_decimal res = {{0}};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_sign(&val, MINUS);
  s21_decimal res;
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal value = {{456, 0, 0, 0}};
  set_sign(&value, PLUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 456);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal val = {{0}};
  s21_decimal res = {{0}};
  int sign_before = get_sign(val);
  s21_negate(val, &res);
  int sign_after = get_sign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal value = {{123456, 0, 0, 0}};
  set_scale(&value, 5);
  s21_decimal result = {0};
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_scale(result), 5);
}
END_TEST

START_TEST(negate_5) {
  s21_decimal value = {{UINT_MAX, 0, 0, 0}};
  set_sign(&value, PLUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], UINT_MAX);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(negate_6) {
  s21_decimal value = {{0, 0, 0, 0}};
  set_sign(&value, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(negate_7) {
  s21_decimal value = {{0, 0, 0, 0xFFFFFFFF}};
  s21_decimal result = {0};
  int status = s21_negate(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(negate_8) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal value_2 = {{1, 1, 1, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_9) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_10) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int status = s21_negate(decimal, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

Suite* suite_s21_negate(void) {
  Suite* s = suite_create("suite_negate");
  TCase* tc = tcase_create("tc_negate");

  tcase_add_test(tc, negate_0);
  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  tcase_add_test(tc, negate_7);
  tcase_add_test(tc, negate_8);
  tcase_add_test(tc, negate_9);
  tcase_add_test(tc, negate_10);

  suite_add_tcase(s, tc);
  return s;
}