# EmbeddedGeneticAlgorithm

This is the source code of our project "Embedded genetic algorithm for low-power, low-cost and low-size-memory devices". 

It consists of a genetic algorithm implementation targeting embedded devices, such as microcontrollers.

### Running It

This project was initially developed using the IDE Atmel Studio 7.0 focusing the microcontroller ATmega328P - the same one present in Arduino Uno. 
Be aware that some features like sending text via USART for debug purposes depends on the device/ architecture you are using, therefore you may need
to use a different method. 

Moreover, if you want to debug and receive some float values via USART (using some C function such as `sprintf`, for example), 
you need to link the C library `printf_flt`. You can find a guide in the following link about how to do it using Atmel Studio 7, for example:

https://startingelectronics.org/articles/atmel-AVR-8-bit/print-float-atmel-studio-7/

### GA Parameters

All genetic algorithm parameters must be defined in the file `ga.h`. The only exception is the evaluation function, which is defined in the `main.c` file.
Please, notice that if you are using an evaluation function with multiple dimensions, you also need to change the parameter `DIMENSIONS`.

### Debugging and Evaluating Performance

If you want to check the result of the GA run, you need to send data via USART to your computer. The project already provides some functions that may be useful for you.

Finally, if you want to analyze the GA performance, you can use one of the internal counters (there are some functions ready to be used) or you can use one of the GPIO
pins to keep toggling between high and low voltage so you can use an external device (such as an oscilloscope) to measure the period.