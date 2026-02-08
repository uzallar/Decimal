#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, get = 0, sign_res = 0;
  zero_decimal(result);
  if (get_sign(value_1) && get_sign(value_2)) {
    sign_res = 1;
  }
  if (get_sign(value_1) != get_sign(value_2)) {
    int sign = 0;
    sign = get_sign(value_1);
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
    error = sign ? s21_sub(value_2, value_1, result)
                 : s21_sub(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    int scale = 0;
    convert_decimal_to_big_decimal(value_1, &v1);
    convert_decimal_to_big_decimal(value_2, &v2);
    int diff = get_scale(value_1) - get_scale(value_2);
    if (diff > 0) {
      get = get_scale(value_1);
      set_scale(&value_2, get);
    } else {
      get = get_scale(value_2);
      set_scale(&value_1, get);
    }
    adjust_decimal_scales(&v1, &v2, diff);
    add_big_decimal(v1, v2, &r);
    scale = normalize_big_decimal_scale(&r, get_scale(value_1));
    if (scale >= 0) {
      convert_big_decimal_to_decimal(result, r);
      set_scale(result, scale);
    } else {
      error = 1;
    }
  }
  sign_res == 1 ? ar_set_sign(result) : 0;
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int res = 0, ovf = 0;
  for (int i = 0; i < 256; i++) {
    res = get_big_bit(value_1, i) + get_big_bit(value_2, i) + ovf;
    ovf = res / 2;
    set_big_bit(result, i, res % 2);
  }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0, sign_res = 0;
  zero_decimal(result);
  if (get_sign(value_1) && get_sign(value_2)) {
    s21_decimal temporary1 = value_1;
    value_1 = value_2;
    value_2 = temporary1;
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
  }
  if (get_sign(value_1) != get_sign(value_2)) {
    get_sign(value_1) ? sign_res = 1 : 1;
    set_bit(&value_1, 127, 0);
    set_bit(&value_2, 127, 0);
    error = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    convert_decimal_to_big_decimal(value_1, &v1);
    convert_decimal_to_big_decimal(value_2, &v2);
    int diff = get_scale(value_1) - get_scale(value_2);
    diff > 0 ? set_scale(&value_2, get_scale(value_2) + diff)
             : set_scale(&value_1, get_scale(value_1) - diff);
    adjust_decimal_scales(&v1, &v2, diff);
    if (compare_big_decimals_greater(v2, v1)) {
      s21_big_decimal temporary2 = v1;
      v1 = v2;
      v2 = temporary2;
      ar_set_sign(result);
    }
    subtract_big_decimal(v1, v2, &r);
    scale = normalize_big_decimal_scale(&r, get_scale(value_1));
    if (scale >= 0) {
      convert_big_decimal_to_decimal(result, r);
      set_scale(result, scale);
    } else {
      error = 1;
    }
  }
  sign_res == 1 ? ar_set_sign(result) : 0;
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

void subtract_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result) {
  int tmp = 0, res = 0;
  for (int i = 0; i < 256; i++) {
    res = get_big_bit(value_1, i) - get_big_bit(value_2, i) - tmp;
    tmp = res < 0;
    res = abs(res);
    set_big_bit(result, i, res % 2);
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0, scale = 0;
  s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
  convert_decimal_to_big_decimal(value_1, &v1);
  convert_decimal_to_big_decimal(value_2, &v2);
  if (get_sign(value_1) != get_sign(value_2)) ar_set_sign(result);
  scale = get_scale(value_1) + get_scale(value_2);
  error = multiply_big_decimal(v1, v2, &r);
  scale = normalize_big_decimal_scale(&r, scale);
  if (scale >= 0) {
    set_scale(result, scale);
    convert_big_decimal_to_decimal(result, r);
  } else {
    error = 1;
  }
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int multiply_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result) {
  int error = 0, count = 0;
  for (int i = 0; i < 256 && !error; i++) {
    if (get_big_bit(value_2, i)) {
      error = left_shift_big_decimal(&value_1, i - count);
      add_big_decimal(value_1, *result, result);
      count = i;
    }
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;
  if (is_decimal_nonzero(value_2)) {
    int scale = 0, res_scale = 0;
    s21_big_decimal v1 = {0}, v2 = {0}, r = {0};
    convert_decimal_to_big_decimal(value_1, &v1);
    convert_decimal_to_big_decimal(value_2, &v2);
    if (get_sign(value_1) != get_sign(value_2)) ar_set_sign(result);
    scale = divide_big_decimal(v1, v2, &r);
    set_scale(&value_1, get_scale(value_1) + scale);
    res_scale = get_scale(value_1) - get_scale(value_2);
    if (res_scale > 0) {
      res_scale = normalize_big_decimal_scale(&r, res_scale);
    } else if (res_scale < 0) {
      multiply_scale_big_decimal(&r, abs(res_scale));
      res_scale = normalize_big_decimal_scale(&r, 0);
    }
    if (res_scale >= 0) {
      convert_big_decimal_to_decimal(result, r);
      set_scale(result, res_scale);
    } else {
      error = 1;
    }
  } else {
    error = 3;
  }
  if (error == 1 && get_sign(*result)) error = 2;
  if (error) zero_decimal(result);
  return error;
}

int divide_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result) {
  int b_1 = 0, b_2 = 0, bit_2 = 0, scale = 0, diff = 0, save_scale = 0;
  s21_big_decimal tmp = {0};
  find_highest_bits_big_decimals(value_1, value_2, &b_1, &b_2);
  bit_2 = b_2;
  for (int i = 0; i < 96 && is_big_decimal_nonzero(value_1);) {
    if (i > 0) {
      left_shift_big_decimal(&value_2, 1);
      multiply_scale_big_decimal(result, 1);
      multiply_scale_big_decimal(&value_1, 1);
      save_scale++;
    }
    scale = adjust_scales_of_big_decimals(&value_1, &value_2);
    save_scale += scale;
    b_1 = b_2 = 0;
    find_highest_bits_big_decimals(value_1, value_2, &b_1, &b_2);
    diff = b_2 - bit_2;
    if (diff < 0) diff = 0;
    for (; diff >= 0 && is_big_decimal_nonzero(value_1);) {
      if (compare_big_decimals_greater(value_2, value_1)) {
        set_big_bit(&tmp, 0, 0);
      } else {
        subtract_big_decimal(value_1, value_2, &value_1);
        set_big_bit(&tmp, 0, 1);
      }
      i++;
      diff--;
      if (diff >= 0) right_shift_big_decimal(&value_2, 1);
      left_shift_big_decimal(&tmp, 1);
    }
    if (diff >= 0) left_shift_big_decimal(&tmp, diff + 1);
    right_shift_big_decimal(&tmp, 1);
    add_big_decimal(*result, tmp, result);
    set_big_zero(&tmp);
  }
  return save_scale;
}

void convert_decimal_to_big_decimal(s21_decimal value_1,
                                    s21_big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
}

void convert_big_decimal_to_decimal(s21_decimal *value_1,
                                    s21_big_decimal value_2) {
  value_1->bits[0] = value_2.bits[0];
  value_1->bits[1] = value_2.bits[1];
  value_1->bits[2] = value_2.bits[2];
}

void right_shift_big_decimal(s21_big_decimal *dst, int num) {
  int buffer[7] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_big_bit(*dst, (i + 1) * 32);
    }
    for (int i = 0; i < 7; i++) {
      dst->bits[i] >>= 1;
      set_big_bit(dst, (i + 1) * 32 - 1, buffer[i]);
    }
    dst->bits[7] >>= 1;
  }
}

