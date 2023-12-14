#include "../../s21_decimal.h"

int s21_long_mantissa_ten_times(s21_long_decimal* dec) {
  int error = 0;
  if (dec->bits[5] >> 30)
    error++;
  else {
    s21_long_decimal two_times;
    s21_long_decimal_to_long_decimal(*dec, &two_times);
    error += s21_long_shift(&two_times, 1);
    s21_long_decimal eight_times;
    s21_long_decimal_to_long_decimal(*dec, &eight_times);
    error += s21_long_shift(&eight_times, 3);
    error += s21_add_long(eight_times, two_times, dec);
  }
  return error;
}

int s21_long_mantissa_div_10(s21_long_decimal divisible,
                             s21_long_decimal* result) {
  int error = 0;
  s21_initialize_long(result);
  s21_long_decimal shifted_ten = {{10, 0, 0, 0, 0, 0, 0}};
  s21_long_decimal long_ten = {{10, 0, 0, 0, 0, 0, 0}};
  while (s21_long_greater_or_equal(divisible, shifted_ten)) {
    s21_long_shift(&shifted_ten, 1);
  }
  s21_long_shift(&shifted_ten, -1);
  while (s21_long_greater_or_equal(shifted_ten, long_ten)) {
    s21_long_shift(result, 1);
    if (s21_long_greater_or_equal(divisible, shifted_ten)) {
      s21_sub_long(divisible, shifted_ten, &divisible);
      s21_set_bit_1_long(result, 0);
    }
    s21_long_shift(&shifted_ten, -1);
  }
  return error;
}

int s21_long_div_mantissa(s21_long_decimal divisible, s21_long_decimal divider,
                          s21_long_decimal* result) {
  int mod = 0;
  s21_initialize_long(result);
  s21_long_decimal shifted_divider;
  s21_long_decimal_to_long_decimal(divider, &shifted_divider);
  while ((s21_long_greater_or_equal(divisible, shifted_divider)) &&
         (!s21_long_shift(&shifted_divider, 1)))
    ;
  s21_long_shift(&shifted_divider, -1);
  while (s21_long_greater_or_equal(shifted_divider, divider)) {
    s21_long_shift(result, 1);
    if (s21_long_greater_or_equal(divisible, shifted_divider)) {
      s21_sub_long(divisible, shifted_divider, &divisible);
      s21_set_bit_1_long(result, 0);
    }
    s21_long_shift(&shifted_divider, -1);
  }
  mod = (!s21_long_is_eq_0(divisible));
  return mod;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  s21_initialize(result);
  if (s21_is_eq_0(value_2))
    error = 3;
  else {
    int exp_divisible = s21_get_exp(value_1);
    int exp_divider = s21_get_exp(value_2);
    if (exp_divisible < exp_divider) s21_norm(&value_1, &value_2);
    exp_divisible = s21_get_exp(value_1);
    exp_divider = s21_get_exp(value_2);
    s21_long_decimal long_divisible;
    s21_decimal_to_long(value_1, &long_divisible);
    s21_long_decimal long_divider;
    s21_decimal_to_long(value_2, &long_divider);
    s21_long_decimal long_result;
    s21_initialize_long(&long_result);
    if (s21_long_div_mantissa(long_divisible, long_divider, &long_result)) {
      while (!s21_long_mantissa_ten_times(&long_divisible)) {
        exp_divisible++;
      }
      s21_long_div_mantissa(long_divisible, long_divider, &long_result);
    }
    s21_set_exp_long(&long_result, (exp_divisible - exp_divider));
    error = s21_long_decimal_to_decimal(long_result, result);
    s21_set_sign(result, (s21_get_sign(value_1) ^ s21_get_sign(value_2)));
    if ((error) && (!s21_get_sign(*result))) error = 1;
    if ((error) && (s21_get_sign(*result))) error = 2;
    if (s21_is_eq_0(*result) && (s21_get_exp(*result) == 28)) error = 2;
  }
  if (error) s21_initialize(result);
  return error;
}