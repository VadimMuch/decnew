#include "../../s21_decimal.h"

int s21_is_greater(s21_decimal dec1, s21_decimal dec2) {
  int greater = 0;
  s21_norm(&dec1, &dec2);
  if (s21_get_sign(dec1) == s21_get_sign(dec2)) {
    int i = 95;
    while ((i >= 0) && (s21_get_bit(dec1, i) == s21_get_bit(dec2, i))) i--;
    if ((s21_get_bit(dec1, i)) > (s21_get_bit(dec2, i))) greater = 1;
    if (s21_get_sign(dec1) && s21_is_not_equal(dec1, dec2))
      greater = (greater == 0);
  } else if (s21_get_sign(dec1) < s21_get_sign(dec2))
    greater = 1;
  return greater;
}