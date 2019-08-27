/*
 * usartA.c
 *
 * Created: 9/10/2018 4:53:49 PM
 * 
 */ 


#include <avr/io.h>

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/(16*(BAUD-1))

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );

unsigned char i;

int main( void )
{
	unsigned char  str = 'A';
	
	USART_Init ( MYUBRR );
	//USART_Transmit('A' );
	while(1)
	{
		USART_Transmit( str );
	}
	return(0);
}

void USART_Init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable transmitter */
	UCSR0B = (1<<TXEN);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
