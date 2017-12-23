#include <avr/io.h>

// Motor Control Functions -- pwm is an 8-bit value
//  (i.e. ranges from 0 to 255)

void M1_forward(unsigned char pwm)
{
  OCR0A = 0;
  OCR0B = pwm;
}

void M1_reverse(unsigned char pwm)
{
  OCR0B = 0;
  OCR0A = pwm;
}

void M2_forward(unsigned char pwm)
{
  OCR2A = 0;
  OCR2B = pwm;
}

void M2_reverse(unsigned char pwm)
{
  OCR2B = 0;
  OCR2A = pwm;
}


// Motor Initialization routine -- this function must be called
//  before you use any of the above functions
void motors_init()
{
    // configure for inverted PWM output on motor control pins:
    //  set OCxx on compare match, clear on timer overflow
    //  Timer0 and Timer2 count up from 0 to 255
    TCCR0A = TCCR2A = 0xF3;

    // use the system clock/8 (=2.5 MHz) as the timer clock
    TCCR0B = TCCR2B = 0x02;

    // initialize all PWMs to 0% duty cycle (braking)
    OCR0A = OCR0B = OCR2A = OCR2B = 0;

    // set PWM pins as digital outputs (the PWM signals will not
    // appear on the lines if they are digital inputs)
    DDRD |= (1 << PORTD3) | (1 << PORTD5) | (1 << PORTD6);
    DDRB |= (1 << PORTB3);
}

//The following sample program demonstrates how these motor control functions can be used:
// delay for time_ms milliseconds by looping
//  time_ms is a two-byte value that can range from 0 - 65535
//  a value of 65535 (0xFF) produces an infinite delay
void delay_ms(unsigned int time_ms)
{
    // _delay_ms() comes from <util/delay.h> and can only
    //  delay for a max of around 13 ms when the system
    //  clock is 20 MHz, so we define our own longer delay
    //  routine based on _delay_ms()

    unsigned int i;

    for (i = 0; i < time_ms; i++)
        _delay_ms(1);
}

int main()
{
    motors_init();

    M1_forward(128);  // motor 1 forward at half speed
    M2_reverse(25);  // motor 2 reverse at 10% speed

    delay_ms(2000);  // delay for 2s while motors run

    M1_reverse(64);  // motor 1 reverse at 25% speed
    M2_forward(0);  // motor 2 stop/brake

    // loop here forever to keep the program counter from
    //  running off the end of our program
    while (1)
        ;

    return 0;
}
