#include "../../s21_decimal.h"

int s21_set_bit_0(s21_decimal* dec, int i) {
  int byte = (int)(i / 32);
  i = i - byte * 32;
  int error = 1;
  if (byte <= 3) {
    dec->bits[byte] = ((dec->bits[byte]) & ~(1 << i));
    error = 0;
  }
  return error;
}

int s21_set_bit_1(s21_decimal* dec, int i) {
  int byte = (int)(i / 32);
  i = i - byte * 32;
  int error = 1;
  if (byte <= 3) {
    dec->bits[byte] = ((dec->bits[byte]) | (1 << i));
    error = 0;
  }
  return error;
}

int s21_set_bit(s21_decimal* dec, int i, int bit) {
  int error = 0;
  if (bit == 1)
    error = s21_set_bit_1(dec, i);
  else
    error = s21_set_bit_0(dec, i);
  return error;
}

int s21_set_sign(s21_decimal* dec, int bit) {
  s21_set_bit(dec, 127, bit);
  return bit;
}

void s21_set_exp(s21_decimal* dec, int exp) {
  for (int i = 16, j = 0; i < 24; i++, j++) {
    if ((exp & (1 << j)) >> j)
      s21_set_bit_1(dec, 96 + i);
    else
      s21_set_bit_0(dec, 96 + i);
  }
}

int s21_set_bit_0_long(s21_long_decimal* dec, int i) {
  int byte = (int)(i / 32);
  i = i - byte * 32;
  int err = 1;
  if (byte <= 6) {
    dec->bits[byte] = ((dec->bits[byte]) & ~(1 << i));
    err = 0;
  }
  return err;
}

int s21_set_bit_1_long(s21_long_decimal* dec, int i) {
  int byte = (int)(i / 32);
  i = i - byte * 32;
  int error = 1;
  if (byte <= 6) {
    dec->bits[byte] = ((dec->bits[byte]) | (1 << i));
    error = 0;
  }
  return error;
}

int s21_set_bit_long(s21_long_decimal* dec, int i, int bit) {
  int err = 0;
  if (bit == 1)
    err = s21_set_bit_1_long(dec, i);
  else
    err = s21_set_bit_0_long(dec, i);
  return err;
}

void s21_set_exp_long(s21_long_decimal* dec, int exp) { dec->bits[6] = exp; }

int s21_get_sign(s21_decimal dec) {
  int c = (dec.bits[3] >> 31);
  return c;
}

int s21_get_bit(s21_decimal dec, int i) {
  int err = -1;
  int byte = (int)(i / 32);
  i = i - byte * 32;
  if ((byte <= 3) && (i >= 0)) err = (dec.bits[byte] & (1 << i)) >> i;
  return err;
}

int s21_get_exp_long(s21_long_decimal dec_l) { return (dec_l.bits[6]); }

int s21_get_exp(s21_decimal dec) {
  return ((dec.bits[3] & (((long long)1 << 27) - 1)) >> 16);
}

int s21_get_bit_long(s21_long_decimal dec, int i) {
  int err = -1;
  int byte = (int)(i / 32);
  i = i - byte * 32;
  if ((byte <= 6) && (i >= 0)) err = (dec.bits[byte] & (1 << i)) >> i;
  return err;
}

int s21_norm(s21_decimal* dec1, s21_decimal* dec2) {
  int exp1 = s21_get_exp(*dec1), exp2 = s21_get_exp(*dec2), exp_result = 0;
  if (exp1 < exp2)
    exp_result = s21_norm_min_max(dec1, dec2);
  else
    exp_result = s21_norm_min_max(dec2, dec1);
  return exp_result;
}

int s21_norm_min_max(s21_decimal* dec_min, s21_decimal* dec_max) {
  int exp_min = s21_get_exp(*dec_min);
  int exp_max = s21_get_exp(*dec_max);
  while ((exp_min < exp_max) && (!s21_mul_10(dec_min))) {
    exp_min++;
  }
  s21_set_exp(dec_min, exp_min);
  while (exp_min < exp_max) {
    s21_div_10(dec_max);
    exp_max--;
  }
  s21_set_exp(dec_max, exp_max);
  return exp_min;
}

int s21_norm_exp(s21_decimal* dec, int new_exp) {
  int error = 0;
  int exp = s21_get_exp(*dec);
  for (int i = exp; i < new_exp; i++) error += s21_mul_10(dec);
  for (int i = exp; i > new_exp; i--) error += s21_div_10(dec);
  s21_set_exp(dec, new_exp);
  return error;
}

