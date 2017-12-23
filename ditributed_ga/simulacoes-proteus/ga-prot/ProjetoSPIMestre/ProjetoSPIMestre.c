#include <avr\io.h>
#include <util/delay.h>

#define F_CPU 8000000UL  // 8 MHz

int main()
{
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

unsigned char k1 = 0,k2 = 4, k3 = 7;

while(1)
{
	//Transmite dados para o escravo 1
	PORTC = PORTC & 0b00000110;
	SPDR = k1;
	while (!(SPSR & (1<<SPIF)));
	//Recebe dados do escravo 1
	PORTA = SPDR;

	PORTC = PORTC | 0b00000111;
	 
	 _delay_ms(1000);

	k1++;
	k1=k1%8;

	//Transmite dados para o escravo 2
	PORTC = PORTC & 0b00000101;
	SPDR = k2;
	while (!(SPSR & (1<<SPIF)));
	PORTC = PORTC | 0b00000111;

	//Recebe dados do escravo 2
	PORTA = SPDR;

	_delay_ms(1000);

	k2++;
	k2=k2%8;

	//Transmite dados para o escravo 3
	PORTC = PORTC & 0b00000011;
	SPDR = k3;
	while (!(SPSR & (1<<SPIF)));
	PORTC = PORTC | 0b00000111;

	//Recebe dados do escravo 3
	PORTA = SPDR;

	_delay_ms(1000);

    k3++;
	k3=k3%8;

}


}


