
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

void setup_mstr();

unsigned int seed;

int main(int argc, char const *argv[]){

    
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);

    /*
    * PORTB0 and PORTB1 are output
    * B0 ->  led 
    * B1 -> flag de controle do fitness
    */
    DDRB |= 0b11000000;   

    /* quantidade de processadores*/
    int comm_sz = 4;
    int my_rank = 0;

    int size_local_population = size_population / comm_sz;

    unsigned int population[size_population][N], local_population[size_local_population][N];
    unsigned int new_population[size_population][N];
    float fitness[size_population], local_fitness[size_local_population];
   
    init_population(local_population, size_local_population);  
    get_fitness(local_population, local_fitness, size_local_population);

    int i,T = 10000;
    int j;

    i = 0;

    while(i < T){ 

        gather_population(population, local_population, size_local_population);
        gather_fitness(fitness, local_fitness, size_local_population);

        send_population_bcast(population, size_population);
        send_fitness_bcast(fitness, size_population);

        get_new_population(population, local_population, fitness, size_local_population);
        get_fitness(local_population, local_fitness, size_local_population); 

        
        if (i % 2 == 0)
          PORTB |= 0b10000000;
        else
          PORTB &= 0b01111111;    
        
        i++;           
    }    

    return 0;
}

/*
* sinaliza para espera o escravo esperar até o fitness ser calculado
*/
void set_fitness_flag(int flag){
    if (flag){
        PORTB |= 0b01000000;
    }
    else{
        PORTB &= 0b10111111;
    }
    
}

void setup_mstr(){
    //mestre
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







