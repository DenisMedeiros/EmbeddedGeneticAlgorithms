#ifndef POWER_H_
#define POWER_H_

#define BASE_F_CPU 16000000UL  /* Base CPU clock = 16 MHz. */
#define CPU_DIV 1

#define F_CPU BASE_F_CPU/CPU_DIV

/* Initializes the power configuration. */
void power_init(void);

#endif /* POWER_H_ */