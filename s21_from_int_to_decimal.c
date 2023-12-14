#include "../../s21_decimal.h"

int s21_from_int_to_decimal(int i, s21_decimal *dec) {
  char result = 0;
  if (dec) {
    dec->bits[0] = 0;
    dec->bits[1] = 0;
    dec->bits[2] = 0;
    dec->bits[3] = 0;
    if (i < 0) {
      s21_set_sign(dec, 1);
      i *= -1;
    }
    dec->bits[0] = i;
  } else
    result = 1;
  return result;
}