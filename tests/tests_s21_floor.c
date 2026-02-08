#include "test.h"

START_TEST(floor_1) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal value = {{UINT_MAX, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], UINT_MAX);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal src1;
  src1.bits[0] = 0b00001111111111111111111111111111;
  src1.bits[1] = 0b00111110001001010000001001100001;
  src1.bits[2] = 0b00100000010011111100111001011110;
  src1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res_od = {0};
  s21_floor(src1, &res_od);
  s21_decimal result = {0};
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res_od.bits[0], result.bits[0]);
  ck_assert_float_eq(res_od.bits[1], result.bits[1]);
  ck_assert_float_eq(res_od.bits[2], result.bits[2]);
  ck_assert_float_eq(res_od.bits[3], result.bits[3]);
}
END_TEST

START_TEST(floor_4) {
  s21_decimal value = {{123, 0, 0, 0}};
  set_scale(&value, 0);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_5) {
  s21_decimal value = {{12399, 0, 0, 0}};
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_6) {
  s21_decimal value = {{12345, 0, 0, 0}};
  set_sign(&value, MINUS);
  set_scale(&value, 2);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 124);
  ck_assert_int_eq(get_sign(result), MINUS);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_sign(&val, MINUS);
  s21_decimal res = {{0}};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_8) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  set_scale(&value_1, 5);
  set_sign(&value_1, 1);
  s21_decimal check = {{75, 0, 0, 0}};
  set_sign(&check, 1);
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(floor_9) {
  s21_decimal val = {{2, 0, 0, 0}};
  set_sign(&val, MINUS);
  s21_decimal res = {{0}};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(floor_10) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_floor(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(floor_11) {
  s21_decimal value_1 = {{0x0, 0x0, 0x0, 0x001B0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x0, 0x0, 0x0, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_floor(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}

START_TEST(floor_12) {
  s21_decimal value = {{-1, 0, 0, 0x1D0000}};
  s21_decimal result;
  int status = s21_floor(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(floor_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_floor(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

START_TEST(floor_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  set_scale(&value_1, 1);
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x9999999A, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {0};
  int status = s21_floor(value_1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
  ck_assert_int_eq(get_sign(result), get_sign(value_2));
}
END_TEST

Suite* suite_s21_floor(void) {
  Suite* s = suite_create("suite_floor");
  TCase* tc = tcase_create("tc_floor");

  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);
  tcase_add_test(tc, floor_8);
  tcase_add_test(tc, floor_9);
  tcase_add_test(tc, floor_10);
  tcase_add_test(tc, floor_11);
  tcase_add_test(tc, floor_12);
  tcase_add_test(tc, floor_13);
  tcase_add_test(tc, floor_14);

  suite_add_tcase(s, tc);
  return s;
}