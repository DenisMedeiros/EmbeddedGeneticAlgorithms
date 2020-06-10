/* Multiply with carry generator */

#ifndef MWC_H_
#define MWC_H_

#define SIZE 64
#define PHI 0x9e3779b9

#include <stdint.h>

void mwc_srand(uint32_t n);
uint32_t mwc_rand(void);

#endif /* MWC_H_ */