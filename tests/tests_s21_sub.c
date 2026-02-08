#include "test.h"

START_TEST(sub_1) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  set_scale(&value_1, 28);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal value_1 = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{4, 0, 0, 0}};
  s21_decimal result = {{0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_scale(result), 2);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal src1 = {0}, src2 = {0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin = {0};
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_decimal result_our = {0};
  s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal c = {{100, 0, 0, 0}};
  s21_decimal d = {{5, 0, 0, 0}};
  s21_decimal etalon = {{5, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};
  s21_decimal* p_res = &res;
  int add = s21_sub(c, d, p_res);
  ck_assert_int_eq(add, 0);
  int equal = s21_is_equal(res, etalon);
  ck_assert_int_eq(equal, 0);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(sub_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  set_sign(&value_2, MINUS);
  set_scale(&value_2, 21);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal value_1 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  s21_decimal value_2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(sub_12) {
  s21_decimal value_1 = {{0x9999999B, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x99999999, 0x99999999, 0x19999999, 0x00000000}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_sub(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(get_sign(result), MINUS);
}

Suite* suite_s21_sub(void) {
  Suite* s = suite_create("suite_sub");
  TCase* tc = tcase_create("tc_sub");

  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);
  tcase_add_test(tc, sub_4);
  tcase_add_test(tc, sub_5);
  tcase_add_test(tc, sub_6);
  tcase_add_test(tc, sub_7);
  tcase_add_test(tc, sub_8);
  tcase_add_test(tc, sub_9);
  tcase_add_test(tc, sub_10);
  tcase_add_test(tc, sub_11);
  tcase_add_test(tc, sub_12);

  suite_add_tcase(s, tc);
  return s;
}