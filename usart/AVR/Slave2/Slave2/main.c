/*
 * Slave2.c
 *
 * Created: 22/11/2016 14:46:32
 * Author : Randson
 */ 

#include <avr\io.h>
#include <math.h>;
#include <stdint.h>
#include <util/delay.h>
#include "C:\PortableGit\projects\GA_MCU\ga-spi\ga-2.h"
#include "C:\PortableGit\projects\GA_MCU\ga-spi\GA-SPI.h"

void config_SPI_slaver();
void configure_rand();
void enable_transmission();
void disable_transmission();
int main();

unsigned int population[SIZE_POPULATION][N];
unsigned int new_population[SIZE_POPULATION][N];
float fitness[SIZE_POPULATION];

unsigned int local_population[SZ_LOCAL_POPULATION][N];
float local_fitness[SZ_LOCAL_POPULATION];

float best[N];
float best_fit;

int i;
int gen = 0;
int main(){
	
	configure_rand();
	config_SPI_slaver();
	
	DDRA |= (1 << 0) | (1 << 1);
	PORTA &= ~(1 << 0);
	PORTA &= ~(1 << 1);
	
	int i = 0;
	
	while(1){
		
		rcve_population(population,SIZE_POPULATION);
		rcve_fitness(fitness,SIZE_POPULATION);
		
		//get_new_population(population,local_population,fitness,SZ_LOCAL_POPULATION);
		//get_fitness(local_population,local_fitness,SZ_LOCAL_POPULATION);
				
		//enable_transmission();
		//send_population(local_population,SZ_LOCAL_POPULATION);
		//disable_transmission();
		
		//enable_transmission();
		//send_fitness(local_fitness,SZ_LOCAL_POPULATION);
		//disable_transmission();
		
		//get_best_chromossome(new_population,fitness,best,SIZE_POPULATION);
		//best_fit = feval(best);
		
		gen++;
		
	}
}

void enable_transmission(){
	PORTA |= (1 << 0);
}

void disable_transmission(){
	PORTA &= ~(1 << 0);
}

void config_SPI_slaver(){
	
	//Ajusta o pino MISO (PB3) como saída
	DDRB = _BV(PB3);
	//bit SPE habilita o SPI
	SPCR = _BV(SPE);
}

void configure_rand(){
	TCCR1B |= 0b00000001;
	TCNT1 = 0x0;
	unsigned int seed = TCNT1;
	// EPROM
	srand(seed+2);
}


