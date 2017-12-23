
/*
  multiplas variáveis
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "../pesquisa_ga/ga/versao 2/ga.h"
#include "ga-2.h"
#include <time.h>
//#include <avr/io.h>


unsigned int seed;
void exibeAvancoGeracao(float best[][N], int qtdGen);
void exibeTabuleiro(unsigned int best[]);
void exibeAptidao(float aptidao[], int sizePop);

int main(int argc, char const *argv[]){
    unsigned int population[size_population][N];
    unsigned int newPopulation[size_population][N];
    float aptidao[size_population];

    clock_t t = clock(); 
    srand((unsigned) time(NULL));      
   
    initializePopulation(population);    
    getAptidao(aptidao, population);

    int i,T = 200;
    int j;

    i = 0;
    float best,aux;
    float chrNorm[N];

    best = 0;
    aux = 0;
    while(1){  

        getNewPopulation(population, newPopulation,aptidao);
        getAptidao(aptidao,newPopulation);              

        avaliaPopulacao(newPopulation,aptidao);       
        transferePopulacao(population,newPopulation,size_population);        

        normalizeChromossome(newPopulation[0],chrNorm);
        
        best = feval(chrNorm);
        if(best >= aux){
        	printf("N: %f\n", best);   
        	printf("t:%d\n\n", i);
        	aux = best;
        }        

        if(best == N){
            break;
        }
        
        i++;   
        
    }

    t = clock() - t;
    float elapsed;
    elapsed = ((float)t)/CLOCKS_PER_SEC;

    printf("\n tempo: %f\n",elapsed );
    exibeTabuleiro(newPopulation[0]);
    //exibeAptidao(aptidao, size_population);

    return 0;
}


void exibeTabuleiro(unsigned int best[]){
	int i,j;

	float bestNorm[N];

	normalizeChromossome(best,bestNorm);

	for(i = 0; i < N; i++){
		//printf("%f ", bestNorm[i]);
	}
	printf("\n");
	for(i = 0; i < N; i++){
		printf(" _");
	}
	printf("\n");

	for(i = 0; i < N; i++){
		printf("|");
		for(j = 0; j < N; j++){
			if(best[i] == j){
				printf("R|");
			}
			else{
				printf("_|");
			}
			
		}
		printf("\n");
	}
}

void exibeAvancoGeracao(float best[][N], int qtdGen){
    printf("\n----------------- melhor resultado em cada geração-----------------------\n");
    int i,j;  
    for (i = 0; i < qtdGen;i++){
        printf("%d: ",i);
        for(j = 0; j < N;j++){
            printf("%f ",best[i][j]);
        }
        printf("\n");
        
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

