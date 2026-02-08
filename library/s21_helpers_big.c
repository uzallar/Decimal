#include "../s21_decimal.h"

int is_big_zero(s21_big_decimal dec) {
  s21_big_decimal null = {0};
  s21_big_decimal minus_null = {0};
  set_big_sign(&minus_null, MINUS);
  return (comparison_big_mantissa(dec, null) == 0);
}

void set_big_zero(s21_big_decimal *dec) {
  for (int i = 0; i < BIG_DECIMAL; i++) {
    dec->bits[i] = 0;
  }
}

int is_big_decimal_nonzero(s21_big_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2] + dst.bits[3] + dst.bits[4] +
         dst.bits[5] + dst.bits[6] + dst.bits[7];
}

int get_big_scale(s21_big_decimal dec) {
  return (dec.bits[BIG_DECIMAL - 1] >> 16) & 0xFF;
}

void set_big_scale(s21_big_decimal *dec, int scale) {
  dec->bits[BIG_DECIMAL - 1] &= MINUS << (BITS_IN_1_INT - 1);
  dec->bits[BIG_DECIMAL - 1] |= scale << 16;
}

int get_big_sign(s21_big_decimal dec) {
  return (dec.bits[BIG_DECIMAL - 1] >> 31) & 1;
}

void set_big_sign(s21_big_decimal *dec, int sign) {
  if (sign == 0) {
    dec->bits[BIG_DECIMAL - 1] &= ~(1U << 31);
  } else {
    dec->bits[BIG_DECIMAL - 1] |= (1U << 31);
  }
}

void set_big_bit(s21_big_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}

int get_big_bit(s21_big_decimal dst, int index) {
  int mask = 1u << (index % 32);
  return (dst.bits[index / 32] & mask) != 0;
}

s21_big_decimal shift_left(s21_big_decimal dec, int num_shift) {
  unsigned int bit_temp = 0;
  for (int i = 0; i < BIG_DECIMAL - 1; i++) {
    unsigned int temp_bits = dec.bits[i];
    dec.bits[i] <<= num_shift;
    dec.bits[i] |= bit_temp;
    bit_temp = temp_bits >> (BITS_IN_1_INT - num_shift);
  }
  return dec;
}

void normalization(s21_big_decimal *dec_1, s21_big_decimal *dec_2) {
  s21_big_decimal result = {0};
  set_big_zero(&result);
  int scale_1 = get_big_scale(*dec_1);
  int scale_2 = get_big_scale(*dec_2);
  int sign_1 = get_big_sign(*dec_1);
  int sign_2 = get_big_sign(*dec_2);
  set_big_sign(dec_1, 0);
  set_big_sign(dec_2, 0);
  while (scale_1 != scale_2) {
    if (scale_1 > scale_2) {
      add_big_decimal(shift_left(*dec_2, 1), shift_left(*dec_2, 3), &result);
      *dec_2 = result;
      scale_2++;
      set_big_scale(dec_2, scale_2);
    } else {
      add_big_decimal(shift_left(*dec_1, 1), shift_left(*dec_1, 3), &result);
      *dec_1 = result;
      scale_1++;
      set_big_scale(dec_1, scale_1);
    }
  }
  set_big_sign(dec_1, sign_1);
  set_big_sign(dec_2, sign_2);
}

int comparison_big_mantissa(s21_big_decimal dec1, s21_big_decimal dec2) {
  int flag = 0;
  for (int i = BIG_DECIMAL - 1; i >= 0 && flag == 0; i--) {
    if (dec1.bits[i] > dec2.bits[i]) {
      flag = 1;
    } else if (dec1.bits[i] < dec2.bits[i]) {
      flag = -1;
    }
  }
  return flag;
}

void convert_to_big_decimal(s21_decimal decimal, s21_big_decimal *b_decimal) {
  for (int i = 0; i < 3; i++) {
    b_decimal->bits[i] = decimal.bits[i];
  }
  for (int i = 3; i < BIG_DECIMAL - 1; i++) {
    b_decimal->bits[i] = 0;
  }
  b_decimal->bits[BIG_DECIMAL - 1] = decimal.bits[3];
}