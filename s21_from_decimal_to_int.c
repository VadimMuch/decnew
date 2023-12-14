#include "../../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal dec, int *res) {
  int result = 0;
  int sign;
  if (s21_check(dec)) return 1;
  if (s21_get_exp(dec)) s21_norm_exp(&dec, 0);
  sign = s21_get_bit(dec, 127) ? -1 : 1;
  *res = dec.bits[0];
  *res *= sign;
  if (dec.bits[1] || dec.bits[2] || dec.bits[0] > 0x80000000) {
    *res = 0;
    result = 1;
  }
  return result;
}