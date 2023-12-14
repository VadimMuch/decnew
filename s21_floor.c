#include "../../s21_decimal.h"

int s21_floor(s21_decimal dec1, s21_decimal *dec2) {
  int sign = dec1.bits[3] >> 31;
  s21_decimal int_part;
  s21_initialize(dec2);
  s21_truncate(dec1, &int_part);
  s21_decimal one = {{1, 0, 0, 0}};
  if (sign)
    s21_sub(int_part, one, dec2);
  else {
    for (int i = 0; i < 3; i++) dec2->bits[i] = int_part.bits[i];
  }
  return 0;
}