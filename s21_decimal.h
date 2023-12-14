#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned long long bits[4];
} s21_big_decimal;

typedef struct {
  unsigned int bits[7];
} s21_long_decimal;

/* ARITHMETIC */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

/* COMPARE */
int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);
int s21_compare(s21_decimal dec1, s21_decimal dec2);
int s21_is_eq_0(s21_decimal dec);
int s21_long_is_eq_0(s21_long_decimal dec);
int s21_long_is_greater(s21_long_decimal long_dec1, s21_long_decimal long_dec2);
int s21_long_mantissa_is_equal(s21_long_decimal dec1, s21_long_decimal dec2);
int s21_long_greater_or_equal(s21_long_decimal dec1, s21_long_decimal dec2);
int s21_long_mantissa_ten_times(s21_long_decimal* dec);

/* COVERTERS */
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);

/* OTHER */
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

/* AIXILIARY */
int s21_set_bit_1(s21_decimal* d, int i);
int s21_set_bit_0(s21_decimal* d, int i);
int s21_set_bit(s21_decimal* d, int i, int a);
void s21_set_exp(s21_decimal* decimal, int exponent);
int s21_set_sign(s21_decimal* dec, int c);

int s21_set_bit_0_long(s21_long_decimal* d, int i);
int s21_set_bit_1_long(s21_long_decimal* d, int i);
int s21_set_bit_long(s21_long_decimal* d, int i, int a);
void s21_set_exp_long(s21_long_decimal* decimal, int exponent);

void s21_inverse(s21_decimal* d, int i);
int s21_inverse_long(s21_long_decimal* d, int i);

int s21_get_bit(s21_decimal d, int i);
int s21_get_exp(s21_decimal dec);
int s21_get_sign(s21_decimal dec);

int s21_get_exp_long(s21_long_decimal long_dec);
int s21_get_bit_long(s21_long_decimal d, int i);

int s21_norm_exp(s21_decimal* dec, int newexp);
int s21_norm_min_max(s21_decimal* dec_exp_min, s21_decimal* dec_exp_max);
int s21_norm(s21_decimal* value_1, s21_decimal* value_2);

void s21_decimal_to_decimal(s21_decimal value, s21_decimal* result);

void s21_decimal_to_big_decimal(s21_decimal dec, s21_big_decimal* dst);
int s21_big_decimal_to_decimal(s21_big_decimal Big_Dec, s21_decimal* dec);
void s21_big_decimal_to_decimal_after_div(s21_big_decimal Big_Dec,
                                          s21_decimal* dec);

void s21_decimal_to_long(s21_decimal dec, s21_long_decimal* dst);
int s21_long_decimal_to_decimal(s21_long_decimal Long_Dec, s21_decimal* dec);
void s21_long_decimal_to_long_decimal(s21_long_decimal value,
                                      s21_long_decimal* result);

int s21_sub_max_min(s21_decimal dec_max, s21_decimal dec_min,
                    s21_decimal* result);
int s21_bit_addition(s21_decimal dec_1, s21_decimal dec_2, s21_decimal* result);
int s21_add_long(s21_long_decimal dec_1, s21_long_decimal dec_2,
                 s21_long_decimal* result);
int s21_sub_long(s21_long_decimal dec_max, s21_long_decimal dec_min,
                 s21_long_decimal* result);
void s21_div_big_decimal(s21_decimal dec, s21_big_decimal* Big_Dec);
int s21_long_div_10(s21_long_decimal divisible, s21_long_decimal* result);
int s21_long_mantissa_div_10(s21_long_decimal divisible,
                             s21_long_decimal* result);
int s21_mul_10(s21_decimal* dec);
int s21_div_10(s21_decimal* dec);

void s21_initialize(s21_decimal* dst);
void s21_initialize_long(s21_long_decimal* dst);
int s21_check(s21_decimal decimal);
int s21_check_float(float src);
int s21_decrease_exp(s21_decimal* value_1, s21_decimal* value_2);
int s21_long_shift(s21_long_decimal* long_shifted, int k);
void s21_change_sign(s21_decimal* dec);