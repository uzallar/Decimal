#include "test.h"

START_TEST(truncate_1) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_2) {
  s21_decimal value = {{12399, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_3) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_scale(&value, 2);
  set_sign(&value, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_sign(result), MINUS);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_4) {
  s21_decimal value = {{0, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {0};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_5) {
  s21_decimal value = {{123, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {0};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_6) {
  s21_decimal value = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  set_scale(&value, 5);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value = {{123, 0, 0, 0}};
  set_scale(&value, 2);
  set_sign(&value, MINUS);
  s21_decimal result = {0};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), MINUS);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal value = {{123, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(truncate_9) {
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  set_scale(&value_1, 3);
  set_sign(&value_1, 1);
  s21_decimal check = {{123, 0, 0, 0}};
  set_sign(&check, 1);
  s21_truncate(value_1, &value_1);
  ck_assert_int_eq(s21_is_equal(value_1, check), 1);
}
END_TEST

START_TEST(truncate_10) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_scale(&value, 29);
  s21_decimal result = {0};
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(truncate_11) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_truncate(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(truncate_12) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x001B0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_truncate(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}

START_TEST(truncate_13) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;
  int status = s21_truncate(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(truncate_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_truncate(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(truncate_15) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  set_scale(&value_1, 1);
  s21_decimal value_2 = {{0x99999999, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_truncate(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

Suite* suite_s21_truncate(void) {
  Suite* s = suite_create("suite_truncate");
  TCase* tc = tcase_create("tc_truncate");

  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);
  tcase_add_test(tc, truncate_9);
  tcase_add_test(tc, truncate_10);
  tcase_add_test(tc, truncate_11);
  tcase_add_test(tc, truncate_12);
  tcase_add_test(tc, truncate_13);
  tcase_add_test(tc, truncate_14);
  tcase_add_test(tc, truncate_15);

  suite_add_tcase(s, tc);
  return s;
}