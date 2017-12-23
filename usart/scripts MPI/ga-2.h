
/*
  implementa multiplas variáveis  e 
  usa uma variável diferente pra nova população
  algoritmo distribuído
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <avr/io.h>

unsigned int const size_population = 20;
char const size_chromossome = 10; // acima de 31 dá erro
char const N = 1;

unsigned int  MAX_SORT;// // maior valor sorteado


float const txMutacao = 0.05;
float const txElite = 0.01;
float const txCrossover = 0.70;

float const minimo = -1000;
float const maximo = 1000;

const int MINIMIZE = 1; 

void initializePopulation(unsigned int population[][N], int size_population);
void getFitness(float feval_population[], float fitness[], int size_population);
void sortPopulation(unsigned int population[][N], float fitness[], char esquerda, char direita);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[][N],float fitness[], int size_population);
float feval(float x[]);
void get_feval_population(unsigned int population[][N], float feval_population[], int size_population);
void aplicaMutacao(unsigned int population[][N], int size_population);
void normalizeChromossome(unsigned int chr[], float chrNorm[]);
void normalizePopulation(unsigned int population[][N], float population_norm[][N], int size_population);
void aplicaCrossover_roleta_4p(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population);
void aplicaCrossover_roleta_simples(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population);
void applyCrossover_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population);
float getSumFitness(float fitness[], int size_population);
unsigned char selectChromossome(float fitness[],float sumFitness, int size_population);
unsigned char selectChromossome_torneio(float fitness[], int size_population);
void getElite(unsigned int population[][N], unsigned int new_population[][N], int size_population);
void get_new_population(unsigned int population[][N], float fitness[] , unsigned int newPopulation[][N], int size_population);
void transferePopulacao(unsigned int population[][N],unsigned int new_population[][N], int size_population);
void ga();


void ga(){

}

/*
*population in
*fitness in
*newPopulation out
*/
void get_new_population(unsigned int population[][N], float fitness[] , unsigned int newPopulation[][N], int size_population){
    getElite(population,newPopulation, size_population);
    //aplicaCrossover_roleta_4p(population,newPopulation, fitness);  
    applyCrossover_by_torneio(population,newPopulation,fitness, size_population);
    //aplicaCrossover_roleta_simples(population,newPopulation, fitness);                              
    aplicaMutacao(newPopulation, size_population); 
}

//ok
void transferePopulacao(unsigned int population[][N],unsigned int new_population[][N], int size_population){
    int i,j;
    for(i = 0; i < size_population; i++){
        for(j = 0; j < N;j++){
            population[i][j] = new_population[i][j];
        }
        
    }
}

//ok
void initializePopulation(unsigned int population[][N], int size_population){
    MAX_SORT = pow(2,size_chromossome)-1;
    char i,j;
    for(i = 0; i < size_population; i++){
        for(j = 0; j < N;j++){
            population[i][j] = rand()%(MAX_SORT);
        }
        
    }
}

