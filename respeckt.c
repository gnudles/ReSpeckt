#include <stdint.h>

#define ROR(x, r) ((x >> (r)) | (x << ((64 - (r))/*&63*/)))
#define ROL(x, r) ((x << (r)) | (x >> ((64 - (r))/*&63*/)))
#define R(x, y, k) (x = ROR(x, 24+(y&31)), x += y, x ^= k, y = ROL(y, 9+(x&31)), y ^= x)
#define ROUNDS 32

void encrypt(uint64_t ct[2],
             uint64_t const pt[2],            
             uint64_t const K[2])
{
   uint64_t y = pt[0], x = pt[1], b = K[0], a = K[1];

   R(x, y, b);
   for (int i = 0; i < ROUNDS - 1; i++) {
      R(a, b, i);
      R(x, y, b);
   }

   ct[0] = y;
   ct[1] = x;
}
