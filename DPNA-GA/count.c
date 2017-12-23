#define F_CPU 1000000UL
#include <avr/io.h>
#include < avr/interrupt.h>

// declaração de variáveis aqui...

ISR(TIMER0_OVF_vect){
  // código após a chamada do estouro do T/CO
}

int main(){
  // inicializações aqui

  TCCRO = (1 << CS01) | (1 << CS00); // prescaler de 64, interrupção a cada 16,384 ms
  TIMSK = 1 << TOIE0; //habilita a interrupção do TC/0
  sei();

  for(;;){
    // a cada estouro, o código desvia para ISR()
  }
}
