
/*
  implementa multiplas variáveis  e
  usa uma variável diferente pra nova população
  algoritmo distribuído

  pode considerar uma maximização ou minização do algoritmo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <avr/io.h>

unsigned int const SIZE_POPULATION = 30;
char const size_chromossome = 10;
char const N = 1;

unsigned int  MAX_SORT;// // maior valor sorteado

float const txMutacao = 0.05;
float const txElite = 0.01;
float const txCrossover = 0.70;

float const minimo = -500;
float const maximo = 100;

const int MINIMIZE = 1;

void init_population(unsigned int population[][N], int SIZE_POPULATION);
void get_fitness(unsigned int population[][N], float fitness[], int SIZE_POPULATION);
void sortPopulation(unsigned int population[][N], float fitness[], char esquerda, char direita);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[][N],float fitness[], int SIZE_POPULATION);
float feval(float x[]);
void get_feval_population(unsigned int population[][N], float feval_population[], int SIZE_POPULATION);
void aplicaMutacao(unsigned int population[][N], int SIZE_POPULATION);
void normalizeChromossome(unsigned int chr[], float chrNorm[]);
void normalizePopulation(unsigned int population[][N], float population_norm[][N], int SIZE_POPULATION);
void aplicaCrossover_roleta_4p(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION);
void aplicaCrossover_roleta_simples(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION);
void applyCrossover_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION);
float getSumFitness(float fitness[], int SIZE_POPULATION);
unsigned char selectChromossome(float fitness[],float sumFitness, int SIZE_POPULATION);
unsigned char selectChromossome_torneio(float fitness[], int SIZE_POPULATION);
void getElite(unsigned int population[][N], unsigned int new_population[][N], int SIZE_POPULATION);
void get_new_population(unsigned int population[][N],unsigned int new_population[][N], float fitness[] , int SIZE_POPULATION);
void transferePopulacao(unsigned int population[][N],unsigned int new_population[][N], int SIZE_POPULATION);
void ga();


void ga(){

}

/*
*population in
*fitness in
*newPopulation out
*/
void get_new_population(unsigned int population[][N],unsigned int new_population[][N], float fitness[] , int SIZE_POPULATION){
    getElite(population,new_population, SIZE_POPULATION);
    //aplicaCrossover_roleta_4p(population,newPopulation, fitness);
    applyCrossover_by_torneio(population,new_population,fitness, SIZE_POPULATION);
    //aplicaCrossover_roleta_simples(population,newPopulation, fitness);
    aplicaMutacao(new_population, SIZE_POPULATION);
}

//ok
void transferePopulacao(unsigned int population[][N],unsigned int new_population[][N], int SIZE_POPULATION){
    int i,j;
    for(i = 0; i < SIZE_POPULATION; i++){
        for(j = 0; j < N;j++){
            population[i][j] = new_population[i][j];
        }

    }
}

//ok
void init_population(unsigned int population[][N], int SIZE_POPULATION){
    MAX_SORT = pow(2,size_chromossome)-1;
    char i,j;
    for(i = 0; i < SIZE_POPULATION; i++){
        for(j = 0; j < N;j++){
            population[i][j] = rand()%(MAX_SORT);
        }
    }
}

void getElite(unsigned int population[][N], unsigned int new_population[][N], int SIZE_POPULATION){

    int qtdElite = ceil(txElite*SIZE_POPULATION);

    int i,j;
    for(i = 0; i < qtdElite; i++){
        for(j = 0; j < N; j++){
            new_population[i][j] = population[i][j];
        }
    }
}

/**
Roleta simples
*/
void aplicaCrossover_roleta_simples(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION){

    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float sumFitness, cruza;
    int j;

    sumFitness = getSumFitness(fitness, SIZE_POPULATION);

    i_newPop = ceil(txElite*SIZE_POPULATION);

    while(i_newPop < SIZE_POPULATION){

        i1 = selectChromossome(fitness,sumFitness, SIZE_POPULATION);
        i2 = selectChromossome(fitness,sumFitness, SIZE_POPULATION);

        for(j = 0; j < N; j++){
            chr1[j] = population[i1][j];
            chr2[j] = population[i2][j];
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
            for(j = 0; j < N; j++){
                cruzaCromossomos(&chr1[j], &chr2[j]);
            }
        }

        if(i_newPop <= SIZE_POPULATION-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j];
            }
            i_newPop += 2;

        }
        else if(i_newPop <= SIZE_POPULATION-1){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
            }
            i_newPop++;
        }

    }
}

