#include "xs.h"

inline void xs_srand(uint32_t n)
{
	seed = n;
}

inline uint32_t xs_rand(void)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}
