
/*
  multiplas variáveis
  GA - distribuído
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ga-2.h"
#include "GA_SPI.h"
//#include <time.h>
#include <avr/io.h>

void setup_slaver();

unsigned int seed;

int main(int argc, char const *argv[]){

    /*
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);

    //DDRB |= 0b10000000;
    */

    /*
        if (t % 2 == 0)
          PORTB |= 0b10000000;
        else
          PORTB &= 0b01111111;   
    */ 

    int comm_sz = 4;
    int my_rank = 1;
    int size_local_population = size_population / comm_sz;

    unsigned int population[size_population][N], local_population[size_local_population][N];
    float fitness[size_population], local_feval[size_local_population];

    /*
    clock_t t = clock(); 
    srand((unsigned) time(NULL));      
    */
    
    init_population(local_population, size_local_population); 
    get_feval_population(local_population, local_feval, size_population); 

    int i,T = 10000;
    int j;

    i = 0;

    while(i < T){ 

        send_local_population_to_mstr(local_population, size_local_population);
        send_local_feval_to_mstr(local_feval, size_local_population);

        recv_population_from_mstr(population, size_local_population);
        recv_fitness_from_mstr(fitness, size_local_population);

        get_new_population(population, local_population, fitness, size_local_population);
        get_feval_population(local_population, local_feval, size_local_population);        
        
        i++;           
    }    

    /*
    t = clock() - t;
    float elapsed;
    elapsed = ((float)t)/CLOCKS_PER_SEC;

    printf("\n tempo: %f s\n",elapsed );
    */
    
    return 0;
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






