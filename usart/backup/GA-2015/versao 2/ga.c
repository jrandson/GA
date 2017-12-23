
/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "../pesquisa_ga/ga/versao 2/ga.h"
#include "ga-1.1.h"
#include <time.h>
//#include <avr/io.h>

/*
10% -> elitismo
80% -> cross
10% -> mutaçao
*/

unsigned int seed;

float validaGA(unsigned int population[], float minimo, float maximo);
void exibePopulacao(int* population, int sizePop);
float getMinimoReal(int population[], int sizePop);
void exibeAptidao(float aptidao[], int sizePop);
void ga(float* x, float* minimoGA,float* minimoReal);
void initializePopulation2(unsigned int population[]);
void exibePopulacaoNormalizada(int population[], int sizePop);
void testaCrossover(int pop[],int sizePop);
void exibeAvancoGeracao(float best[], int qtdGen);

int main(int argc, char const *argv[]){
    unsigned int population[size_population];
    unsigned int newPopulation[size_population];
    float aptidao[size_population];

    clock_t t = clock(); 
    srand((unsigned) time(NULL));    
   
    initializePopulation(population);
    getAptidao(aptidao,population);
    //exibePopulacaoNormalizada(newPopulation,size_population);

    int i,T = 11;

    i = 0;
    float best[T];
    float soma;
    while(i < T){  

        getNewPopulation(population,newPopulation,aptidao);
        getAptidao(aptidao,newPopulation); 
        
        avaliaPopulacao(newPopulation,aptidao);       
        transferePopulacao(population,newPopulation,size_population);
        
        best[i] = normalizeChromossome(newPopulation[0]);        
        i++;           
    }

    //exibePopulacaoNormalizada(newPopulation,size_population);
    //exibeAptidao(aptidao,size_population); 

    //exibeAvancoGeracao(best,T);    

    printf("\n Minimo: %f\n", feval(best[T-1]));

    t = clock() - t;
    float elapsed;
    elapsed = ((float)t)/CLOCKS_PER_SEC;

    printf("\n tempo: %f\n",elapsed );

    return 0;
}

/**===========================funções de depuração =============================*/

void testaCrossover(int pop[],int sizePop){
    int i;
    unsigned int ch1,ch2,ch1_,ch2_,j;
    for(i = 0; i < 20; i++){
        j = rand()%sizePop;
        ch1 = pop[j];
        j = rand()%sizePop;
        ch2 = pop[j];

        printf("ch1:%d; ch2:%d -- ",ch1,ch2);
        cruzaCromossomos(&ch1, &ch2);
        printf("ch1':%d;ch2':%d\n", ch1,ch2);
    }
}

void exibePopulacao(int population[], int sizePop){
    printf("\n----------------- População-----------------------\n");
    int i;
    for(i = 0; i < sizePop; i++){
        printf("%d: %d\n",i,population[i]);
    }
}

void exibeAptidao(float aptidao[], int sizePop){
    printf("\n----------------- Aptidão\n");
    int i;
    for(i = 0; i < sizePop; i++){
        printf("%d: %f\n",i,aptidao[i]);
    }

    printf("\n------------------------------------------------------------------\n");
}

void exibePopulacaoNormalizada(int population[], int sizePop){
    printf("\n----------------- População normaliza \n------------------------------------------------------------------\n");
    int i;
    float valChr;
    for(i = 0; i < sizePop; i++){
        valChr = normalizeChromossome(population[i]);
        printf("%d: %f\n",i, valChr);
    }

    printf("\n------------------------------------------------------------------\n");
}

void exibeAvancoGeracao(float best[], int qtdGen){
    printf("\n----------------- melhor resultado em cada geração-----------------------\n");
    int i;
  
    for (i = 0; i < qtdGen;i++){
        printf("%f ",feval(best[i]));
    }

}
