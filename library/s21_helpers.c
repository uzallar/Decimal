#include "../s21_decimal.h"

int is_zero(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

void zero_decimal(s21_decimal *dst) {
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;
}

int is_decimal_nonzero(s21_decimal dst) {
  return dst.bits[0] + dst.bits[1] + dst.bits[2];
}

int get_sign(s21_decimal dst) { return (dst.bits[3] & 1u << 31) != 0; }

void set_sign(s21_decimal *value, int sign) {
  value->bits[3] = (value->bits[3] & ~(1 << 31)) | (sign << 31);
}

int get_scale(s21_decimal dst) {
  int mask = 127 << 16;
  int scale = (mask & dst.bits[3]) >> 16;
  return scale;
}
void set_scale(s21_decimal *dst, int scale) {
  int sign = 0;
  sign = get_sign(*dst);
  dst->bits[3] = 0;
  scale <<= 16;
  dst->bits[3] = scale | dst->bits[3];
  if (sign) ar_set_sign(dst);
}

int get_bit(s21_decimal dst, int index) {
  int mask = 1u << (index % 32);
  return (dst.bits[index / 32] & mask) != 0;
}

void set_bit(s21_decimal *dst, int index, int bit) {
  int mask = 1u << (index % 32);
  if (bit == 0)
    dst->bits[index / 32] = dst->bits[index / 32] & ~mask;
  else
    dst->bits[index / 32] = dst->bits[index / 32] | mask;
}