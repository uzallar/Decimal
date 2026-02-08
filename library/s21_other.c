#include "../s21_decimal.h"

int handle_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal int_part = {0};
  s21_decimal frac_part = {0};
  int status = get_int_frac_part(value, &int_part, &frac_part);
  if (status == 0) {
    int sign = get_sign(value);
    if (sign && !is_zero(frac_part)) {
      s21_decimal one = {{1, 0, 0, 0}};
      status = s21_sub(int_part, one, result);
    } else {
      *result = int_part;
    }
  }
  return status;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = 1;
  if (result != NULL && correct_value(&value)) {
    if (is_zero(value)) {
      *result = (s21_decimal){{0, 0, 0, 0}};
      status = 0;
    } else {
      status = handle_floor(value, result);
    }
    set_sign(result, get_sign(value));
  }
  return status;
}

int handle_round(s21_decimal value, s21_decimal *result) {
  s21_decimal int_part = {0};
  s21_decimal frac_part = {0};
  int status = get_int_frac_part(value, &int_part, &frac_part);
  if (status == 0) {
    int sign = get_sign(value);
    s21_decimal compare = {{5, 0, 0, 0x00010000}};
    s21_decimal one = {{1, 0, 0, 0}};
    s21_decimal abs_frac_part = frac_part;
    set_sign(&abs_frac_part, 0);
    if (s21_is_greater_or_equal(abs_frac_part, compare)) {
      status = sign ? s21_sub(int_part, one, result)
                    : s21_add(int_part, one, result);
    } else {
      *result = int_part;
    }
  }
  return status;
}
int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 1;
  if (result != NULL && correct_value(&value)) {
    if (is_zero(value)) {
      *result = (s21_decimal){{0, 0, 0, 0}};
      status = 0;
    } else {
      status = handle_round(value, result);
    }
    set_sign(result, get_sign(value));
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 1;
  if (result != NULL && correct_value(&value)) {
    if (is_zero(value)) {
      *result = (s21_decimal){{0, 0, 0, 0}};
      set_sign(result, get_sign(value));
      status = 0;
    } else {
      int scale = get_scale(value);
      *result = value;
      for (int i = 0; i < scale; i++) {
        s21_div10(result);
      }
      set_scale(result, 0);
      status = 0;
    }
  }
  return status;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 1;
  if (result != NULL && correct_value(&value)) {
    *result = value;
    set_sign(result, !get_sign(value));
    status = 0;
  }
  return status;
}

int correct_value(s21_decimal *value) {
  return (get_scale(*value) <= 28 && !(value->bits[3] & (0x7F00FFFF)));
}

int s21_div10(s21_decimal *value) {
  int mod_10 = 0;
  for (int i = 2; i >= 0; i--) {
    long long tmp = mod_10 * pow(2, 32) + (unsigned)value->bits[i];
    mod_10 = tmp % 10;
    value->bits[i] = tmp / 10;
  }
  return mod_10;
}

int get_int_frac_part(s21_decimal value, s21_decimal *int_part,
                      s21_decimal *frac_part) {
  int status = 1;
  if (int_part != NULL && frac_part != NULL) {
    status = s21_truncate(value, int_part);
    if (status == 0) {
      status = s21_sub(value, *int_part, frac_part);
    }
  }
  return status;
}