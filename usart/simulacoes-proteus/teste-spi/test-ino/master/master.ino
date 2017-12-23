#include <stdio.h>
#include <avr\io.h>
#include <util/delay.h>
#include <SD.h>



#define F_CPU 8000000UL  // 8 MHz

int main()
{

   File fp;
   fp = SD.open("test.txt", FILE_WRITE);
   fp.println("Writing to test.txt...");
   fp.println("testing 1, 2, 3.");
   fp.close();
  
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

    int z = 500;
    unsigned char vetor[z];
    int j;

     
    
    while(1)
    {
        //Transmite dados para o escravo 1
        PORTC = PORTC & 0b00000110;
        for(j = 0; j < z; j++){
          SPDR = vetor[j];
          while (!(SPSR & (1<<SPIF)));
          //Recebe dados do escravo 1
          vetor[j] = SPDR; 
          //PORTA = SPDR;
        }       
        PORTC = PORTC | 0b00000111;         
        // _delay_ms(1000);  
    
    }


}