/**
 seleção por torneio
*/
void applyCrossover_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION){

    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float sumFitness, cruza;
    int j;

    sumFitness = getSumFitness(fitness, SIZE_POPULATION);

    i_newPop = ceil(txElite*SIZE_POPULATION);

    while(i_newPop < SIZE_POPULATION){

        i1 = selectChromossome_torneio(fitness, SIZE_POPULATION);
        i2 = selectChromossome_torneio(fitness, SIZE_POPULATION);

        for(j = 0; j < N; j++){
            chr1[j] = population[i1][j];
            chr2[j] = population[i2][j];
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
            for(j = 0; j < N; j++){
                cruzaCromossomos(&chr1[j], &chr2[j]);
            }
        }

        if(i_newPop <= SIZE_POPULATION-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j];
            }
            i_newPop += 2;

        }
        else if(i_newPop <= SIZE_POPULATION-1){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
            }
            i_newPop++;
        }

    }
}

/*
Seleção por torneio
*/
unsigned char selectChromossome_torneio(float fitness[], int SIZE_POPULATION){

    unsigned char i1,i2;

    i1 = rand() % SIZE_POPULATION;
    i2 = rand() % SIZE_POPULATION;

    if(fitness[i1] >= fitness[i2]){
        return i1;
    }
    else{
        return i2;
    }
}

/**
Este método implementa a roleta de quatro pontos
ok
*/
void aplicaCrossover_roleta_4p(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int SIZE_POPULATION){

    unsigned char i1, i2,i3,i4;
    unsigned int chr1[N], chr2[N], chr3[N], chr4[N], i_newPop;
    float sumFitness, cruza;
    int part,j;

    sumFitness = getSumFitness(fitness, SIZE_POPULATION);

    i_newPop = ceil(txElite*SIZE_POPULATION);

    part = ceil(SIZE_POPULATION/4);
    //printf("part: %d\n", part);
    while(i_newPop < SIZE_POPULATION){

        //i_newPop++;
        //printf("%d\n", i_newPop);

        i1 = selectChromossome(fitness,sumFitness, SIZE_POPULATION);

        i2 = (i1+2*part) % (SIZE_POPULATION-1);
        i3 = (i1+part) % (SIZE_POPULATION-1);
        i4 = (i1+3*part) % (SIZE_POPULATION-1);

        for(j = 0; j < N; j++){
            chr1[j] = population[i1][j];
            chr2[j] = population[i2][j];
            chr3[j] = population[i3][j];
            chr4[j] = population[i4][j];
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
            for(j = 0; j < N; j++){
                cruzaCromossomos(&chr1[j], &chr2[j]);
            }
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
            for(j = 0; j < N; j++){
                cruzaCromossomos(&chr3[j], &chr4[j]);
            }
        }


        if(i_newPop <= SIZE_POPULATION-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j];
            }
            i_newPop += 2;

        }
        else if(i_newPop <= SIZE_POPULATION-1){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
            }
            i_newPop++;

        }

        if(i_newPop <= SIZE_POPULATION-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr3[j];
                new_population[i_newPop+1][j] = chr4[j];
            }
            i_newPop += 2;
        }
        else if(i_newPop <= SIZE_POPULATION-1){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr3[j];
            }
            i_newPop++;
        }

    }
}

/*
Seleção por roleta simples
*/
unsigned char selectChromossome(float fitness[],float sumFitness, int SIZE_POPULATION){
    float valuePopulation_sort, somaTemp;
    unsigned char j, chr;

    valuePopulation_sort = rand() % (int) sumFitness;
    chr = 0;
    for(j = 0; j < SIZE_POPULATION; j++){

        somaTemp += fitness[j];
        if(somaTemp >= valuePopulation_sort){
            chr = j;
            somaTemp = 0.0;
            break;
        }
    }

    return chr;
}

float getSumFitness(float fitness[], int SIZE_POPULATION){
    char i;
    float fit;
    fit = 0.0;
    for(i = 0; i < SIZE_POPULATION; i++){
        fit  += fitness[i];
    }

    return fit;
}

void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2){

    int chr1_,chr2_;
    int i;
    chr1_ = *chr1;
    chr2_ = *chr2;

    for(i = 0; i < size_chromossome/2; i++){
        if(chr1_ & (1 << i))
            *chr2 |= 1 << i;
        else
            *chr2 &= ~(1 << i);

        if(chr2_ & (1 << i))
            *chr1 |= 1 << i;
        else
            *chr1 &= ~(1 << i);
    }
}

