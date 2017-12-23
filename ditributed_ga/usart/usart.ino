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
#include "C:\PortableGit\projects\GA_MCU\ga-spi-2\ga-3.h"

/************************************************************************/
/* USART                                                                */
/************************************************************************/
#define FOSC 1843200 // frequencia de operacao
#define  BAUD 9600
#define MYUBRR FOSC /16/BAUD-1
                                                    // define baud
#define BAUDRATE  ((F_CPU)/(BAUD*16UL)-1)            // set baud rate value for UBRR

void USART_init();
unsigned char USART_rcve();
void USART_send(unsigned char data);
void USART_flush();
void blink_led(char count);

/************************************************************************/
/* USART                                                                */

int main(){
  unsigned char count;
  DDRA=0x01;
  // led
  DDRB |= (1 << 7);
  PORTB &= ~(1 << 7);

  //9600 baud rate reffer data sheet //refer to formula in uart_init function
  USART_init();
  int i = 0;
  unsigned char data = 138; //152 -> 10011000; 138 -> 10001010
  float data_f[10] = {12.32, 300.09, 10.0, 33.21, 98.29, 11.11, 9.23, 101.92, 0.092, 1.092};
  int data_i[10] = {2, 34, 190, 398, 11, 982, 30, 3298, 430, 8};
  count = 0;
  int rcve = 0;
  float rcve_f = 0;
  uint32_t rcve_i = 0;
  while(1){
    USART_flush();

    float tmp_f, send_f = 3.141592653589;
    uint32_t  tmp_i = 0;

    rcve_f = USART_rcve_float();
    USART_send_float(rcve_f); // 4294967295

    //rcve = USART_rcve_int();
    //USART_send_int(rcve);

    //USART_flush();
    //USART_send_int(221);

    //blink_led((char)count);
  }

  return 0;
}

void ga(){

    unsigned int population[SIZE_POPULATION][N];
    unsigned int new_population[SIZE_POPULATION][N];
    float fitness[SIZE_POPULATION];

    int i = 0,T = 500;
    int j;
    float chromossome[N];


    init_population(population, SIZE_POPULATION);
    get_fitness(population, fitness, SIZE_POPULATION);

    while(i < T){
        new_generation(population, new_population, fitness, SIZE_POPULATION);
        get_best_chromossome(population, fitness, chromossome, SIZE_POPULATION);

        i++;
    }

    return 0;
}

void new_generation(unsigned int population[][N],unsigned int new_population[][N], float fitness[], int size_pop){
  get_new_population(population, new_population,fitness, size_pop);
  get_fitness(new_population,fitness, size_pop);
  transferePopulacao(population,new_population,size_pop);
}

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
  float data = 0;
  uint32_t tmp=0;
  unsigned char rcve;
  int i;

  for(i = 0; i < 2; i++){
    rcve = USART_rcve();
    tmp |= (rcve << i*8);
  }

  int_to_float(tmp,&data);
  return data;
}

int USART_rcve_int(){
  int data = 0;
  unsigned char rcve;
  int i;
  for(i = 0; i < 4; i++){
    rcve = USART_rcve();
    data |= (rcve << i*8);
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
