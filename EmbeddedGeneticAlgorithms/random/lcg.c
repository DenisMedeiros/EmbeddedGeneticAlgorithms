#include "lcg.h"

inline void lcg_srand(uint32_t n)
{
	rseed = n;
}

#ifndef MS_RAND

	inline uint32_t lcg_rand(void)
	{
		return rseed = (rseed * 1103515245 + 12345) & RAND_MAX;
	}

#else /* MS rand */

	inline uint32_t lcg_rand(void)
	{
		return (rseed = (rseed * 214013 + 2531011) & RAND_MAX_32) >> 16;
	}

#endif
