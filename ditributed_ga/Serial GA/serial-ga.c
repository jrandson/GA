
/*
  multiplas variáveis
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "serial-ga.h"
#include <time.h>
//#include <avr/io.h>


unsigned int seed;

float validaGA(unsigned int population[], float minimo, float maximo);
void exibePopulacao(unsigned int population[][N], int sizePop);
float getMinimoReal(int population[], int sizePop);
void exibeAptidao(float aptidao[], int sizePop);

void ga(float* x, float* minimoGA,float* minimoReal);
void initializePopulation2(unsigned int population[]);
void exibePopulacaoNormalizada(unsigned int population[][N], int sizePop);
void exibeAvancoGeracao(float best[][N], int qtdGen);
void initPop(unsigned int pop[][N],int sizePop);
void getApt(unsigned int linha[]);
void showFevalPop(unsigned int population[][N]);
void testaCrossover(unsigned int population[][N], char ch1, char ch2);
void testaNormalizacao(unsigned int pop[][N], int sizePop);

int main(int argc, char const *argv[]){

    /*
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);

    DDRB |= (1 << 7);

	if (t % 2 == 0)
		PORTB |= (1 << 7);
	else
		PORTB &= ~(1 << 7);
    */

    unsigned int population[SIZE_POPULATION][N];
    unsigned int new_population[SIZE_POPULATION][N];
    float fitness[SIZE_POPULATION];

    clock_t t = clock();
    srand((unsigned) time(NULL));

    int i = 0,T = 32;
    int j;
    float best_chromossomes[T][N];
    float chromossome[N];


    init_population(population, SIZE_POPULATION);
    get_fitness(population, fitness, SIZE_POPULATION);

    while(i < T){

        get_new_population(population, new_population,fitness, SIZE_POPULATION);
        get_fitness(new_population,fitness, SIZE_POPULATION);
        transferePopulacao(population,new_population,SIZE_POPULATION);

        //get_best_chromossome(population, fitness, chromossome, SIZE_POPULATION);
        //printf("%d: %f\n", i,feval(chromossome));

        for(j = 0; j < N; j++){
            best_chromossomes[i][j] = chromossome[j];
        }

        i++;
    }

    t = clock() - t;
    float elapsed;
    elapsed = ((float)t)/CLOCKS_PER_SEC;

    exibeAvancoGeracao(best_chromossomes,T);

    printf("\n Minimo: %f\n", feval(chromossome));

    printf("\n tempo: %f\n",elapsed );

    return 0;
}

/**===========================funções de depuração =============================*/



void testaNormalizacao(unsigned int pop[][N], int sizePop){
    int i,j;
    float norm[sizePop][N];

    for(i = 0; i < sizePop; i++){
        normalizeChromossome(pop[i],norm[i]);
    }

    for(i = 0; i < sizePop;i++){
        for(j = 0; j < N; j++){
            printf("%f ", norm[i][j]);
        }
        printf("\n");
    }
}

void testaCrossover(unsigned int population[][N], char ch1, char ch2){
    int i;
    for(i = 0; i < N; i++){
        printf("%d ", population[ch1][i]);
    }
    printf("\n");
    for(i = 0; i < N; i++){
        printf("%d ", population[ch2][i]);
    }
    printf("\n--------------------------\n");

    for(i = 0; i < N; i++){
        cruzaCromossomos(&population[ch1][i],&population[ch2][i]);
    }

    for(i = 0; i < N; i++){
        printf("%d ", population[ch1][i]);
    }
    printf("\n");
    for(i = 0; i < N; i++){
        printf("%d ", population[ch2][i]);
    }
    printf("\n--------------------------\n");
}

void getApt(unsigned int linha[]){
    int i;
    for(i = 0; i < N; i++){
        printf("%d ", linha[i]);
    }
}

void exibeAptidao(float aptidao[], int sizePop){
    printf("\n----------------- Aptidão-----------------------------------------\n");
    int i;
    for(i = 0; i < sizePop; i++){
        printf("%d: %f\n",i,aptidao[i]);
    }

    printf("\n------------------------------------------------------------------\n");
}

void exibePopulacaoNormalizada(unsigned int population[][N], int sizePop){
    printf("\n----------------- População normaliza -------------------------\n");
    int i,j;
    float valChr[N];
    for(i = 0; i < sizePop; i++){
        normalizeChromossome(population[i],valChr);
        for(j = 0; j < N; j++){
            printf("%f ", valChr[j]);
        }
        printf("\n");
    }

    printf("\n------------------------------------------------------------------\n");
}


void exibeAvancoGeracao(float best[][N], int qtdGen){


    printf("\n----------------- melhor resultado em cada geração-----------------------\n");
    int i,j;
    for (i = 0; i < qtdGen;i++){
        printf("%d: ",i);
        for(j = 0; j < N; j++){
            printf("%f ",best[i][j]);
        }
        printf("\n");


    }
}


void exibePopulacao(unsigned int population[][N], int sizePop){
    printf("\n----------------- População-----------------------\n");
    int i,j;
    for(i = 0; i < sizePop; i++){
        printf("%d: ",i);
        for(j = 0; j < N; j++){
            printf("%d ",population[i][j]);
        }
        printf("\n");
    }
}

void showFevalPop(unsigned int population[][N]){
    int i;
    float norm[N];
    for(i = 0; i < SIZE_POPULATION;i++){
        normalizeChromossome(population[i],norm);
        printf("%f\n", feval(norm));
    }
}
