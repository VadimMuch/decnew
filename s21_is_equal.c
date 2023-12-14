#include "../../s21_decimal.h"

int s21_is_eq_0(s21_decimal dec) {
  int equal = 0;
  for (int i = 95; i >= 0; i--)
    if (s21_get_bit(dec, i) != 0) equal++;
  return (!equal);
}

int s21_is_equal(s21_decimal dec1, s21_decimal dec2) {
  int equal = 0;
  s21_norm(&dec1, &dec2);
  if (s21_get_sign(dec1) == s21_get_sign(dec2)) {
    for (int i = 95; i >= 0; i--)
      if ((s21_get_bit(dec1, i) != s21_get_bit(dec2, i))) equal++;
  } else
    equal++;
  if ((s21_is_eq_0(dec1)) && (s21_is_eq_0(dec2))) equal = 0;
  return (!equal);
}