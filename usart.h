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
#define FOSC 1843200 // frequencia de operacao
#define  BAUD 9600
#define MYUBRR FOSC /16/BAUD-1
                                                    // define baud
#define BAUDRATE  ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

/************************************************************************/
/* Declaração de funções                                                */
/************************************************************************/
void USART_init();
unsigned char USART_rcve();
void USART_send(unsigned char data);
void USART_flush();
void blink_led(char count);
void USART_send_int(int data);
uint32_t USART_rcve_int();
void USART_send_float(float data);
float USART_rcve_float();
void float_to_int(float f, uint32_t *i);
void int_to_float(uint32_t i, float *f);
///////////////////////////////////////////////////////////////////////////

void USART_init(){

  /* USART - Character Size - 8, */
  /*Stop bit - 1, baud Rate 9600, No Parity */

  /*Baund rate for f = 16MHz */
  /*unsigned int ubrr = 207;
  UBRR0H = (unsigned char) (ubrr >> 8);
  UBRR0L = (unsigned char) ubrr; */

  UBRR0H = (BAUDRATE>>8);                      // shift the register right by 8 bits
  UBRR0L = BAUDRATE;                           // set baud rate
  UCSR0B|= (1<<TXEN0)|(1<<RXEN0);              // enable receiver and transmitter
  UCSR0C |= (1 << USBS0)|(1<<UCSZ00)|(1<<UCSZ10); //(1 << UCSZ01)|(1 << UCSZ00)|(1 << USBS0);   // 8bit data format
}

void USART_send_int(int data){
  int i;
  unsigned char tmp;
  for(i = 0; i < 4; i++){
    tmp = data & 0b11111111;
    USART_send(tmp);
    data = (data >> 8);
  }
}

void USART_send_float(float data){
  int i;
  uint32_t data_int;
  float_to_int(data, &data_int);
  unsigned char tmp;

  USART_flush();

  for(i = 0; i < 4; i++){
    tmp = data_int & 0b11111111;
    USART_send(tmp);
    data_int = (data_int >> 8);
  }
}

//envia frames de 5 a 8 bits
void USART_send(unsigned char data){
  while(!(UCSR0A & (1 << UDRE0))); // espera a limpeza do registr. de transmiss
  UDR0 = data; //coloca o dado no registrador e envia
}

float USART_rcve_float(){
  uint32_t tmp, data_int;
  float data_float = 0;
  int i,j;
  tmp = 0;
  data_int = 0;

  USART_flush();

  for(i = 0; i < 4; i++){
    tmp = USART_rcve();
    for( j = 0; j < i; j++){
      tmp = (tmp << 8);
    }
    data_int |= tmp;
  }
  data_float = 0.0;
  int_to_float(data_int, &data_float);
  return data_float;
}

uint32_t USART_rcve_int(){
  uint32_t tmp;
  uint32_t data = 0;
  int i,j;

  for(i = 0; i < 4; i++){
    tmp = USART_rcve();
    for(j = 0; j < i; j++){
      tmp |= (tmp << 8);
    }
    data |= tmp;
  }

  return data;
}

//recebe frames de  5 a 8 bits
unsigned char USART_rcve(){
  while(!(UCSR0A & (1 <<  RXC0)));
  return UDR0;
}

//limpando o registrador de entrada
void USART_flush(){
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

typedef union{
  float f;
  long long int i;
} my_union;

void float_to_int(float f, uint32_t *i){
  my_union float_u;

  float_u.f = f;
  *i = float_u.i;
}

void int_to_float(uint32_t i, float *f){
  my_union int_u;

  int_u.i = i;
  *f = int_u.f;
}
