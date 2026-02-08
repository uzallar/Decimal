#include "test.h"

START_TEST(div_1) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(div_2) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
}
END_TEST

START_TEST(div_3) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(div_4) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{100, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{10, 0, 0, 0}};
  set_scale(&value_2, 1);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_scale(result), 1);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  set_scale(&value_1, 28);
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 28);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(div_9) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{2, 0, 0, 0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), PLUS);
}
END_TEST

START_TEST(div_10) {
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  set_scale(&decimal1, 28);
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  set_scale(&decimal2, 28);
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(decimal1, decimal2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_11) {
  s21_decimal value_1 = {{0x2, 0x0, 0x0, 0x0}};
  s21_decimal value_2 = {{0x0, 0x0, 0x80000000, 0x0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(div_12) {
  s21_decimal value_1 = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFE, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(div_13) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
}
END_TEST

START_TEST(div_14) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  set_sign(&value_2, MINUS);
  s21_decimal result = {{0x0, 0x0, 0x0, 0x0}};
  int status = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_sign(result), MINUS);
}
END_TEST

Suite* suite_s21_div(void) {
  Suite* s = suite_create("suite_div");
  TCase* tc = tcase_create("tc_div");

  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);
  tcase_add_test(tc, div_3);
  tcase_add_test(tc, div_4);
  tcase_add_test(tc, div_5);
  tcase_add_test(tc, div_6);
  tcase_add_test(tc, div_7);
  tcase_add_test(tc, div_8);
  tcase_add_test(tc, div_9);
  tcase_add_test(tc, div_10);
  tcase_add_test(tc, div_11);
  tcase_add_test(tc, div_12);
  tcase_add_test(tc, div_13);
  tcase_add_test(tc, div_14);

  suite_add_tcase(s, tc);
  return s;
}