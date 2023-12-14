#include "../../s21_decimal.h"

int s21_sub_max_min(s21_decimal dec_max, s21_decimal dec_min,
                    s21_decimal* result) {
  int error = 0;
  int tmp = 0;
  for (int i = 0; i <= 95; i++) {
    int res_bit = s21_get_bit(dec_max, i) ^ s21_get_bit(dec_min, i) ^ tmp;
    s21_set_bit(result, i, res_bit);
    tmp = ((s21_get_bit(dec_max, i) - s21_get_bit(dec_min, i)) - tmp < 0);
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int error = 0;
  s21_initialize(result);
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    s21_set_sign(result, s21_get_sign(value_1));
    int exp_result = s21_norm(&value_1, &value_2);
    if (s21_compare(value_1, value_2))
      s21_sub_max_min(value_1, value_2, result);
    else {
      s21_sub_max_min(value_2, value_1, result);
      s21_change_sign(result);
    }
    s21_set_exp(result, exp_result);
  } else {
    s21_set_sign(&value_2, s21_get_sign(value_1));
    error = s21_add(value_1, value_2, result);
  }
  if (s21_is_eq_0(*result)) {
    s21_set_sign(result, 0);
    s21_set_exp(result, 0);
  }
  return error;
}