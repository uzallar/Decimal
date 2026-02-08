#include "../s21_decimal.h"

int s21_is_less(s21_decimal number_1, s21_decimal number_2) {
  int result = FALSE;
  if (is_correct_decimal(number_1) && is_correct_decimal(number_2)) {
    result = (comparison_two_decimal(number_1, number_2) == -1);
  }
  return result;
}

int s21_is_less_or_equal(s21_decimal number_1, s21_decimal number_2) {
  int result = FALSE;
  if (is_correct_decimal(number_1) && is_correct_decimal(number_2)) {
    int temp = comparison_two_decimal(number_1, number_2);
    result = (temp == -1 || temp == 0);
  }
  return result;
}

int s21_is_greater(s21_decimal number_1, s21_decimal number_2) {
  int result = FALSE;
  if (is_correct_decimal(number_1) && is_correct_decimal(number_2)) {
    result = (comparison_two_decimal(number_1, number_2) == 1);
  }
  return result;
}

int s21_is_greater_or_equal(s21_decimal number_1, s21_decimal number_2) {
  int result = FALSE;
  if (is_correct_decimal(number_1) && is_correct_decimal(number_2)) {
    int temp = comparison_two_decimal(number_1, number_2);
    result = (temp == 1 || temp == 0);
  }
  return result;
}

int s21_is_equal(s21_decimal number_1, s21_decimal number_2) {
  int result = FALSE;
  if (is_correct_decimal(number_1) && is_correct_decimal(number_2)) {
    result = (comparison_two_decimal(number_1, number_2) == 0);
  }
  return result;
}

int s21_is_not_equal(s21_decimal number_1, s21_decimal number_2) {
  return !s21_is_equal(number_1, number_2);
}

int comparison_two_decimal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int sign_value_1 = get_sign(value_1);
  int sign_value_2 = get_sign(value_2);
  int is_sign_equal = (sign_value_1 == sign_value_2);
  s21_big_decimal big_val_1 = {0};
  s21_big_decimal big_val_2 = {0};
  convert_to_big_decimal(value_1, &big_val_1);
  convert_to_big_decimal(value_2, &big_val_2);
  normalization(&big_val_1, &big_val_2);
  if (is_big_zero(big_val_1) && is_big_zero(big_val_2)) {
    result = 0;
  } else if (!is_sign_equal) {
    result = (sign_value_1 == 0) ? 1 : -1;
  } else {
    result = comparison_big_mantissa(big_val_1, big_val_2);
    if (sign_value_1) {
      if (result == 1)
        result = -1;
      else if (result == -1)
        result = 1;
    }
  }
  return result;
}