void s21_decimal_to_big_decimal(s21_decimal dec, s21_big_decimal* big_decimal) {
  for (int i = 0; i < 4; i++) big_decimal->bits[i] = dec.bits[i];
}

void s21_decimal_to_decimal(s21_decimal dec1, s21_decimal* dec2) {
  for (int k = 0; k <= 3; k++) dec2->bits[k] = dec1.bits[k];
}

void s21_div_big_decimal(s21_decimal dec, s21_big_decimal* big_decimal) {
  for (int i = 0; i < 3; i++)
    big_decimal->bits[i] = (unsigned long long)dec.bits[i] << 32;
  big_decimal->bits[3] = dec.bits[3];
}

void s21_big_decimal_to_decimal_after_div(s21_big_decimal big_decimal,
                                          s21_decimal* dec) {
  big_decimal.bits[0] = (unsigned int)(big_decimal.bits[0] >> 32) +
                        (unsigned int)big_decimal.bits[1];
  big_decimal.bits[1] = (unsigned int)(big_decimal.bits[1] >> 32) +
                        (unsigned int)big_decimal.bits[2];
  big_decimal.bits[2] = (unsigned int)(big_decimal.bits[2] >> 32);
  s21_big_decimal_to_decimal(big_decimal, dec);
}

int s21_big_decimal_to_decimal(s21_big_decimal big_decimal, s21_decimal* dec) {
  int error = 0;
  big_decimal.bits[1] = big_decimal.bits[1] + (big_decimal.bits[0] >> 32);
  big_decimal.bits[2] = big_decimal.bits[2] + (big_decimal.bits[1] >> 32);
  if (big_decimal.bits[2] >> 32) error = 1;
  for (int i = 0; i < 4; i++) dec->bits[i] = (int)big_decimal.bits[i];
  return error;
}

void s21_decimal_to_long(s21_decimal dec1, s21_long_decimal* dec2) {
  for (int i = 0; i <= 2; i++) dec2->bits[i] = dec1.bits[i];
  for (int i = 3; i <= 5; i++) dec2->bits[i] = 0;
  dec2->bits[6] = dec1.bits[3];
}

void s21_long_decimal_to_long_decimal(s21_long_decimal dec1,
                                      s21_long_decimal* dec2) {
  for (int k = 0; k <= 6; k++) dec2->bits[k] = dec1.bits[k];
}

int s21_long_decimal_to_decimal(s21_long_decimal dec_l, s21_decimal* dec) {
  s21_initialize(dec);
  int exp_result = s21_get_exp_long(dec_l);
  while (((dec_l.bits[3]) || (dec_l.bits[4]) || (dec_l.bits[5]) ||
          (exp_result > 28)) &&
         exp_result) {
    exp_result--;
    s21_long_mantissa_div_10(dec_l, &dec_l);
  }
  int error = (dec_l.bits[3]) || (dec_l.bits[4]) || (dec_l.bits[5]);
  if (!error) {
    for (int i = 0; i <= 2; i++) dec->bits[i] = (int)dec_l.bits[i];
    s21_set_exp(dec, exp_result);
  }
  return error;
}

int s21_mul_10(s21_decimal* dec) {
  int error = 0;
  if (dec->bits[2] >> 30)
    error++;
  else {
    s21_big_decimal big_decimal = {{0, 0, 0, 0}};
    s21_decimal_to_big_decimal(*dec, &big_decimal);
    for (int i = 0; i < 3; i++) {
      big_decimal.bits[i] =
          (big_decimal.bits[i] << 3) + (big_decimal.bits[i] << 1);
    }
    error += s21_big_decimal_to_decimal(big_decimal, dec);
  }
  return error;
}

int s21_div_10(s21_decimal* dec) {
  int error = 0;
  s21_big_decimal big_decimal = {{0, 0, 0, 0}};
  s21_div_big_decimal(*dec, &big_decimal);
  for (int i = 0; i < 3; i++) big_decimal.bits[i] = big_decimal.bits[i] / 10;
  s21_big_decimal_to_decimal_after_div(big_decimal, dec);
  return error;
}

