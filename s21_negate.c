#include "../../s21_decimal.h"

int s21_negate(s21_decimal dec1, s21_decimal *dec2) {
  s21_decimal_to_decimal(dec1, dec2);
  s21_inverse(dec2, 127);
  return 0;
}