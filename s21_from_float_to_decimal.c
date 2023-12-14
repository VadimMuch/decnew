#include "../../s21_decimal.h"

int s21_from_float_to_decimal(float flt, s21_decimal *dec) {
  s21_initialize(dec);
  if (dec == NULL || s21_check_float(flt)) return 1;
  long double ldflt = flt;
  int output = 0;
  int sign = 0;
  if (ldflt < 0)
    sign = 1;
  else
    sign = 0;
  ldflt = fabsl(ldflt);
  if (pow(10, -28) <= ldflt && ldflt < pow(2, 96) &&
      ldflt >= -(pow(2, 96) - 1)) {
    int scale = 0;
    while (ldflt < 999999 && scale < 28) {
      ldflt *= 10;
      scale++;
    }
    while (ldflt > 9999999) {
      ldflt /= 10;
      scale--;
    }
    ldflt = round(ldflt);
    int temp = (int)ldflt;
    dec->bits[0] = temp;
    while (scale > 0 && dec->bits[0] % 10 == 0) {
      scale--;
      s21_div_10(dec);
    }
    while (scale < 0) {
      s21_mul_10(dec);
      scale++;
    }
    s21_set_exp(dec, scale);
    if (sign) s21_set_sign(dec, 1);
  } else
    output = 1;
  return output;
}

int s21_check_float(float flt) {
  int output = 0;
  static const float max_decimal = 79228162514264337593543950335.;
  if (isnan(flt) || isinf(flt) || max_decimal < flt || flt < -(max_decimal) ||
      (flt > 0 && flt < 1e-28) || (flt < 0 && flt > -1e-28)) {
    output = 1;
  }
  return output;
}