#include "../../s21_decimal.h"

int s21_truncate(s21_decimal dec1, s21_decimal *dec2) {
  int exp = s21_get_exp(dec1);
  int sign = s21_get_sign(dec1);
  if (exp) {
    for (int i = 0; i < exp; i++) {
      s21_long_decimal long1;
      s21_long_decimal long2;
      s21_initialize_long(&long1);
      s21_initialize_long(&long2);
      s21_decimal_to_long(dec1, &long1);
      s21_long_mantissa_div_10(long1, &long2);
      s21_long_decimal_to_decimal(long2, &dec1);
    }
    s21_set_exp(&dec1, 0);
    s21_decimal_to_decimal(dec1, dec2);
  } else
    s21_decimal_to_decimal(dec1, dec2);
  if (sign > 0) s21_set_sign(dec2, 1);
  return 0;
}