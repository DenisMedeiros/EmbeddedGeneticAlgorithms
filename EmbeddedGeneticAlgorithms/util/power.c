#include "power.h"
#include <avr/power.h>

/* Initializes the power configuration. */
void power_init(void)
{
	/* Reduce base clock (F_CPU is defined in USART). */
	switch (CPU_DIV)
	{
		case 2:
			clock_prescale_set(clock_div_2);
			break;
		case 4:
			clock_prescale_set(clock_div_4);
			break;
		case 8:
			clock_prescale_set(clock_div_8);
			break;
		case 16:
			clock_prescale_set(clock_div_16);
			break;
		default:
			clock_prescale_set(clock_div_1);
			break;
	}
	
	/* Disable other peripherals that are not being used.*/
	// power_aca_disable(); /* Disable the Analog Comparator on PortA. */
	// power_adc_disable(); /* Disable the Analog to Digital Converter module. */
	// power_adca_disable(); /* Disable the Analog to Digital Converter module. */
	
}