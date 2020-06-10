/*
 * temperature.c
 *
 * Created: 04/09/2017 10:35:06
 *  Author: Denis
 */ 

#include "temperature.h"
#include <avr/io.h>


void temperature_init(void)
{
	/* Enable internal temperature measurement, with internal 1.1 V as reference */
	ADMUX |= (1 << MUX3) | (1 << REFS0) | (1 << REFS1);

	/* Configure the prescaller to 128 (125 KHz), enable interrupts, and select ADC0 */
	ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

uint32_t temperature_get(void)
{
	
	/* Start conversion */
	ADCSRA |= (1 << ADSC);
	
	/* Wait the end of the conversion */
	while (ADCSRA & (1 << ADSC));       // Detect end-of-conversion

	/* The returned temperature is in degrees Celsius */
	//return (ADCW - 324.31) / 1.22;
	return ADCW;
}