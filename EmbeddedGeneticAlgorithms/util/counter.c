/*
 * counter.c
 *
 * Created: 04/01/2018 14:32:08
 *  Author: Denis
 */ 

#include "counter.h"
#include <avr/io.h>

/* Configure the counter. */
void counter_init(void)
{
	/* Normal mode... */
}

/* Start the counter. */
void counter_start(void)
{
	/* Initial value of the timer. */
	TCNT1 = 0;
	
	/* Set prescaller to 1024 and starts the timer. */
	TCCR1B |= (1 << CS10) | (1 << CS12);
}

/* Stop the counter and return the elapsed time in s. */
float counter_stop(void)
{
	/* Stop the timer. */
	TCCR1B &= ~(1 << CS10) & ~(1 << CS12); 

	return TCNT1 * COUNTER_INTERVAL;
}

