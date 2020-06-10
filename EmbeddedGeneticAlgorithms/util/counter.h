/*
 * counter.h
 *
 * Created: 04/01/2018 14:30:05
 *  Author: Denis
 */ 

#ifndef COUNTER_H_
#define COUNTER_H_

#define CLOCK 16000000L
#define PRESCALLER 1024.0
#define COUNTER_INTERVAL 1.0/(CLOCK/PRESCALLER)

#include <stdint.h>

/* Configure the counter. */
void counter_init(void);

/* Start the counter. */
void counter_start(void);

/* Stop the counter. */
float counter_stop(void);

#endif /* COUNTER_H_ */