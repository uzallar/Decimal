#include "test.h"

START_TEST(round_1) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(round_2) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  set_scale(&value_1, 5);
  s21_decimal check = {{75, 0, 0, 0}};
  set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(round_3) {
  s21_decimal value = {{UINT_MAX, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], UINT_MAX);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(round_4) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_sign(&value, MINUS);
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_sign(result), MINUS);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(round_5) {
  s21_decimal value = {{123, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(round_6) {
  s21_decimal value = {{123456789, 0, 0, 0}};
  set_scale(&value, 8);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(round_7) {
  s21_decimal val = {{7, 7, 7, 0}};
  set_sign(&val, MINUS);
  s21_decimal res = {{0}};
  set_scale(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(round_8) {
  s21_decimal src1, origin;
  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(round_9) {
  s21_decimal src1, origin;
  src1.bits[0] = 0b00000000000000000000100110001000;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_round(src1, &result);
  origin.bits[0] = 0b00000000000000000000000000011000;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(round_10) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_round(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(round_11) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x001B0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_round(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}

START_TEST(round_12) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;
  int status = s21_round(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(round_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_round(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(round_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x9999999A, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_round(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

Suite* suite_s21_round(void) {
  Suite* s = suite_create("suite_round");
  TCase* tc = tcase_create("tc_round");

  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);
  tcase_add_test(tc, round_5);
  tcase_add_test(tc, round_6);
  tcase_add_test(tc, round_7);
  tcase_add_test(tc, round_8);
  tcase_add_test(tc, round_9);
  tcase_add_test(tc, round_10);
  tcase_add_test(tc, round_11);
  tcase_add_test(tc, round_12);
  tcase_add_test(tc, round_13);
  tcase_add_test(tc, round_14);

  suite_add_tcase(s, tc);
  return s;
}