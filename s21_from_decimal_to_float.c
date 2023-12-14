#include "../../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal dec, float *res) {
  int result = 0;
  int sign;
  double temp = 0.0;
  for (int i = 0; i < 96; i++) temp += (s21_get_bit(dec, i) * pow(2, i));
  int exp = s21_get_exp(dec);
  *res = temp / pow(10, exp);
  if (s21_get_bit(dec, 127) == 1)
    sign = -1;
  else
    sign = 1;
  *res *= sign;
  return result;
}