#include "test.h"

START_TEST(decimal_to_int_1) {
  s21_decimal src = {{123, 0, 0, 0}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 123);
}
END_TEST

START_TEST(decimal_to_int_2) {
  s21_decimal src = {{123, 0, 0, 0x80000000}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, -123);
}
END_TEST

START_TEST(decimal_to_int_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 0);
}
END_TEST

START_TEST(decimal_to_int_4) {
  s21_decimal src = {{2147483647, 0, 0, 0}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, INT_MAX);
}
END_TEST

START_TEST(decimal_to_int_5) {
  s21_decimal src1;
  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  int result = 0;
  int* res = &result;
  s21_from_decimal_to_int(src1, res);
  ck_assert_int_eq(result, -3);
}
END_TEST

START_TEST(decimal_to_int_6) {
  s21_decimal src = {{2147483648, 0, 0, 0}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(decimal_to_int_7) {
  s21_decimal src = {{2147483649, 0, 0, 0x80000000}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(decimal_to_int_8) {
  s21_decimal src = {{0}};
  int result = 0, number = 0;
  src.bits[0] = UINT_MAX;
  src.bits[1] = UINT_MAX;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(decimal_to_int_9) {
  s21_decimal src = {{123, 0, 0, 0x00070000}};
  int dst = 0;
  int result = s21_from_decimal_to_int(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst, 0);
}
END_TEST

Suite* suite_s21_decimal_to_int(void) {
  Suite* s = suite_create("suite_decimal_int");
  TCase* tc = tcase_create("tc_decimal_int");

  tcase_add_test(tc, decimal_to_int_1);
  tcase_add_test(tc, decimal_to_int_2);
  tcase_add_test(tc, decimal_to_int_3);
  tcase_add_test(tc, decimal_to_int_4);
  tcase_add_test(tc, decimal_to_int_5);
  tcase_add_test(tc, decimal_to_int_6);
  tcase_add_test(tc, decimal_to_int_7);
  tcase_add_test(tc, decimal_to_int_8);
  tcase_add_test(tc, decimal_to_int_9);

  suite_add_tcase(s, tc);
  return s;
}