void getElite(unsigned int population[][N], unsigned int new_population[][N], int size_population){

    int qtdElite = ceil(txElite*size_population);

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
void aplicaCrossover_roleta_simples(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population){

    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float sumFitness, cruza;
    int j;

    sumFitness = getSumFitness(fitness, size_population);

    i_newPop = ceil(txElite*size_population);

    while(i_newPop < size_population){

        i1 = selectChromossome(fitness,sumFitness, size_population);  
        i2 = selectChromossome(fitness,sumFitness, size_population);      
        
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
        
        if(i_newPop <= size_population-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j]; 
            }
            i_newPop += 2;
            
        }
        else if(i_newPop <= size_population-1){
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
void applyCrossover_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population){

    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float sumFitness, cruza;
    int j;

    sumFitness = getSumFitness(fitness, size_population);

    i_newPop = ceil(txElite*size_population);

    while(i_newPop < size_population){

        i1 = selectChromossome_torneio(fitness, size_population);  
        i2 = selectChromossome_torneio(fitness, size_population);      
        
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
        
        if(i_newPop <= size_population-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j]; 
            }
            i_newPop += 2;
            
        }
        else if(i_newPop <= size_population-1){
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
unsigned char selectChromossome_torneio(float fitness[], int size_population){

    unsigned char i1,i2;

    i1 = rand() % size_population;
    i2 = rand() % size_population;
    
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
void aplicaCrossover_roleta_4p(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population){

    unsigned char i1, i2,i3,i4;
    unsigned int chr1[N], chr2[N], chr3[N], chr4[N], i_newPop;
    float sumFitness, cruza;
    int part,j;

    sumFitness = getSumFitness(fitness, size_population);

    i_newPop = ceil(txElite*size_population);

    part = ceil(size_population/4);
    //printf("part: %d\n", part);
    while(i_newPop < size_population){
    	
        //i_newPop++;
        //printf("%d\n", i_newPop);

		i1 = selectChromossome(fitness,sumFitness, size_population); 		

        i2 = (i1+2*part) % (size_population-1);
        i3 = (i1+part) % (size_population-1);
        i4 = (i1+3*part) % (size_population-1);        
        
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

        
        if(i_newPop <= size_population-2){
            for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j];
                new_population[i_newPop+1][j] = chr2[j]; 
            }
        	i_newPop += 2;
            
        }
        else if(i_newPop <= size_population-1){
        	for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr1[j]; 
            }
            i_newPop++;

        }

        if(i_newPop <= size_population-2){
        	for(j = 0; j < N; j++){
                new_population[i_newPop][j] = chr3[j];
                new_population[i_newPop+1][j] = chr4[j]; 
            }
            i_newPop += 2;
        }
        else if(i_newPop <= size_population-1){
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
unsigned char selectChromossome(float fitness[],float sumFitness, int size_population){
    float valuePopulation_sort, somaTemp;
    unsigned char j, chr;

    valuePopulation_sort = rand() % (int) sumFitness;
    chr = 0;
    for(j = 0; j < size_population; j++){

        somaTemp += fitness[j];
        if(somaTemp >= valuePopulation_sort){
            chr = j;
            somaTemp = 0.0;
            break;
        }
    }

    return chr;
}

float getSumFitness(float fitness[], int size_population){
    char i;
    float fit;
    fit = 0.0;
    for(i = 0; i < size_population; i++){
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
void aplicaMutacao(unsigned int population[][N], int size_population){
    int i,j, chromossome_i, qtd_chromossome, qtd_dim;

    qtd_chromossome = ceil(size_population*txMutacao);

    for(i = 0; i <= qtd_chromossome; i++){
         chromossome_i = rand() % size_population;
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
void avaliaPopulacao(unsigned int population[][N],float fitness[], int size_population){

    int i;  
    
    for(i = 0; i < size_population; i++){
        fitness[i] *= -1;
    }
    
    sortPopulation(population,fitness,0,size_population-1);

    for(i = 0; i < size_population; i++){
        fitness[i] *= -1;
    }
}

/**
* Change the range of population to search space of the problem
**/
void normalizePopulation(unsigned int population[][N], float population_norm[][N], int size_population){
    int i;
    for(i = 0; i < size_population; i++){
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
* 1. normaliza o cromossomo cn = min + (max-min)*(c/MAX-1)
* 2. get feval()
* 3. get gitness()
* ok
*/
void getFitness(float feval_population[], float fitness[], int size_population){

    int i;
    float fitnessMinima,fitnessMaxima, dif;

    for(i = 0; i < size_population; i++){         
        fitness[i] = feval_population[i];        
    }    

    fitnessMinima = fitnessMaxima = fitness[0];

    /**
    * pega o maior e o menor valor de fitness para normalizar entre 0 e 1
    **/
    for(i = 0; i < size_population; i++){
        if(fitness[i] > fitnessMaxima){
            fitnessMaxima = fitness[i];
        }

        if(fitness[i] < fitnessMinima){
            fitnessMinima = fitness[i];
        }
    }

    /**
    /*Faz com que o cromossomo de menor valor tenha aptidão máxim
    */
    if(MINIMIZE){ 
        for(i = 0; i < size_population;i++){
            fitness[i] = (fitnessMaxima - fitness[i])/fitnessMaxima;
        }
    }
    /**
    /*Faz com que o cromossomo de menor valor tenha aptidão mínima
    */
    else{
        dif = fitnessMaxima - fitnessMinima;

        if(dif == 0){
            dif = 1;
        }

        for(i = 0; i < size_population;i++){
            fitness[i] = (fitness[i] - fitnessMinima)/(dif);
        }
    }
}

/**
* get the function value to the population
**/
void get_feval_population(unsigned int population[][N], float feval_population[], int size_population){

    float population_norm[size_population][N];
    int i;

    normalizePopulation(population, population_norm, size_population);    

    for (i = 0; i < size_population; i++){
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

    return valor;
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





