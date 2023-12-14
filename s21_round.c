#include <stdint.h>

#include "../../s21_decimal.h"

int s21_round(s21_decimal dec1, s21_decimal *dec2) {
  s21_decimal one = {{1, 0, 0, 0}};
  s21_initialize(dec2);
  int sign = dec1.bits[3] >> 31;
  s21_decimal int_part;
  s21_truncate(dec1, &int_part);
  s21_decimal diff_dec;
  s21_sub(dec1, int_part, &diff_dec);
  float diff = 0;
  s21_from_decimal_to_float(diff_dec, &diff);
  if (fabs(diff) < 0.5)
    s21_decimal_to_decimal(int_part, dec2);
  else {
    if (sign == 1)
      s21_sub(int_part, one, dec2);
    else
      s21_add(int_part, one, dec2);
  }
  return 0;
}