#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"
/**
http://maxembedded.com/2011/06/the-adc-of-the-avr/
https://acroname.com/articles/linearizing-sharp-ranger-data

*/

void ADC_init();
uint32_t ADC_read(uint8_t channel);

int main()
{

  USART_init();
  float valor_dist = 0;
  uint32_t ADC_val;

  DDRC = 0x00; // pino ADC0 como entrada
  DDRB |= (1 << 7); // led
  PORTB &= ~(1 << 7);
  ADC_init();
  while(1){

      ADC_val = ADC_read(0);
      valor_dist =  (6787 / (ADC - 3)) - 4;
      USART_send_float(valor_dist);

      if(valor_dist > 0.1){
        PORTB |= (1 << 7);
      }
      else{
        PORTB &= ~(1 << 7);
      }
  }
}



void ADC_init(){
  ADMUX |= (1 << REFS0) | (0 << REFS1);
  ADMUX &= ~(1 << ADLAR); // 10 bits resolution

  ADCSRA = (1 << ADEN ) | (1 << ADPS2) | (1 << ADPS1) |  (1 << ADPS0) ; // habilita o ADC, prescaler: divisão do clock por 128
  //ADCSRA |= (1 << ADIF) ; // Para checar se a converso foi completada ou nao


}

uint32_t ADC_read(uint8_t channel){

  uint32_t ADC_val;
  // select the corresponding channel 0~7
  // ANDing with ’7′ will always keep the value
  // of ‘channel’ between 0 and 7
  channel &= 0b00000111;  // AND operation with 7
  ADMUX = channel;
  //ADMUX = (ADMUX & 0xF8)|channel; // clears the bottom 3 bits before ORing

  // start single convertion
  // write ’1′ to ADSC
  ADCSRA |= (1 << ADSC);

  // wait for conversion to complete
  // run loop continuously
  while( ADCSRA & (1 << ADSC));

  ADC_val = ADCL;
  ADC_val = (ADCH << 8) + ADC_val;
  return ADC_val;
}
