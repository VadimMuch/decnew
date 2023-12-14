#include "../../s21_decimal.h"

int s21_mul_bit_by_bit(s21_decimal dec_1, s21_decimal dec_2,
                       s21_decimal* result) {
  int error = 0;
  s21_long_decimal long_result;
  s21_initialize_long(&long_result);
  for (int i = 0; i <= 95; i++) {
    if (s21_get_bit(dec_2, i)) {
      s21_long_decimal long_shifted;
      s21_decimal_to_long(dec_1, &long_shifted);
      s21_long_shift(&long_shifted, i);
      s21_add_long(long_result, long_shifted, &long_result);
    }
  }
  s21_set_exp_long(&long_result, s21_get_exp(dec_1) + s21_get_exp(dec_2));
  error = s21_long_decimal_to_decimal(long_result, result);
  return error;
}

int s21_decrease_exp(s21_decimal* value_1, s21_decimal* value_2) {
  int exp1 = s21_get_exp(*value_1);
  int exp2 = s21_get_exp(*value_2);
  if (exp1 > exp2)
    exp1--;
  else
    exp2--;
  s21_norm_exp(value_1, exp1);
  s21_norm_exp(value_2, exp2);
  int exp_result = exp1 + exp2;
  return exp_result;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  s21_initialize(result);
  int exp1 = s21_get_exp(value_1);
  int exp2 = s21_get_exp(value_2);
  int exp_result = exp1 + exp2;
  while (exp_result > 28) exp_result = s21_decrease_exp(&value_1, &value_2);
  error = s21_mul_bit_by_bit(value_1, value_2, result);
  s21_set_sign(result, (s21_get_sign(value_1) ^ s21_get_sign(value_2)));
  if ((error) && (s21_get_sign(*result))) error = 2;
  if (error) s21_initialize(result);
  return error;
}