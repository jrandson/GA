/*
 * CFile1.c
 *
 * Created: 01/12/2016 19:12:28
 *  Author: Randson
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//make sure you set this according to the freq your board operates at
#define F_CPU 16000000UL  // 16 MHz
#include <inttypes.h>
/************************************************************************/
/* USART                                                                */
/************************************************************************/
#define FOSC 1843200 // frequencia de operação
#define  BAUD 9600
#define MYUBRR FOSC /16/BAUD-1

void USART_init();
unsigned char USART_rcve();
void USART_send(unsigned char data);
void USART_Flush();
void blink_led(char count);

/************************************************************************/
/* USART                                                                */



int main(){
	unsigned char count;
	DDRA=0x01;
	// led
	DDRB |= (1 << 7);
	
	//9600 baud rate reffer data sheet //refer to formula in uart_init function
	USART_init();
	int i = 0;
	while(1){
		count = USART_rcve();
		USART_send(count);
		
		if(count == 10){
			PORTB |= (1 << 7);
			_delay_ms(k1000);
		}
		else{
			PORTB &= ~(1 << 7);
			_delay_ms(1000);
		}
		
		//blink_led((char)count);
	}
	
	return 0;
}

void USART_init(){
	
	/* USART - Character Size - 8, */
	/*Stop bit - 1, baud Rat 9600, No Parity */
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00) |(1 << USBS0);
	
	/*Baund rate for f = 16MHz */
	unsigned int ubrr = 207;
	UBRR0H = (unsigned char) (ubrr >> 8);
	UBRR0L = (unsigned char) ubrr;
}

//envia frames de 5 a 8 bits
void USART_send(unsigned char data){
	while(!(UCSR0A & (1 << UDRE0))); // espera a limpeza do registr. de transmiss
	UDR0 = data; //coloca o dado no registrador e envia
}

//recebe frames de  5 a 8 bits
unsigned char USART_rcve(){
	while(!(UCSR0A & (1 <<  RXC0)));
	return UDR0;
}

//limpando o registrador de entrada
void USART_Flush(){
	unsigned char dummy;
	while(UCSR0A & (1<<RXC0)) dummy = UDR0;
}


void blink_led(char count){
	char i;
	for(i = 0; i < count; i++){
		PORTA |= (1 << 0);
		_delay_ms(1000);
		
		PORTA &= ~(1 << 0);
		_delay_ms(5000);
	}
}
