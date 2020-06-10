/* Mersenne Twister generator */

#ifndef MT_H_
#define MT_H_

#include <stdint.h>

#define N              (62)                 // length of state vector
#define M              (39)                 // a period parameter
#define K              (0x9908B0DFU)         // a magic constant
#define hiBit(u)       ((u) & 0x80000000U)   // mask all but highest   bit of u
#define loBit(u)       ((u) & 0x00000001U)   // mask all but lowest    bit of u
#define loBits(u)      ((u) & 0x7FFFFFFFU)   // mask     the highest   bit of u
#define mixBits(u, v)  (hiBit(u)|loBits(v))  // move hi bit of u to hi bit of v

void mt_srand(uint32_t seed);
uint32_t mt_reload(void);
uint32_t mt_rand(void);


#endif /* MT_H_ */