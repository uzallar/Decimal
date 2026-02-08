#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>

#include "../s21_decimal.h"

#define IS_OK 0
#define IS_ERROR 1

Suite *suite_s21_add(void);
Suite *suite_s21_sub(void);
Suite *suite_s21_mul(void);
Suite *suite_s21_div(void);
Suite *suite_s21_is_less(void);
Suite *suite_s21_is_less_or_equal(void);
Suite *suite_s21_is_greater(void);
Suite *suite_s21_is_greater_or_equal(void);
Suite *suite_s21_is_equal(void);
Suite *suite_s21_is_not_equal(void);
Suite *suite_s21_int_to_decimal(void);
Suite *suite_s21_float_to_decimal(void);
Suite *suite_s21_decimal_to_int(void);
Suite *suite_s21_decimal_to_float(void);
Suite *suite_s21_floor(void);
Suite *suite_s21_round(void);
Suite *suite_s21_truncate(void);
Suite *suite_s21_negate(void);

#endif