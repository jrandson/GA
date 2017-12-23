#include <avr\io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "C:\PortableGit\projects\GA_MCU\ga-spi-2\ga-3.h"
#include "C:\PortableGit\projects\GA_MCU\ga-spi-2\GA-SPI.h"

/************************************************************************/
/* USART                                                                */
/************************************************************************/
//#define FOSC 1843200 // frequencia de opera��o
//#define  BAUD 9600
//#define MYUBRR FOSC /16/BAUD-1

void config_SPI_master();
void disable_slave(int i);
void enaable_slave(int i);
void send_population_bcast(unsigned int population[][N], int size_population);
void send_fitness_bcast(float fitness[], int size_population);
void gather_fitness(float fitness[]);
void gather_population(unsigned int population[][N]);
float SPI_float(float data);
int main();
void configure_rand();
void activate_slave(int slave);
void identify_slavers();



unsigned int population[SIZE_POPULATION][N];
unsigned int local_population[SZ_LOCAL_POPULATION][N];
unsigned int local_population_tmp[SZ_LOCAL_POPULATION][N];

float fitness[SIZE_POPULATION];
float local_fitness[SZ_LOCAL_POPULATION];


float best_fit;
float best[N];

int i;
int gen = 0;
int main(){

	configure_rand();
	config_SPI_master();

	// sincronismo com os MCUs scravos (l� as sa�das do MCUs escravos)
	DDRA |= 0b11111000;

	init_population(population, SIZE_POPULATION);
	get_fitness(population,fitness,SIZE_POPULATION);

	while(1){

		send_population_bcast(population,SIZE_POPULATION);
		send_fitness_bcast(fitness,SIZE_POPULATION);

		get_new_population(population,local_population,fitness,SZ_LOCAL_POPULATION);
		get_fitness(local_population,local_fitness,SZ_LOCAL_POPULATION);


		gather_population(population);
		gather_fitness(fitness);

		//get_best_chromossome(population,fitness,best,SIZE_POPULATION);
		//best_fit = feval(best);



		gen++;

		if(gen%2){
			PORTA |= (1 << 3);
		}
		else{
			PORTA &= ~(1 << 3);
		}
	}
}


void identify_slavers(){
	activate_slave(1);
	SPI_transfer_int(1);

	activate_slave(2);
	SPI_transfer_int(2);

	activate_slave(3);
	SPI_transfer_int(3);
}

void configure_rand(){
	TCCR1B |= 0b00000001;
	TCNT1 = 0x0;
	unsigned int seed = TCNT1;
	srand(seed);
}

void config_SPI_master(){

	//Ajusta os pinos MOSI (PB2) e CLK (PB1) como sa�da
	DDRB = _BV(PB2) | _BV(PB1);

	//Ajusta os pinos PC0, PC1 e PC2 para sa�da objetivando
	//o controle SS dos escravos
	DDRC = _BV(PC0) | _BV(PC1)| _BV(PC2);
	PORTC = _BV(PC0) | _BV(PC1)| _BV(PC2);

	//bit SPE habilita o SPI
	//bit MSTR = 1 habilita modo mestre
	//bits SPI2X, SPR1 e SPR2 configuram o clock
	SPCR = _BV(SPE) | _BV(MSTR) | (1 << SPI2X); // Hebilita SPI, Meste, Tx clk/2

	//Bit 6: WCOL � Write Collision Flag

}

void activate_slave(int slave){
	PORTC |= (1 << 0) | (1 << 1) | (1 << 2);
	PORTC &= ~(1 << slave);
}

void activate_all_slavers(){
	int i;
	for(i = 0; i < COUNT_SLAVERS; i++){
		PORTC &= ~(1 << i);
	}
}

int slave_is_ready(int slave){
	return PINA & (1 << slave);
}

int all_slavers_are_ready(){
	int i;
	int result = 1;
	for(i = 0; i < COUNT_SLAVERS; i++)
	result *= slave_is_ready(i);

	return result;
}

void send_fitness_bcast(float fitness[], int size_population){
	//activate_all_slavers();
	//send_fitness(fitness,SIZE_POPULATION);
	int i;
	for(i = 0; i < COUNT_SLAVERS; i++){
		activate_slave(i);
		send_fitness(fitness,SIZE_POPULATION);
	}
}

void send_population_bcast(unsigned int population[][N], int size_population){
	//activate_all_slavers();
	//send_population(population,SIZE_POPULATION);
	int i;
	for(i = 0; i < COUNT_SLAVERS; i++){
		activate_slave(i);
		send_population(population,SIZE_POPULATION);
	}
}

void gather_population(unsigned int population[][N]){

	int i, j, k, p;
	unsigned int local_pop_tmp[SZ_LOCAL_POPULATION][N];

	for(i = 0; i < SZ_LOCAL_POPULATION; i++){
		for(j = 0; j < N; j++){
			population[i][j] = local_population[i][j];
		}
	}

	for(p = 0; p < COUNT_SLAVERS; p++){
		while(!slave_is_ready(p));
		activate_slave(p);
		rcve_population(local_population_tmp, SZ_LOCAL_POPULATION);

		for(i = (p+1)*SZ_LOCAL_POPULATION, j = 0; j < SZ_LOCAL_POPULATION; i++, j++){
			for(k = 0; k < N; k++){
				population[i][k]= local_population_tmp[j][k];
			}
		}
	}
}

void gather_fitness(float fitness[]){
	int i,j, p;
	float local_fitness_tmp[SZ_LOCAL_POPULATION];

	for(i = 0; i < SZ_LOCAL_POPULATION; i++){
		fitness[i] = local_fitness[i];
	}

	for(p = 0; p < COUNT_SLAVERS; p++){
		while(!slave_is_ready(p));
		activate_slave(p);
		rcve_fitness(local_fitness_tmp, SZ_LOCAL_POPULATION);

		for(i = (p+1)*SZ_LOCAL_POPULATION, j = 0; j < SZ_LOCAL_POPULATION; i++, j++){
			fitness[i] = local_fitness_tmp[j];
		}
	}
}
