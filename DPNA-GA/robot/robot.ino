#include <stdio.h>
#include <stdlib.h>
#include  <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include "modules.h"

float pid(float error, float prev_error, float sum_error);
void move_robot(float distance);
float send_sinal(float sinal);
void turn_robot(int direction, float angle);
float send_signal(uint16_t sinal, uint8_t direction);

int main(int argc, char const *argv[]) {
  /* code */
   
  DDRB |= (1 << 0) | (1 << 1) | (1 << 2); 
  DDRD |= (1 << 5) | (1 << 6) | (1 << 7);

  int i = 0;
  while(1){
    send_signal(125,1);
  }


  return 0;
}

//enviar um sinal pwm para o robô girar
/*
  portas 5(PD5)ENA ,6(PD6) IN1, 7(PD7)IN2 e 8(PB0)IN3, 9(PB1)IN4, 10(PB2)ENA
    
    control MA:
      pwm : PD5
      dir : PD7 e PD6
      
    control MB:
      pmw : PB2
      dir : PB0 e PB1
      
    Motor A:
      go forward: IN1 = 1, IN2 = 0
      go backward: IN1 = 0, IN2 = 1
    
    Motor B:
      go forward: IN3 = 1, IN4 = 0
      go backward: IN3 = 0, IN4 = 1
      
*/

float send_signal(uint16_t sinal, uint8_t direction){

  //pin direction roda
  PORTD |= (1 << 7);  
  PORTD &= ~(1 << 6);

  PORTD |= (1 << 5);  
  
  return 0.0;
}
