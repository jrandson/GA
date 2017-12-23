#include <avr\io.h>


int main()
{


  DDRB |= 0b10000000;

  int t = 0;   


    //Ajusta o pino MISO (PB4) como saída
    DDRB = _BV(PB4);
    
    //bit SPE habilita o SPI
    SPCR = _BV(SPE);
    
    //Ajustando o pino D0, D1 e D2 como saída
    DDRD = 0b00000111; 
    PORTD = 0;
    
    
    int z = 500;
    unsigned char vetor[z];
    int j;

    for(j = 0; j < z; j++){
      vetor[j] = j;
    }

  while(1)
  {
    // Dados para serem enviados ao mestre
    for(j = 0; j < 10; j++){
      SPDR = vetor[z];
      //Recebendo dados do mestre
      while (!(SPSR & (1<<SPIF)));
      
      vetor[j] = SPDR;
      //PORTD = SPDR; 
    }     

     if (t % 2 == 0)
      PORTB |= 0b10000000;
     else
      PORTB &= 0b01111111; 
     
     t++;
  }


}



