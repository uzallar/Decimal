#ifndef SRC_S21_DECIMAL_H
#define SRC_S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define START_INFO 96
#define MAX_DEC powf(2.0f, 96.0f) - 1.0
#define MIN_DEC -powf(2.0f, 96.0f) + 1.0
#define BADINT (unsigned int)0x80000000

#define BITS_IN_1_INT 32
#define BIG_DECIMAL 8
#define TRUE 1
#define FALSE 0

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[BIG_DECIMAL];
} s21_big_decimal;

typedef union {
  int ui;
  float fl;
} floatbits;

typedef enum { PLUS, MINUS } sign;

typedef enum {
  STATUS_SUCCESS,
  STATUS_OVERFLOW_POSITIVE,
  STATUS_OVERFLOW_NEGATIVE
} add_status;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void add_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void subtract_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                          s21_big_decimal *result);
int multiply_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
int divide_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result);
void convert_decimal_to_big_decimal(s21_decimal value_1,
                                    s21_big_decimal *value_2);
void convert_big_decimal_to_decimal(s21_decimal *value_1,
                                    s21_big_decimal value_2);
void right_shift_big_decimal(s21_big_decimal *dst, int num);
int left_shift_big_decimal(s21_big_decimal *dst, int num);
void adjust_decimal_scales(s21_big_decimal *value_1, s21_big_decimal *value_2,
                           int diff);
int normalize_big_decimal_scale(s21_big_decimal *result, int scale);
void multiply_scale_big_decimal(s21_big_decimal *dst, int n);
void decrease_scale_big_decimal(s21_big_decimal *dst, int n);
int compare_big_decimals_greater(s21_big_decimal value_1,
                                 s21_big_decimal value_2);
int compare_big_decimals_or_equal(s21_big_decimal value_1,
                                  s21_big_decimal value_2);
void find_highest_bits_big_decimals(s21_big_decimal v1, s21_big_decimal v2,
                                    int *bit_1, int *bit_2);
int adjust_scales_of_big_decimals(s21_big_decimal *value_1,
                                  s21_big_decimal *value_2);
void ar_set_sign(s21_decimal *dst);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int comparison_two_decimal(s21_decimal value_1, s21_decimal value_2);
s21_big_decimal shift_left(s21_big_decimal dec, int num_shift);
void normalization(s21_big_decimal *dec_1, s21_big_decimal *dec_2);
int comparison_big_mantissa(s21_big_decimal dec1, s21_big_decimal dec2);
void convert_to_big_decimal(s21_decimal decimal, s21_big_decimal *b_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int count_significant_bits(int number);
int is_correct_scale_for_int(s21_decimal value);
int is_correct_decimal(s21_decimal value);
int from_char_to_7_symbol_int(char *arr, float src, int *insignificant_zero);
void decimal_mul_ten(s21_decimal *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int get_int_frac_part(s21_decimal value, s21_decimal *int_part,
                      s21_decimal *frac_part);
int correct_value(s21_decimal *value);
int s21_div10(s21_decimal *value);
int handle_floor(s21_decimal value, s21_decimal *result);
int handle_round(s21_decimal value, s21_decimal *result);

int is_zero(s21_decimal value);
void zero_decimal(s21_decimal *dst);
int is_decimal_nonzero(s21_decimal dst);
int get_sign(s21_decimal dst);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal dst);
void set_scale(s21_decimal *dst, int scale);
int get_bit(s21_decimal dst, int index);
void set_bit(s21_decimal *dst, int index, int bit);

int is_big_zero(s21_big_decimal dec);
void set_big_zero(s21_big_decimal *dec);
int is_big_decimal_nonzero(s21_big_decimal dst);
int get_big_scale(s21_big_decimal dec);
void set_big_scale(s21_big_decimal *dec, int scale);
int get_big_sign(s21_big_decimal dec);
void set_big_sign(s21_big_decimal *dec, int sign);
void set_big_bit(s21_big_decimal *dst, int index, int bit);
int get_big_bit(s21_big_decimal dst, int index);

#endif