int left_shift_big_decimal(s21_big_decimal *dst, int num) {
  int error = 0;
  int buffer[8] = {0};
  for (int k = 0; k < num; k++) {
    for (int i = 0; i < 7; i++) {
      buffer[i] = get_big_bit(*dst, (i + 1) * 32 - 1);
    }
    for (int i = 7; i > 0 && !error; i--) {
      if (get_big_bit(*dst, 255)) error = 1;
      dst->bits[i] <<= 1;
      set_big_bit(dst, i * 32, buffer[i - 1]);
    }
    dst->bits[0] <<= 1;
  }
  return error;
}

void adjust_decimal_scales(s21_big_decimal *value_1, s21_big_decimal *value_2,
                           int diff) {
  if (diff > 0) {
    multiply_scale_big_decimal(value_2, diff);
  } else if (diff < 0) {
    multiply_scale_big_decimal(value_1, -diff);
  }
}

int normalize_big_decimal_scale(s21_big_decimal *result, int scale) {
  int dop = 0;
  while ((result->bits[3] || result->bits[4] || result->bits[5] ||
          result->bits[6] || result->bits[7]) &&
         scale > 0) {
    if (scale == 1 && result->bits[3]) dop = 1;
    decrease_scale_big_decimal(result, 1);
    scale--;
  }
  if (dop && scale == 0 && result->bits[3] == 0 && get_big_bit(*result, 0))
    set_big_bit(result, 0, 0);
  if ((result->bits[3] || result->bits[4] || result->bits[5] ||
       result->bits[6] || result->bits[7]))
    scale = -1;
  return scale;
}

