#ifndef GA_H_
#define GA_H_

#include <stdint.h>

/* Configuration of the Genetic Algorithm */

#define CHROMOSOME_SIZE 16 /* 8, 16 or 32 */
#define DIMENSIONS 1 /* Dimension of the chromosome */
#define POPULATION_SIZE 32 /* 16, 32, 64, 128 or 256 */
#define NUM_GENERATIONS 64 /* Between 1 and 256 */
#define MULTATED_INDIVIDUALS 1 /* Between 0 and POPULATION_SIZE. */
#define NORMALIZATION_MIN 0.0 /* Min limit for the result */
#define NORMALIZATION_MAX 1.0 /* Max limit for the result */

/*  DO NOT EDIT ANYTHING BELLOW THIS POINT */

/* Chromosome configuration */

#define MASK_SIZE CHROMOSOME_SIZE

#if CHROMOSOME_SIZE == 8

	typedef uint8_t chromosome_t;
	#define MASK 0xF0
	#define NORMALIZED_GAIN ((NORMALIZATION_MAX - NORMALIZATION_MIN)/255.0)

#elif CHROMOSOME_SIZE == 16

	typedef uint16_t chromosome_t;
	#define MASK 0xFF00
	#define NORMALIZED_GAIN ((NORMALIZATION_MAX - NORMALIZATION_MIN)/65535.0)

#elif CHROMOSOME_SIZE == 32

	typedef uint32_t chromosome_t;
	#define MASK 0xFFFF0000
	#define NORMALIZED_GAIN ((NORMALIZATION_MAX - NORMALIZATION_MIN)/4294967295.0) 
	
#else
	#error "CHROMOSOME_SIZE must be 8, 16 or 32"
#endif

/* Population configuration */
typedef uint8_t dimensionsize_t;
typedef uint8_t chromosomesize_t;
typedef uint8_t popsize_t;
typedef uint8_t generationsize_t;	

/* Fitness configuration */
typedef float fitness_t;
typedef float normalization_t;

/* Functions definitions */

/** 
 * This is the core function of the genetic algorithm. It runs all the modules
 * and finds the best possible solution.
 *
 * @param evaluation A vector that will store the fitness values for the individuals.
 * @param population A vector containing the individuals.
 * @return The index of the best individual in the population after the last generation.
 */
popsize_t geneticAlgorithmFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS]);

/** 
 * This function initializes the population with random individuals. It should be called once.
 *
 * @param population A vector containing the individuals.
 */
void initializationFM(chromosome_t population[][DIMENSIONS]);

/** 
 * This function calculates the fitness value for the whole population. Before that, the
 * individuals are normalized to a range where the solution might be in.
 *
 * @param evaluation A vector that will store the fitness values for the individuals.
 * @param population A vector containing the individuals.
 * @return The index of the best individual in the population after the last generation.
 */
popsize_t fitnessFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS]);

/** 
 * This function normalizes an individual to an specified range (between NORMALIZATION_MIN and NORMALIZATION_MAX).
 *
 * @param chromesome A individual of the population.
 * @param normalizedChromesome The normalized individual.
 */
void normalizationFM(chromosome_t chromesome[], normalization_t normalizedChromesome[]);

/** 
 * This function generates a new population from a previous one. It does this by selecting and crossing
 * some individuals and applying mutation over some of them. In the and, it updates the current population
 * by the newer one.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @param population A vector containing the individuals.
 * @param The index of the best individual in the population after the generation of the new population.
 */
void newPopulationFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS], popsize_t iBest);

/** 
 * This function does the selection and crossover of the individuals.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @param population A vector containing the individuals.
 * @param newPopulation A vector with the newer population.
 */
void selectionCrossoverFM(fitness_t evaluation[], chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS]);

/** 
 * This function does the selection of one individual from the population. It picks two fitness
 * values and compares what is the best one and then returns its index.
 *
 * @param evaluation A vector that stores the fitness values of the individuals.
 * @return The index of the best individual from the two that were selected.
 */
popsize_t selectionFM(fitness_t evaluation[]);

/** 
 * This function crosses two individuals and generates two news ones.
 *
 * @param i The index where the new individual will be placed in the new population vector.
 * @param population A vector containing the individuals.
 * @param newPopulation A vector where the new two individuals will be put in.
 * @param ichA The index of the first individual to be crossed.
 * @param ichB The index of the second individual to be crossed.
 */
void crossoverFM(popsize_t i, chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS], popsize_t ichA, popsize_t ichB);

/** 
 * This function mutates some individuals of the population.
 *
 * @param newPopulation A vector containing the individuals.
 */
void mutationFM(chromosome_t newPopulation[][DIMENSIONS]);

/** 
 * This function replaced the old population by the new one.
 *
 * @param population A vector containing the old individuals.
 * @param newPopulation A vector containing the new individuals.
 * @param iBest The index of the best individual in the population.
 */
void updateFM(chromosome_t population[][DIMENSIONS], chromosome_t newPopulation[][DIMENSIONS], popsize_t iBest);

/*
 * This function evaluates and generates a fitness value of the invididual, that has to
 * be already normalized. The user must implement it in his program.
 *
 * @param xn A individual of the population.
 * @return The fitness value of this individual.
 */
fitness_t evaluationFM(normalization_t xn[]);

#endif /* GA_H_ */
