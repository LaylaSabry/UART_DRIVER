/*
 * main.c
 *
 *  Created on: ??‏/??‏/????
 *      Author: layla
 */


#include "avr/io.h"
#include "util/delay.h"

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_INIT(uint16_t baud);
void USART_Transmit( unsigned char data );
void main(void)
{

	// PIN 8 IN PORT A AS INPUT
	DDRA &= ~(1<<DDA6);
	PORTA = (1<<PORTA6);    // enable pull up resestor
	DDRB = 0XFF ;



	USART_INIT(MYUBRR);

	while(1)

	{
		if(! (PINA &(1<<PIN6)))
		{
		USART_Transmit('N');
		}
		else
		{
			PORTB = 0XFF ;
			_delay_us(500);
			PORTB = 0X00 ;
			_delay_us(500);
		}
	}
}


void USART_INIT(uint16_t baud)
{
	/* Set baud rate */
	UBRRH = ( unsigned char)(baud>>8);
	UBRRL = ( unsigned char)baud;

	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);

	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}


unsigned char USART_Receive(void)
{
	// wait for receive complete
	while(!(UCSRA & (1<<RXC))) ;
	// then return the value received in UDR

	return UDR ;
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}


