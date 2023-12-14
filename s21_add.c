#include "../../s21_decimal.h"

int s21_bit_addition(s21_decimal dec_1, s21_decimal dec_2,
                     s21_decimal* result) {
  int tmp = 0;
  for (int i = 0; i <= 95; i++) {
    int res_bit = ((s21_get_bit(dec_1, i) ^ s21_get_bit(dec_2, i)) ^ tmp);
    s21_set_bit(result, i, res_bit);
    tmp = ((s21_get_bit(dec_1, i) + s21_get_bit(dec_2, i)) + tmp > 1);
  }
  return tmp;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  s21_initialize(result);
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    int exp_result = s21_norm(&value_1, &value_2);
    error = s21_bit_addition(value_1, value_2, result);
    while ((error) && (exp_result)) {
      exp_result--;
      s21_norm_exp(&value_1, exp_result);
      s21_norm_exp(&value_2, exp_result);
      error = s21_bit_addition(value_1, value_2, result);
    }
    s21_set_exp(result, exp_result);
    s21_set_sign(result, s21_get_sign(value_1));
    if (error && (!s21_get_sign(value_1))) error = 1;
    if (error && s21_get_sign(value_1)) error = 2;
  } else {
    if (s21_compare(value_1, value_2)) {
      s21_set_sign(&value_2, s21_get_sign(value_1));
      error = s21_sub(value_1, value_2, result);
    } else {
      s21_set_sign(&value_1, s21_get_sign(value_2));
      error = s21_sub(value_2, value_1, result);
    }
  }
  if (s21_is_eq_0(*result)) {
    s21_set_sign(result, 0);
    s21_set_exp(result, 0);
  }
  return error;
}