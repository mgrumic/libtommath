#include "tommath_private.h"
#ifdef BN_MP_TC_AND_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * SPDX-License-Identifier: Unlicense
 */

/* two complement and */
int mp_tc_and(const mp_int *a, const mp_int *b, mp_int *c)
{
   int res = MP_OKAY, bits, abits, bbits;
   int sa = a->sign, sb = b->sign;
   mp_int *mx = NULL, _mx, acpy, bcpy;

   if ((sa == MP_NEG) || (sb == MP_NEG)) {
      abits = mp_count_bits(a);
      bbits = mp_count_bits(b);
      bits = MAX(abits, bbits);
      res = mp_init_set_int(&_mx, 1uL);
      if (res != MP_OKAY) {
         goto end;
      }

      mx = &_mx;
      res = mp_mul_2d(mx, bits + 1, mx);
      if (res != MP_OKAY) {
         goto end;
      }

      if (sa == MP_NEG) {
         res = mp_init(&acpy);
         if (res != MP_OKAY) {
            goto end;
         }

         res = mp_add(mx, a, &acpy);
         if (res != MP_OKAY) {
            mp_clear(&acpy);
            goto end;
         }
         a = &acpy;
      }
      if (sb == MP_NEG) {
         res = mp_init(&bcpy);
         if (res != MP_OKAY) {
            goto end;
         }

         res = mp_add(mx, b, &bcpy);
         if (res != MP_OKAY) {
            mp_clear(&bcpy);
            goto end;
         }
         b = &bcpy;
      }
   }

   res = mp_and(a, b, c);

   if ((sa == MP_NEG) && (sb == MP_NEG) && (res == MP_OKAY)) {
      res = mp_sub(c, mx, c);
   }

end:
   if (a == &acpy) {
      mp_clear(&acpy);
   }

   if (b == &bcpy) {
      mp_clear(&bcpy);
   }

   if (mx == &_mx) {
      mp_clear(mx);
   }

   return res;
}
#endif

/* ref:         $Format:%D$ */
/* git commit:  $Format:%H$ */
/* commit time: $Format:%ai$ */
