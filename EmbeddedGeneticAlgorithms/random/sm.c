#include "sm.h"

uint32_t x; /* The state can be seeded with any value. */

inline void sm_srand(uint32_t n)
{
	x = n;
}

inline uint32_t sm_rand() {
	uint32_t z = (x += UINT32_C(0x9E3779B97F4A7C15));
	z = (z ^ (z >> 30)) * UINT32_C(0xBF58476D1CE4E5B9);
	z = (z ^ (z >> 27)) * UINT32_C(0x94D049BB133111EB);
	return z ^ (z >> 31);
}