void multiply_scale_big_decimal(s21_big_decimal *dst, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    multiply_big_decimal(*dst, ten, &tmp);
    *dst = tmp;
    set_big_zero(&tmp);
  }
}

void decrease_scale_big_decimal(s21_big_decimal *dst, int n) {
  s21_big_decimal ten = {{10, 0, 0, 0, 0, 0, 0, 0}}, tmp = {0};
  for (int i = 0; i < n; i++) {
    divide_big_decimal(*dst, ten, &tmp);
    *dst = tmp;
    set_big_zero(&tmp);
  }
}

int compare_big_decimals_greater(s21_big_decimal value_1,
                                 s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !result && !out; i--) {
    if (value_1.bits[i] || value_2.bits[i]) {
      if (value_1.bits[i] > value_2.bits[i]) {
        result = 1;
      }
      if (value_1.bits[i] != value_2.bits[i]) out = 1;
    }
  }
  return result;
}

int compare_big_decimals_or_equal(s21_big_decimal value_1,
                                  s21_big_decimal value_2) {
  int result = 0, out = 0;
  for (int i = 7; i >= 0 && !out && !result; i--) {
    if (value_1.bits[i] != 0 || value_2.bits[i] != 0) {
      if (value_1.bits[i] >= value_2.bits[i]) {
        result = 1;
      }
      out = 1;
    }
  }
  return result;
}

void find_highest_bits_big_decimals(s21_big_decimal v1, s21_big_decimal v2,
                                    int *bit_1, int *bit_2) {
  for (int i = 255; i >= 0 && (!(*bit_1) || !(*bit_2)); i--) {
    if (*bit_1 == 0 && get_big_bit(v1, i)) *bit_1 = i;
    if (*bit_2 == 0 && get_big_bit(v2, i)) *bit_2 = i;
  }
}

int adjust_scales_of_big_decimals(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2) {
  int scale = 0;
  while (compare_big_decimals_greater(*value_2, *value_1)) {
    multiply_scale_big_decimal(value_1, 1);
    scale++;
  }
  while (compare_big_decimals_or_equal(*value_1, *value_2)) {
    left_shift_big_decimal(value_2, 1);
  }
  right_shift_big_decimal(value_2, 1);
  return scale;
}
void ar_set_sign(s21_decimal *dst) { dst->bits[3] = dst->bits[3] | 1u << 31; }