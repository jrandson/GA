#include <avr/io.h>

float pid(float error, float prev_error, float sum_error);
void move_robot(float distance);
float send_sinal(float sinal);void rotate_robot(uint8_t direction, float angle);

void rotate_robot(uint8_t direction, float angle){

  float angle0 = 0.0;
  float sinal = 0.0;
  float sum_error = 0.0;
  float prev_error = 0.0;
  float error = 0;

  while(angle0 < angle + 0.1){

    error = angle - angle0;

    sinal = pid(error, prev_error, sum_error);

    angle0 += send_sinal(sinal);

    prev_error = error;
    sum_error += error;
  }
}

//enviar um sinal pwm para o robô girar
/**
  portas 5,6,7 e 8, 9, 10
  pin pwm
    5 : PD5, 6: PD6
  pin direction:
    7:PD7
    8: PB8
    9: PB1
    10: PB2
*/


void move_robot(float distance){

}

float pid(float error, float prev_error, float sum_error){
  float deriv = error - prev_error;
  float integ = sum_error + error;
  float ki, kp, kd;

  ki = 0.02;
  kd = 2.08;
  kp = 1.82;

  return kd * deriv + ki * integ + kp * error;
}