int s21_add_long(s21_long_decimal dec_1, s21_long_decimal dec_2,
                 s21_long_decimal* dec_l) {
  s21_initialize_long(dec_l);
  int tmp = 0;
  for (int i = 0; i <= 191; i++) {
    s21_set_bit_long(
        dec_l, i,
        ((s21_get_bit_long(dec_1, i) ^ s21_get_bit_long(dec_2, i)) ^ tmp));
    tmp = ((s21_get_bit_long(dec_1, i) + s21_get_bit_long(dec_2, i)) + tmp > 1);
  }
  return tmp;
}

int s21_sub_long(s21_long_decimal dec1, s21_long_decimal dec2,
                 s21_long_decimal* dec_l) {
  int error = 0;
  int tmp = 0;
  for (int i = 0; i <= 191; i++) {
    s21_set_bit_long(
        dec_l, i,
        ((s21_get_bit_long(dec1, i) ^ s21_get_bit_long(dec2, i) ^ tmp)));
    tmp = ((s21_get_bit_long(dec1, i) - s21_get_bit_long(dec2, i)) - tmp < 0);
  }
  return error;
}

int s21_long_is_greater(s21_long_decimal dec1, s21_long_decimal dec2) {
  int greater = 0;
  int i = 191;
  while ((i >= 0) && (s21_get_bit_long(dec1, i) == s21_get_bit_long(dec2, i)))
    i--;
  if ((s21_get_bit_long(dec1, i)) > (s21_get_bit_long(dec2, i))) greater = 1;

  return greater;
}

int s21_long_mantissa_is_equal(s21_long_decimal dec1, s21_long_decimal dec2) {
  int equal = 0;
  int i = 191;
  while ((s21_get_bit_long(dec1, i) == s21_get_bit_long(dec2, i)) && (i > 0))
    i--;
  equal = ((!i) && (s21_get_bit_long(dec1, 0) == s21_get_bit_long(dec2, 0)));
  return equal;
}

int s21_long_is_eq_0(s21_long_decimal dec) {
  int tmp = 0;
  int i = 191;
  while ((s21_get_bit_long(dec, i) == 0) && (i > 0)) i--;
  tmp = ((!i) && (s21_get_bit_long(dec, 0) == 0));
  return tmp;
}

int s21_long_greater_or_equal(s21_long_decimal dec1, s21_long_decimal dec2) {
  return (s21_long_mantissa_is_equal(dec1, dec2) ||
          s21_long_is_greater(dec1, dec2));
}

void s21_initialize(s21_decimal* dec) {
  for (int i = 0; i < 4; i++) dec->bits[i] = 0;
}

int s21_compare(s21_decimal dec1, s21_decimal dec2) {
  int status = 0;
  s21_norm(&dec1, &dec2);
  int i = 95;
  while ((i >= 0) && (s21_get_bit(dec1, i) == s21_get_bit(dec2, i))) i--;
  if ((s21_get_bit(dec1, i)) > (s21_get_bit(dec2, i))) status = 1;
  return status;
}

void s21_inverse(s21_decimal* dec, int i) {
  if (s21_get_bit(*dec, i))
    s21_set_bit_0(dec, i);
  else
    s21_set_bit_1(dec, i);
}

void s21_change_sign(s21_decimal* dec) {
  if (s21_get_sign(*dec))
    s21_set_sign(dec, 0);
  else
    s21_set_sign(dec, 1);
}

int s21_check(s21_decimal dec) {
  int error = 0;
  int exp = s21_get_exp(dec);
  int checkZeroBit = dec.bits[3] << 16;
  if (exp > 28 && checkZeroBit) error = 1;
  return error;
}

int s21_long_shift(s21_long_decimal* dec_l, int k) {
  int error = 0;
  if (k >= 0) {
    for (int i = 191; i > 191 - k; i--) error += s21_get_bit_long(*dec_l, i);
    if (!error) {
      for (int i = 191; i >= k; i--)
        s21_set_bit_long(dec_l, i, s21_get_bit_long(*dec_l, i - k));
      for (int i = k - 1; i >= 0; i--) s21_set_bit_0_long(dec_l, i);
    }
  } else {
    k = -k;
    for (int i = 0; i <= 191 - k; i++)
      s21_set_bit_long(dec_l, i, s21_get_bit_long(*dec_l, i + k));
    for (int i = 191 - k; i <= 191; i++) s21_set_bit_0_long(dec_l, i);
  }
  return error;
}

void s21_initialize_long(s21_long_decimal* dec_l) {
  for (int i = 0; i < 7; i++) dec_l->bits[i] = 0;
}