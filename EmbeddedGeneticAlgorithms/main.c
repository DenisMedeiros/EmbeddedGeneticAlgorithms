#include "ga.h"
#include "util/usart.h"
#include "util/power.h"
#include "util/temperature.h"
#include "random/lfsr.h"

#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/power.h>

volatile circular_buffer USART_tx_buffer; // Used to send string via USART.
volatile circular_buffer USART_rx_buffer; // Used to receive string via USART.

#ifndef PI
#define PI 3.14159265358979323846
#endif

/*
 * This function evaluates and generates a fitness value of the invididual, that has to
 * be already normalized. The user must implement it in his program.
 *
 * @param xn A individual of the population.
 * @return The fitness value of this individual.
 */
fitness_t evaluationFM(normalization_t xn[])
{	
	//return 21.5 + xn[0]*(sin(40*pi*xn[0]) + cos(20*pi*xn[0]) );
	//return 20 + pow(xn[0],2) + pow(xn[1],2) - 10*(cos(2*pi*xn[0]) + cos(2*pi*xn[1]));
	//return pow(xn[0]*xn[0] + xn[1]*xn[1], 0.5);
	//return 2*xn[0] + 3*xn[1] + 5;
	//return MINIMO + gainNorm * xn[0];
	
	//return (xn[0]-2)*(xn[0]-4); // f1
	//return xn[0]*xn[0] + xn[1]*xn[1]; // f2
	//return 2*xn[0] + 3*xn[1] + 5; // f3
	return -(21.5 + xn[0]*(sin(40*PI*xn[0]) + cos(20*PI*xn[0]))); // f4
	//return 10 + xn[0]*xn[0] - 10*cos(2*PI*xn[0]) + xn[1]*xn[1] - 10*cos(2*PI*xn[1]);
}

int main(void)
{
	chromosome_t population[POPULATION_SIZE][DIMENSIONS];
	fitness_t evaluation[POPULATION_SIZE];
	normalization_t normalizedChromosome[DIMENSIONS];
	popsize_t iBest;
	// char text[100]; // For debug purposes.
	
	/* Apply any configuration to reduce clock speed. */
	// power_init();
	
	//_delay_ms(1000);
	
	/* Enables interrupts */
	sei();
	
	/* Initialize the USART module */
	// USART_init();
	
	/* Initialize PD7 as output - used by external timer. */
	// DDRD |= (1 << DDD7);
		
	/* Put a seed in the generator of random numbers */
	lfsr_srand8(173);
	lfsr_srand16(27059);
	lfsr_srand32(104729);
	
	while(1)
	{
		/* Set to high on PD7 so start external timer. */
		// PORTD |= (1 << DDD7);
		
		/* Run the GA */
		iBest = geneticAlgorithmFM(evaluation, population);
		
		/* Set to low on PD7 so start external timer. */
		// PORTD &= ~(1 << DDD7);
				
		/* Normalize the result */
		normalizationFM(population[iBest], normalizedChromosome);
		
		/* Send result through USART connection */
		// sprintf(text, "index = %d, value = %f\n", iBest, normalizedChromosome[0]);
		//sprintf(text, "index = %d, value = (%f, %f)\n", iBest, normalizedChromosome[0], normalizedChromosome[1]);
		
		/* Print result. */
		// USART_send_string(text);
		
		/* Busy wait 100 ms */
		_delay_ms(100);
	}
	
	return 0;
}