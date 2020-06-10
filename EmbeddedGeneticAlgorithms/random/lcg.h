/* Linear congruential generator */

#ifndef LCG_H_
#define LCG_H_

#include <stdint.h>

#ifndef MS_RAND
#define RAND_MAX ((1UL << 31) - 1)
#else
#define RAND_MAX_32 ((1U << 31) - 1)
#define RAND_MAX ((1U << 15) - 1)
#endif

uint32_t rseed;

/* Receives the seed */
void lcg_srand(uint32_t n);
/* Generates a random number */
uint32_t lcg_rand(void);

	
#endif /* LCG_H_ */