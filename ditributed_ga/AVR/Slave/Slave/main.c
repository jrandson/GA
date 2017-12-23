#include <avr\io.h>
#include <math.h>;
#include <stdint.h>
#include <util/delay.h>
#include "C:\PortableGit\projects\GA_MCU\ga-spi-2\ga-3.h"
#include "C:\PortableGit\projects\GA_MCU\ga-spi-2\GA-SPI.h"

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

int identity = 0;


int gen = 0;
int main(){
	int i= 0;

	configure_rand();
	config_SPI_slaver();

	DDRA |= (1 << 0) | (1 << 1);
	PORTA &= ~(1 << 0);
	PORTA &= ~(1 << 1);

	for(i = 0; i < SZ_LOCAL_POPULATION; i++){
		local_fitness[i] = 0.5;
	}

	while(1){
		rcve_population(population,SIZE_POPULATION);
		rcve_fitness(fitness,SIZE_POPULATION);

		get_new_population(population,local_population,fitness,SZ_LOCAL_POPULATION);
		get_fitness(local_population,local_fitness,SZ_LOCAL_POPULATION);

		enable_transmission();
		send_population(local_population,SZ_LOCAL_POPULATION);
		disable_transmission();

		enable_transmission();
		send_fitness(local_fitness,SZ_LOCAL_POPULATION);
		disable_transmission();

		//get_best_chromossome(local_population,local_fitness,best,SZ_LOCAL_POPULATION);
		//best_fit = feval(best);

		gen++;

		if(gen%2){
			PORTA |= (1 << 1);
		}
		else{
			PORTA &= ~(1 << 1);
		}
	}
}

void get_identity(int* identity){
	*identity = SPI_transfer_int(0);
}

void enable_transmission(){
	PORTA |= (1 << 0);
}

void disable_transmission(){
	PORTA &= ~(1 << 0);
}

void config_SPI_slaver(){

	//Ajusta o pino MISO (PB3) como sa�da
	DDRB = _BV(PB3);
	//bit SPE habilita o SPI
	SPCR = _BV(SPE);
}

void configure_rand(){
	TCCR1B |= 0b00000001;
	TCNT1 = 0x0;
	unsigned int seed = TCNT1;
	srand(seed);
}
