#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int result = 0;
  if (dst == NULL) result = 1;
  if (result == 0) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    if (src < 0) {
      dst->bits[3] = 1u << 31;
      src *= -1;
    }
    dst->bits[0] = src;
  }
  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int result = 0;
  if (dst == NULL || !is_correct_decimal(src)) {
    result = 1;
  } else {
    s21_decimal intermediate_value = src;
    s21_truncate(src, &intermediate_value);
    set_scale(&intermediate_value, 0);
    if ((intermediate_value.bits[1] != 0 || intermediate_value.bits[2] != 0 ||
         intermediate_value.bits[0] > 2147483648 ||
         (intermediate_value.bits[0] == 2147483648 &&
          intermediate_value.bits[3] != 2147483648))) {
      result = 1;
      *dst = 0;
    } else {
      *dst = intermediate_value.bits[0];
      if (get_sign(src) == 1) *dst = -(*dst);
    }
  }
  return result;
}

int is_correct_decimal(s21_decimal value) {
  int result = 1;
  if (!(((value.bits[3] & 65535) == 0) &&
        ((value.bits[3] & 2130706432) == 0)) ||
      get_scale(value) > 28) {
    result = 0;
  }
  return result;
}

int from_char_to_7_symbol_int(char *arr, float src, int *insignificant_zero) {
  int result = 0, count_int_part = 0;
  if (arr == NULL) {
    result = -1;
  } else {
    int int_part = (int)src;
    while (int_part > 0) {
      count_int_part += 1;
      int_part /= 10;
    }
    int is_unzero_digit = 0;
    for (int i = 6; i >= count_int_part; i--) {
      if (arr[i] == '0' && !is_unzero_digit)
        *insignificant_zero += 1;
      else if (arr[i] != '0') {
        is_unzero_digit = 1;
      }
    }
    int digit = 1;
    for (int i = 6 - *insignificant_zero; i >= 0; i--) {
      result += (arr[i] - '0') * digit;
      digit *= 10;
    }
  }
  return result;
}

void decimal_mul_ten(s21_decimal *dst) {
  s21_decimal decimal_value = {0}, decimal_value1 = {0};
  decimal_value.bits[0] = 10;
  decimal_value.bits[1] = 0;
  decimal_value.bits[2] = 0;
  decimal_value.bits[3] = 0;
  decimal_value1.bits[0] = dst->bits[0];
  decimal_value1.bits[1] = dst->bits[1];
  decimal_value1.bits[2] = dst->bits[2];
  decimal_value1.bits[3] = dst->bits[3];
  s21_mul(decimal_value, decimal_value1, dst);
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0, sign = 0, scale = 0;
  if (src < 0.0) {
    src = -src;
    sign = 1;
  }
  if (src > 79228162514264337593543950335.0f || (src != 0 && src < 1e-28) ||
      isnan(src))
    result = 1;
  if (dst == NULL) result = 1;
  if (result == 0) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    char buffer[13] = {0};
    sprintf(buffer, "%e", src);
    char mantisa[8] = {0};
    int j = 0;
    for (int i = 0; i < 13; i++) {
      if (buffer[i] == 'e') {
        i = 13;
      } else if (buffer[i] >= '0' && buffer[i] <= '9') {
        mantisa[j] = buffer[i];
        j++;
      }
    }
    int insignificant_zero = 0,
        int_part = from_char_to_7_symbol_int(mantisa, src, &insignificant_zero);
    scale = (buffer[10] - '0') * 10 + (buffer[11] - '0');
    s21_from_int_to_decimal(int_part, dst);
    if (buffer[9] == '+' && (scale <= 6 - insignificant_zero))
      scale = 6 - insignificant_zero - scale;
    else if (buffer[9] == '+') {
      for (int i = 0; i < scale - 6 - (insignificant_zero); i++) {
        decimal_mul_ten(dst);
      }
      scale = 0;
    } else if (buffer[9] == '-')
      scale = scale - insignificant_zero + 6;
    set_scale(dst, scale);
    set_sign(dst, sign);
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result = 0;
  if (dst == NULL || !is_correct_decimal(src)) {
    result = 1;
  } else {
    int scale = get_scale(src);
    double a = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 32; j++)
        if (get_bit(src, i * 32 + j) == 1) a += pow(2, i * 32 + j);
    }
    for (int i = 0; i < scale; i++) {
      a /= 10.0;
    }
    if (get_sign(src)) {
      a = -a;
    }
    *dst = (float)a;
  }
  return result;
}