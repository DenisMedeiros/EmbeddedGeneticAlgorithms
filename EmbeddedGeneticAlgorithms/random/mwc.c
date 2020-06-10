#include "mwc.h"

uint32_t Q[SIZE];
uint32_t c;

void mwc_srand(uint32_t n)
{
	int i;
	c = 362436;
	
	Q[0] = n;
	Q[1] = n + PHI;
	Q[2] = n + PHI + PHI;

	for (i = 3; i < SIZE; i++)
	Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
}

uint32_t mwc_rand(void)
{
	unsigned long long t, a = 18782LL;
	static unsigned long i = SIZE-1;
	unsigned long x, r = 0xfffffffe;
	
	i = (i+1) & (SIZE-1);
	t = a * Q[i] + c;
	c = (t >> 32);
	x = t + c;
	if(x < c)
	{
		x++;
		c++;
	}
	return (Q[i] = r - x);
}