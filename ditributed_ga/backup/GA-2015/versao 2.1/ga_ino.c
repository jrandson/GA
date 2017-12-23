
/*
Versão usada para avaliação no atmega. abr/2016
*/

//#include "../pesquisa_ga/ga/versao 2/ga.h"
#include "ga.h"




unsigned int seed;


int main(int argc, char const *argv[]){
 
    unsigned int population[size_population];
    unsigned int newPopulation[size_population];
    float aptidao[size_population];

    //TCCR1A |= 0b00000001;
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;

    unsigned int seed;
    int t;

    seed = TCNT1;

    srand((unsigned)seed);    
   
    initializePopulation(population);
    getAptidao(aptidao,population);

    DDRB |= 0b10000000;

    t = 0;
    while(1){  
        seed = TCNT1;
        srand(seed);
        if (t % 2 == 0)
            PORTB |= 0b10000000;
        else
            PORTB &= 0b01111111; 

        getNewPopulation(population,aptidao, newPopulation);
        getAptidao(aptidao,newPopulation);avaliaPopulacao(newPopulation,aptidao);       
        transferePopulacao(population,newPopulation,size_population);          
    }

    return 0;
}
