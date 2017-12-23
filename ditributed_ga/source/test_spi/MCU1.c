#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char data;

int i;
char token;


int main(){
  
  
  TCCR1B |= 0b00000001;
  TCNT1 = 0x0;
  seed = TCNT1;
  srand(seed);

  //DDRB |= 0b10000000;    

  token = 0;

  while(1){
    
      if(token){
        for(i = 0; i < 10; i++){
          if (i % 2 == 0)
            PORTB |= 0b10000000;
          else
            PORTB &= 0b01111111; 

          _delay_ms(1000); 
        }
      }
      else{
        for(i = 0; i < 100; i++){
          if (i % 2 == 0)
            PORTB |= 0b10000000;
          else
            PORTB &= 0b01111111; 

          _delay_ms(100); 
        }
      }

      tranfere_token(&token);  
         

  }

  return 0;
}
/**
pin 50 (MISO)
pin 51 (MOSI)
pin 52 (SCK)
pin 53 (SS)
**/

void tranfere_token(char * token){

  if(token){

    set_as_master();

    //seleciona o slave select do escravo 1
    PORTC = PORTC & 0b00000110;
    //send data to slave 
    SPDR = token;
    while (!(SPSR & (1<<SPIF)));

    //Receive data from slave 
    token = SPDR; 

  }
  else{

    set_as_slave()

    // seta dado para ser envia ao mestre
    SPDR = token;
    //Recebendo dados do mestre
    while (!(SPSR & (1<<SPIF)));
    
    // dados recebidos do mestre. Não serão utilizados pelo scravo
    token = SPDR;
  }
}

  
void set_as_slave(){
  //Ajusta o pino MISO (PB4) como saída
  DDRB = _BV(PB4);

  //bit SPE habilita o SPI
  SPCR = _BV(SPE);

  //Ajustando o pino D0, D1 e D2 como saída
  DDRD = 0b00000111; 
  PORTD = 0;
}

void set_as_master(){
  //Ajustando os pinos PA0, PA1, PA2 e PA3 como saída
  DDRA = 0b00001111;
  PORTA = 0;

  //Ajusta os pinos MOSI (PB2) e CLK (PB1) como saída
  DDRB = _BV(PB2) | _BV(PB1);

  //bit SPE habilita o SPI
  //bit MSTR = 1 habilita modo mestre
  //bits SPI2X, SPR1 e SPR2 configuram o clock
  SPCR = _BV(SPE) | _BV(MSTR) ;

  //Ajusta os pinos PC0, PC1 e PC2 para saída objetivando 
  //o controle SS dos escravos
  DDRC = _BV(PC0) | _BV(PC1)| _BV(PC2);
  PORTC = _BV(PC0) | _BV(PC1)| _BV(PC2);
}


void SPI_SlaveInit(void)
{
    /* Set MISO output, all others input */
    DDR_SPI = (1<<DD_MISO);
    /* Enable SPI */
    SPCR = (1<<SPE);
    }
    char SPI_SlaveReceive(void)
    {
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)))
    ;
    /* Return Data Register */
    return SPDR;
}


void SPI_MasterInit(void)
{
    /* Set MOSI and SCK output, all others input */
    DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
    /* Enable SPI, Master, set clock rate fck/16 */
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
    }
    void SPI_MasterTransmit(char cData)
    {
    /* Start transmission */
    SPDR = cData;
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)))
    ;
}