#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

void check_sensors();
int range;




int main()
{

  DDRB |= (1 << 7); // led
  PORTB &= ~(1 << 7);

        ADMUX = 0x00; // Get voltage from PA0 pin
        ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1); // configure ADC

        while(1)
        {
               if(ADCSRA & 1<<ADSC) // OR we can check here if ADC have finished working
               {
                       check_sensors();
                       if(range > 0.4){
                         PORTB |= (1 << 7);
                       }
                       else{
                         PORTB &= ~(1 << 7);
                       }
               }
        }

}

// Moreover we can use interrupts after ADC will finish calculating voltage
ISR(ADC_vect)
{
        float ADCdata = ADCW;
        int voltage_0 = ADCdata * 48875 / 10000; // ( 5000 mV / 1023 ) = 4.8875 ( mV in 1 bit )
        int voltage   = voltage_0 % 10000 / 1000;
        int voltage_2 = voltage_0 % 1000 / 100;
        int voltage_3 = voltage_0 % 100 / 10;
        int voltage_4 = voltage_0 % 10;

        if (ADCdata > 3) // Don't dividy by 0
        {
            range = (6787 / (ADCdata - 3)) - 4;
        }


        ADCSRA = ADCSRA | 0x40;// Start ADC again 0b01000000
}

void check_sensors()
{
        if(ADCSRA & 1<<ADSC) // If ADC calculations ended
        {
                unsigned int ADCdata;
                ADCdata = ADCW; // In ADCW our voltage is stored

                if(ADCdata <= 615) // rough measurement 13 cm is 2.5 V GP2D12
                {
                        // Do stuff
                }

                ADCSRA |= (1<<ADSC); // Start ADC conversion
        }
  }
