#include "ga.h"

/* Choose one of the random generators. */

#include "random/lfsr.h"
#include <math.h>
#include "util/usart.h"
#include <stdio.h>
#include <util/delay.h>

/** 
 * This is the core function of the genetic algorithm. It runs all the modules
 * and finds the best possible solution.
 *
 * @param evaluation A vector that will store the fitness values for the individuals.
 * @param population A vector containing the individuals.
 * @return The index of the best individual in the population after the last generation.
 */
popsize_t geneticAlgorithmFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS])
{
	popsize_t iBest;
	generationsize_t k;
	
	/* Initializes the population */
	initializationFM(population);
	
	/* Calculates the fitness for all individuals and save the best individual index */
	iBest = fitnessFM(evaluation, population);
	
	for(k = 0; k < NUM_GENERATIONS; k++)
	{	
		/* Generates a new population */
		newPopulationFM(evaluation, population, iBest);
		
		/* Calculates the fitness again and saves the best individual */
		iBest = fitnessFM(evaluation, population);
	}
	
	return iBest;
}

/** 
 * This function initializes the population with random individuals. It should be called once.
 *
 * @param population A vector containing the individuals.
 */
void initializationFM(chromosome_t population[][DIMENSIONS])
{	
	popsize_t i;
	dimensionsize_t j;
	
	for(i = 0; i < POPULATION_SIZE; i++)
	{
		for(j = 0; j < DIMENSIONS; j++)
		{
			/* Each individual is a random integer number */
#if CHROMOSOME_SIZE == 32
			population[i][j] = lfsr_rand32();		
#elif CHROMOSOME_SIZE == 16
			population[i][j] = lfsr_rand16();		
#else
			population[i][j] = lfsr_rand8();	
#endif
		}
	}
}

/** 
 * This function calculates the fitness value for the whole population. Before that, the
 * individuals are normalized to a range where the solution might be in.
 *
 * @param evaluation A vector that will store the fitness values for the individuals.
 * @param population A vector containing the individuals.
 * @return The index of the best individual in the population after the last generation.
 */
popsize_t fitnessFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS])
{
	popsize_t i;
	popsize_t iBest;
	normalization_t normalizedChromosome[DIMENSIONS];
	
	for (i = 0, iBest = 0; i < POPULATION_SIZE; i++)
	{
		/* First, normalize the individual */
		normalizationFM(population[i], normalizedChromosome);
			
		asm("break");
		/* The evaluation function (evaluationFM) must be defined by the user */
		evaluation[i] = evaluationFM(normalizedChromosome); 
		asm("break");
		
		if (evaluation[i] < evaluation[iBest])
		{
			iBest = i;
		}	
	}
	return iBest;
}

/** 
 * This function normalizes an individual to an specified range (between NORMALIZATION_MIN and NORMALIZATION_MAX).
 *
 * @param chromesome A individual of the population.
 * @param normalizedChromesome The normalized individual.
 */
void normalizationFM(chromosome_t chromesome[], normalization_t normalizedChromesome[])
{
	dimensionsize_t j;
	for(j = 0; j < DIMENSIONS; j++)
	{
	    /* Applies a normalized gain on the chromosome */
		normalizedChromesome[j] = NORMALIZATION_MIN + ((normalization_t) NORMALIZED_GAIN) * chromesome[j];
	}

}

/** 
 * This function generates a new population from a previous one. It does this by selecting and crossing
 * some individuals and applying mutation over some of them. In the and, it updates the current population
 * by the newer one.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @param population A vector containing the individuals.
 * @param The index of the best individual in the population after the generation of the new population.
 */
void newPopulationFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS], popsize_t iBest)
{
	chromosome_t newPopulation[POPULATION_SIZE][DIMENSIONS];
	/* Does the selection and crossover over the population */
	selectionCrossoverFM(evaluation, population, newPopulation);
	/* Applies the mutation over some individuals */
	mutationFM(newPopulation);
	/* Replaces the old population by the new one */
	updateFM(population, newPopulation, iBest);
}

/** 
 * This function does the selection and crossover of the individuals.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @param population A vector containing the individuals.
 * @param newPopulation A vector with the newer population.
 */
void selectionCrossoverFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS])
{
	popsize_t i;
	for(i = 0; i < POPULATION_SIZE; i += 2)
	{
	    /* Does the crossover between two individuals */
		crossoverFM(i, population, newPopulation, selectionFM(evaluation), selectionFM(evaluation));
	}
}

/** 
 * This function does the selection of one individual from the population. It picks two fitness
 * values and compares what is the best one and then returns its index.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @return The index of the best individual from the two that were selected.
 */
popsize_t selectionFM(fitness_t evaluation[])
{
	popsize_t iChromosomeX;  
	popsize_t iChromosomeY;
	
	/* Randomly pick two individuals and compare what is the the best one */
	
	iChromosomeX = lfsr_rand8() & (POPULATION_SIZE - 1);
	iChromosomeY = lfsr_rand8() & (POPULATION_SIZE - 1);
	
	if(evaluation[iChromosomeX] <= evaluation[iChromosomeY]) 
	{
		return iChromosomeX;
	}
	else
	{ 
		return iChromosomeY;
	}
}

/** 
 * This function crosses two individuals and generates two news ones.
 *
 * @param i The index where the new individual will be placed in the new population vector.
 * @param population A vector containing the individuals.
 * @param newPopulation A vector where the new two individuals will be put in.
 * @param ichA The index of the first individual to be crossed.
 * @param ichB The index of the second individual to be crossed.
 */
void crossoverFM(popsize_t i, chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS], popsize_t ichA, popsize_t ichB)
{
	dimensionsize_t j;
	for(j = 0; j < DIMENSIONS; j++)
	{
		/* Two chromosomes exchanges their genes between each other */
		newPopulation[i][j] = (population[ichA][j] & MASK) | (population[ichB][j] & ~MASK);
		newPopulation[i+1][j] = (population[ichA][j] & ~MASK) | (population[ichB][j] & MASK);
	}
}

/** 
 * This function mutates some individuals of the population.
 *
 * @param newPopulation A vector containing the individuals.
 */
void mutationFM(chromosome_t newPopulation[][DIMENSIONS])
{
	popsize_t i;
	dimensionsize_t j;
	chromosomesize_t bitPosition;
	
	
	/* The best individual will not be mutated */
	for(i = 1; i <=  MULTATED_INDIVIDUALS; i++)
	{
		
		for(j = 0; j < DIMENSIONS; j++)
		{
			bitPosition = lfsr_rand8() & (CHROMOSOME_SIZE-1);	
			
#if CHROMOSOME_SIZE == 32
			if(bitPosition < 8) /* First byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x00000001 << bitPosition);
			}
			else if (bitPosition < 16) /* Second byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x00000100 << (bitPosition - 8));
			}
			else if (bitPosition < 24) /* Third byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x00010000 << (bitPosition - 16));
			}
			else /* Fouth byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x01000000 << (bitPosition - 24));
			}
#elif CHROMOSOME_SIZE == 16
			if(bitPosition < 8) /* First byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x0001 << bitPosition);
			}
			else /* Second byte. */
			{
				newPopulation[i][j] = newPopulation[i][j] ^ (0x0100 << (bitPosition - 8));
			}
#else	
			newPopulation[i][j] = newPopulation[i][j] ^ (0x01 << bitPosition);
#endif
		}
	}
}

/** 
 * This function replaced the old population by the new one.
 *
 * @param population A vector containing the old individuals.
 * @param newPopulation A vector containing the new individuals.
 * @param iBest The index of the best individual in the population.
 */
void updateFM(chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS], popsize_t iBest)
{
	popsize_t i;
	dimensionsize_t j;
	/* Put the best individual of the new population in the first position of the old population. */
	for(j = 0; j < DIMENSIONS; j++)
	{
		population[0][j] = population[iBest][j];
	}
	
	/* Replace the old population by the new one */
	for(i = 1; i < POPULATION_SIZE; i++)
	{
		for(j = 0; j < DIMENSIONS; j++)
		{
			population[i][j] = newPopulation[i][j];
		}
	}
}


