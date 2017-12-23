
/*
  multiplas variáveis
  GA - distribuído
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "C:\PortableGit\projects\GA_MCU\ga-spi\ga-2.h"
#include "C:\PortableGit\projects\GA_MCU\ga-spi\GA_SPI.h"
#include <time.h>
#include <avr/io.h>

void setup_slaver();

unsigned int seed;

int main(int argc, char const *argv[]){

    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);

    DDRB |= 0b10000000;

    int comm_sz = 4;
    int my_rank = 1;
    int size_local_population = size_population / comm_sz;

    unsigned int population[size_population][N], local_population[size_local_population][N];
    float local_fitness[size_local_population];      
   
    init_population(local_population, size_local_population); 
    get_fitness(local_population, local_fitness, size_population); 

    int i,T = 10000;
    int j;

    i = 0;

    while(i < T){ 

        send_local_population_to_mstr(local_population, size_local_population);
        send_local_fitness_to_mstr(local_fitness, size_local_population);

        recv_population_from_mstr(population, size_local_population);

        get_new_population(population, local_population, local_fitness, size_local_population);
        get_fitness(local_population, local_fitness, size_local_population);        
        
        i++;  

        if (i % 2 == 0)
          PORTB |= 0b10000000;
        else
          PORTB &= 0b01111111; 
    }   

    return 0;
}

/*
* ler a porta PB1 sinalizando se o fitness já foi calculado
*/
int fitness_is_ready(){
    return 1;
}

void setup_slaver(){
    //Ajusta o pino MISO (PB4) como saída
    DDRB = _BV(PB4);

    //bit SPE habilita o SPI
    SPCR = _BV(SPE);

    //Ajustando o pino D0, D1 e D2 como saída
    DDRD = 0b00000111; 
    PORTD = 0;
}






