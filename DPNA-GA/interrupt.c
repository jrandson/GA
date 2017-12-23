
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//definição de macros
#define set_bit(var,bit_x) (var |= (1 << bit_x))
#define clr_bit(var,bit_x) (var &| ~(1 << bit_x))
#define test_bit(var,bit_x) (var & (1 << bit_x))
#define change_bit(var, bit_x) (var ^= (1 << bit_x))

#define LED PB7

int main(int argc, char const *argv[]) {
  /* code */
  DDRD = 0;
  PORTD = 0xff; // porta D como saída
  DDRB = 0xff; // porta B como entrada
  PORTB = 0xff;

  MCUCR = (1 << ISC01); // define a ocorrencia da interrução em termo das descida, subidas ou bordas

  GICR = (1 << INT1) | (1 << INT0); // ativas as interrupções INT0 e INT1
  sei();

  while(1){

  }
  return 0;
}

ISR(INT0_vect){
  if (test_bit(PINB,PB7))
    clr_bit(PORTB,LED);
  else
    set_bit(PORTB, LED);
}

ISR(INT1_vect){
  change_bit(PORTB,LED)
  _delay_ms(200);
}