//ok
void aplicaMutacao(unsigned int population[][N], int SIZE_POPULATION){
    int i,j, chromossome_i, qtd_chromossome, qtd_dim;

    qtd_chromossome = ceil(SIZE_POPULATION*txMutacao);

    for(i = 0; i <= qtd_chromossome; i++){
         chromossome_i = rand() % SIZE_POPULATION;
        for(j = 0; j < N; j++){
            mutaCromossomo(&population[chromossome_i][j]);
        }
    }
}

// Ok
void mutaCromossomo(unsigned int* chr){
    int pos;
    pos = rand()%size_chromossome;
    *chr ^=  (1 << pos);
}

/**
* sort the population
* ok
**/
void avaliaPopulacao(unsigned int population[][N],float fitness[], int SIZE_POPULATION){

    int i;

    for(i = 0; i < SIZE_POPULATION; i++){
        fitness[i] *= -1;
    }

    sortPopulation(population,fitness,0,SIZE_POPULATION-1);

    for(i = 0; i < SIZE_POPULATION; i++){
        fitness[i] *= -1;
    }
}

/**
* Change the range of population to search space of the problem
**/
void normalizePopulation(unsigned int population[][N], float population_norm[][N], int SIZE_POPULATION){
    int i;
    for(i = 0; i < SIZE_POPULATION; i++){
        normalizeChromossome(population[i], population_norm[i]);
    }
}

/**
chr[] -> vetor de cromossomos : in
chrNorm[] -> vetor de cromossomos normalizados: out
*/
void normalizeChromossome(unsigned int chr[], float chrNorm[]){

    int i;
    for(i = 0; i < N; i++){
        chrNorm[i] = minimo + (maximo - minimo)*chr[i]/ MAX_SORT;
    }
}

/*
* fitness out
* population in
* se tipo for igual a zero significa que a busca será pelo máximo valor, se 1, a busca é de minimização
* 1. normaliza o cromossomo cn = MIN + (MAX - MIN)*(ci - Min)/(Max - Min)
* 2. get feval()
* 3. get gitness()
* ok
*/
void get_fitness(unsigned int population[][N], float fitness[], int SIZE_POPULATION){

    int i;
    float fitnessMinima,fitnessMaxima, dif;
    float feval_population[SIZE_POPULATION];
    float difMaxMin;
    get_feval_population(population, feval_population, SIZE_POPULATION);

    for(i = 0; i < SIZE_POPULATION; i++){
        fitness[i] = feval_population[i];
    }

    fitnessMinima = fitnessMaxima = fitness[0];

    /**
    * pega o maior e o menor valor de fitness para normalizar entre 0 e 1
    **/
    for(i = 0; i < SIZE_POPULATION; i++){
        if(fitness[i] > fitnessMaxima){
            fitnessMaxima = fitness[i];
        }

        if(fitness[i] < fitnessMinima){
            fitnessMinima = fitness[i];
        }
    }

    difMaxMin = fitnessMaxima - fitnessMaxima;

    if(difMaxMin == 0){
      difMaxMin = 1;
    }


    for(i = 0; i < SIZE_POPULATION;i++){
        fitness[i] = (fitness[i] - fitnessMinima)/difMaxMin;
    }
}

/**
* get the function value to the population
**/
void get_feval_population(unsigned int population[][N], float feval_population[], int SIZE_POPULATION){

    float population_norm[SIZE_POPULATION][N];
    int i;

    normalizePopulation(population, population_norm, SIZE_POPULATION);

    for (i = 0; i < SIZE_POPULATION; i++){
        feval_population[i] = feval(population_norm[i]);
    }
}

float feval(float x[]){ //f(x) = x^2
    float valor;
    int i;
    valor = 0;
    for(i = 0; i < N; i++){
        valor += x[i]*x[i];
    }

    return valor - 201.25;
}

/**Quicksort
 O critério de ordenação é a aptidão do cromossomo
 ordenação ocorre em ordem crescente
*/
void sortPopulation(unsigned int population[][N], float fitness[], char esquerda, char direita){
    char i, j,k;
    int y;
    float pivor,z;

    i = esquerda;
    j = direita;
    pivor = fitness[(esquerda + direita) / 2];

    while(i <= j){

        while(fitness[i] < pivor && i < direita){
            i++;
        }

        while(fitness[j] > pivor && j > esquerda){
            j--;
        }

        if(i <= j){

            for(k = 0; k < N; k++){
                y = population[i][k];
                population[i][k] = population[j][k];
                population[j][k] = y;
            }

            z = fitness[i];
            fitness[i] = fitness[j];
            fitness[j] = z;

            i++;
            j--;
        }
    }

    if(j > esquerda){
        sortPopulation(population,fitness, esquerda, j);
    }

    if(i < direita){
        sortPopulation(population, fitness, i, direita);
    }
}
