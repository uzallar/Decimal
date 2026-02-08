#include "test.h"

START_TEST(equal_1) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(equal_2) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{67890, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(equal_3) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_scale(&value_1, 2);
  s21_decimal value_2 = {{1234500, 0, 0, 0}};
  set_scale(&value_2, 4);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(equal_4) {
  s21_decimal value_1 = {{0, 0, 0, 0xFFFFFFFF}};
  s21_decimal value_2 = {{0, 0, 0, 0xFFFFFFFF}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(equal_5) {
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(equal_6) {
  s21_decimal value_1 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  s21_decimal value_2 = {{UINT32_MAX, UINT32_MAX, UINT32_MAX, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(equal_7) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  set_sign(&value_2, 1);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}
END_TEST

START_TEST(equal_8) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{12345, 0, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(equal_9) {
  s21_decimal value_1 = {{12345, 0, 0, 0}};
  s21_decimal value_2 = {{12345, 1, 0, 0}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}
END_TEST

START_TEST(equal_10) {
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal value_2 = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(equal_11) {
  s21_decimal value_1 = {{0xC833FFFF, 0x8881186E, 0x4A03CE6, 0x00120000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x11111111, 0x11111111, 0x11111111, 0x00000000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(equal_12) {
  s21_decimal value_1 = {{0x48D7710D, 0x279AE1C0, 0x4329DD25, 0xF0000}};
  s21_decimal value_2 = {{0xAAAAAAAB, 0xAAAAAAAA, 0x0, 0x00130000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, FALSE);
}

START_TEST(equal_13) {
  s21_decimal value_1 = {{0x48D7710D, 0x279AE1C0, 0x4329DD25, 0xF0000}};
  s21_decimal value_2 = {{0x48D7710D, 0x279AE1C0, 0x4329DD25, 0xF0000}};
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

START_TEST(equal_14) {
  s21_decimal value_1 = {{0x48D7710D, 0x279AE1C0, 0x4329DD25, 0x000F0000}};
  set_sign(&value_1, MINUS);
  s21_decimal value_2 = {{0x48D7710D, 0x279AE1C0, 0x4329DD25, 0x000F0000}};
  set_sign(&value_2, MINUS);
  int result = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(result, TRUE);
}

Suite* suite_s21_is_equal(void) {
  Suite* s = suite_create("suite_equal");
  TCase* tc = tcase_create("tc_equal");

  tcase_add_test(tc, equal_1);
  tcase_add_test(tc, equal_2);
  tcase_add_test(tc, equal_3);
  tcase_add_test(tc, equal_4);
  tcase_add_test(tc, equal_5);
  tcase_add_test(tc, equal_6);
  tcase_add_test(tc, equal_7);
  tcase_add_test(tc, equal_8);
  tcase_add_test(tc, equal_9);
  tcase_add_test(tc, equal_10);
  tcase_add_test(tc, equal_11);
  tcase_add_test(tc, equal_12);
  tcase_add_test(tc, equal_13);
  tcase_add_test(tc, equal_14);

  suite_add_tcase(s, tc);
  return s;
}