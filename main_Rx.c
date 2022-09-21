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
unsigned char USART_Receive(void);
void main(void)
{

	// PIN 1 IN PORT C AS OUTPUT
	DDRC |= (1<<DDC1) |(1<<DDC4);
//	PORTA = (1<<PORTA6);    // enable pull up resestor
//	DDRB = 0XFF ;

	PORTC =(1<<PORTC4);


	USART_INIT(MYUBRR);
	unsigned char RX = USART_Receive();
	while(1)

	{
		if(RX == 'N')
		{
			PORTC |= (1<<PORTC1) ;
			_delay_us(500);
			PORTC &=! (1<<PORTC1) ;
			_delay_us(500);
		}
		else
		{
			PORTC |= (1<<PORTC4) ;
			_delay_us(1000);
			PORTC &=! (1<<PORTC4) ;
			_delay_us(1000);
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


