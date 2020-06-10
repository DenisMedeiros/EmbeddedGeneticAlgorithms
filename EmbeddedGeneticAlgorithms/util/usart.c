/*
 * usart.c
 *
 * Created: 18/03/2017 13:35:27
 *  Author: Denis
 */ 

#include "usart.h"
#include <avr/interrupt.h>

extern volatile circular_buffer USART_tx_buffer;
extern volatile circular_buffer USART_rx_buffer;


/* Configure the USART. */
void USART_init(void) 
{
	/* Set baud rate */
	UBRR0H = (unsigned char) (BAUD_PRESCALLER >> 8);
	UBRR0L = (unsigned char) (BAUD_PRESCALLER);
	
	/* Enable receiver and transmitter */
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	/* Enable interruptions for reception */
	UCSR0B |= (1 << RXCIE0) | (1 << UDRIE0);
	
	/* Set frame format: 8 bits for data, 1 bit for stop bit */
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);	
}

/* Send one byte (with polling). */
void USART_send_byte(char data)
{
	/* Wait for empty transmit buffer. */
	while(!(UCSR0A & (1 << UDRE0)));
	/* Put data into buffer, then sends the data. */
	UDR0 = data;	
}

/* Send one string (with polling). */
void USART_send_string(char* string){
	while(*string != '\0')
	{
		USART_send_byte(*string);
		string++;
	}
}

/* Receive one byte (with polling). */
char USART_receive_byte(void)
{
	/* Wait for data to be received */
	while (!(UCSR0A & (1 << RXC0)));
	
	/* Get and return received data from buffer */
	return UDR0;
}

/* Add one char in the transmission buffer. */
char buffer_add(volatile circular_buffer* buffer, char c)
{
	uint8_t next_head_pos = (buffer->head_pos + 1) % BUFFER_SIZE;
	if (next_head_pos != buffer->tail_pos) {
		/* There is a room in the buffer */
		buffer->data[buffer->head_pos] = c;
		buffer->head_pos = next_head_pos;
		buffer->size++;
		return c;
	 } 
	 else 
	 {
		/* There is no room left in the buffer */
		return 255;
	 }
}

/* Remove one char from the receiving buffer. */
char buffer_remove(volatile circular_buffer* buffer)
{
	char c;
	if (buffer->head_pos != buffer->tail_pos) {
		c = buffer->data[buffer->tail_pos];
		buffer->tail_pos = (buffer->tail_pos + 1) % BUFFER_SIZE;
		buffer->size--;
		return c;
	} 
	else 
	{
		return 255;
	}
}

/* Put one string in the transmission buffer. */
char buffer_put_string(volatile circular_buffer* buffer, char* string)
{
	while(*string != 0x00)
	{
		if(buffer_add(buffer, *string) == 255)
		{
			return 255;
		};
		string++;
	}
	
	return 0;
}

/* Enable the transmission interrupt. */
void USART_enable_tx_interrupt(void)
{
	 UCSR0B |= (1 << UDRIE0);
}

/* Handle interrupt when data has arrived. 
 * The char received is a command for the system.
 * '+' = start the system
 * '-' = stop the system
 * '1' = change system to mode 1
 * '2' = change system to mode 2
 */
//ISR(USART0_RX_vect) // Mega
ISR(USART_RX_vect) 
{
	unsigned char c = UDR0;
	USART_send_byte(c);
	USART_send_byte('\n');
}

/* Handle interrupt when data is ready to be sent. 
 * This happens when the USART internal buffer is empty.
 */
//ISR(USART0_UDRE_vect) // Mega
ISR(USART_UDRE_vect)
{
	unsigned char c = buffer_remove(&USART_tx_buffer);
	
	if(c == 255) {
		/* Disable interrupt */
		UCSR0B &= ~(1 << UDRIE0);
		return;
	}
	
	UDR0 = c;
}