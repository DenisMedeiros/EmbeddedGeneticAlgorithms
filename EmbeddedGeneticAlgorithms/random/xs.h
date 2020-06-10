/* Xorshift generator */

#ifndef XS_H_
#define XS_H_

#include <stdint.h>

uint32_t seed; 

void xs_srand(uint32_t n);
uint32_t xs_rand(void);

#endif /* XS_H_ */