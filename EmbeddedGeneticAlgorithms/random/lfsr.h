/* Linear Feedback Shift Register generator */


#ifndef LFSR_H_
#define LFSR_H_

#include <stdint.h>

void lfsr_srand32(uint32_t seed);
void lfsr_srand16(uint16_t seed);
void lfsr_srand8(uint8_t seed);

uint32_t lfsr_rand32(void);
uint16_t lfsr_rand16(void);
uint8_t lfsr_rand8(void);

#endif /* LFSR_H_ */