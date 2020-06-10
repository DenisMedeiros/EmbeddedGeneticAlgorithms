#include "lfsr.h"

/* These values are prime numbers. */

uint32_t lfsr32 = 0xFFFFFFEF; 
uint16_t lfsr16 = 0xFFD9;
uint8_t lfsr8 = 0xFB; 

inline void lfsr_srand32(uint32_t seed)
{
	lfsr32 = seed;
}

inline void lfsr_srand16(uint16_t seed)
{
	lfsr16 = seed;
}

inline void lfsr_srand8(uint8_t seed)
{
	lfsr8 = seed;
}

inline uint32_t lfsr_rand32(void)
{
	uint32_t feedback = lfsr32 & 1;   /* Get LSB (i.e., the output bit). */
	
	lfsr32 >>= 1;                /* Shift register */
	if (feedback)    
	{              
		lfsr32 ^= 0xB4BCD35C;
	}
	return lfsr32;
	
}

inline uint16_t lfsr_rand16(void)
{
	uint16_t feedback = lfsr16 & 1;   /* Get LSB (i.e., the output bit). */
	
	lfsr16 >>= 1;                /* Shift register */
	if (feedback)
	{
		lfsr16 ^= 0xD295;
	}
	return lfsr16;
	
}

inline uint8_t lfsr_rand8(void)
{
	uint8_t feedback = lfsr8 & 1;   /* Get LSB (i.e., the output bit). */
	
	lfsr8 >>= 1;                /* Shift register */
	if (feedback)
	{
		lfsr8 ^= 0xA6;
	}
	return lfsr8;
	
}
