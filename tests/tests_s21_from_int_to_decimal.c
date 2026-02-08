#include "test.h"

START_TEST(int_to_decimal_1) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = 12345;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 12345);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(int_to_decimal_2) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = -67890;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 67890);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(int_to_decimal_3) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = 0;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 0);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(int_to_decimal_4) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = INT_MAX;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 2147483647);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(int_to_decimal_5) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = INT_MIN;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 2147483648);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

START_TEST(int_to_decimal_6) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = INT_MAX - 1;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 2147483646);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3], 0);
}
END_TEST

START_TEST(int_to_decimal_7) {
  s21_decimal dst = {{0, 0, 0, 0}};
  int src = INT_MIN + 1;
  int result = s21_from_int_to_decimal(src, &dst);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dst.bits[0], 2147483647);
  ck_assert_int_eq(dst.bits[1], 0);
  ck_assert_int_eq(dst.bits[2], 0);
  ck_assert_int_eq(dst.bits[3] & 0x80000000, 0x80000000);
}
END_TEST

Suite* suite_s21_int_to_decimal(void) {
  Suite* s = suite_create("suite_int_decimal");
  TCase* tc = tcase_create("tc_int_decimal");

  tcase_add_test(tc, int_to_decimal_1);
  tcase_add_test(tc, int_to_decimal_2);
  tcase_add_test(tc, int_to_decimal_3);
  tcase_add_test(tc, int_to_decimal_4);
  tcase_add_test(tc, int_to_decimal_5);
  tcase_add_test(tc, int_to_decimal_6);
  tcase_add_test(tc, int_to_decimal_7);

  suite_add_tcase(s, tc);
  return s;
}