
/*
  código utilizado nas mediçoes de cada etapa do GA
  Este código é utlizado para validação de cada etapa do GA
  Não leva em conta seu uso no AT Mega. sua execução ocorre somente no PC
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <avr/io.h>

int const size_population = 100;
int const size_chromossome = 8; // acima de 31 dá erro

unsigned int  MAX_SORT;// // maior valor sorteado


float const txMutacao = 0.1;
float const txElite = 0.1;
float const txCrossover = 0.80;

float const minimo = 0;
float const maximo = 300;

const int MINIMIZE = 1; 

void initializePopulation(unsigned int population[]);
void getAptidao(float aptidao[], unsigned int population[]);
void sortPopulation(unsigned int population[], float aptidao[], char esquerda, char direita);
void permutaLinhas(unsigned int population[][size_chromossome], int line1, int line2);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[],float aptidao[]);
float feval(float x);
void aplicaMutacao(unsigned int population[]);
float normalizeChromossome(unsigned int chr);
void aplicaCrossover(unsigned int population[], unsigned int newPopulation[],float aptidao[]);
void aplicaCrossover2(unsigned int population[], unsigned int newPopulation[],float aptidao[]);
float getSumFitness(float aptidao[]);
unsigned char selectChromossome(float aptidao[],float sumFitness);
unsigned char selectChromossome_torneio(float aptidao[]);
void getElite(unsigned int population[], unsigned int newPopulation[]);
void getNewPopulation(unsigned int population[], float aptidao[], unsigned int newPopulation[]);
void transferePopulacao(unsigned int population[],unsigned int newPopulation[], int size_population);
void ga();

/**
*/
void ga(){
    
    unsigned int population[size_population];
    unsigned int newPopulation[size_population];
    float aptidao[size_population];

    
    //srand((unsigned) time(NULL));    
   
    initializePopulation(population);
    getAptidao(aptidao,population);

    int i,T = 50;
    i = 0;

    while(1){  

        getNewPopulation(population,aptidao, newPopulation);
        getAptidao(aptidao,newPopulation);avaliaPopulacao(newPopulation,aptidao);       
        transferePopulacao(population,newPopulation,size_population);
        i++;        
    }
}

/*
*population in
*aptidao in
*newPopulation out
*/
void getNewPopulation(unsigned int population[], float aptidao[], unsigned int newPopulation[]){
    getElite(population,newPopulation);
    aplicaCrossover2(population,newPopulation, aptidao);                                   
    aplicaMutacao(newPopulation); 
}

void transferePopulacao(unsigned int population[],unsigned int newPopulation[], int size_population){
    int i;
    for(i = 0; i < size_population; i++){
        population[i] = newPopulation[i];
    }
}

void initializePopulation(unsigned int population[]){
    MAX_SORT =  pow(2,size_chromossome)-1;
    char i;
    for(i = 0; i < size_population; i++){
        population[i] = rand()%(MAX_SORT);
    }
}

void getElite(unsigned int population[], unsigned int newPopulation[]){

    int qtdElite = ceil(txElite*size_population);

    int i;
    for(i = 0; i < qtdElite; i++){
        newPopulation[i] = population[i];
    }
}

/**
Roleta simples
*/
void aplicaCrossover(unsigned int population[], unsigned int newPopulation[],float aptidao[]){

    unsigned char i1, i2;
    unsigned int chr1, chr2, i_newPop;
    float sumFitness, cruza;

    sumFitness = getSumFitness(aptidao);

    i_newPop = ceil(txElite*size_population);

    while(i_newPop < size_population){    


        i1 = selectChromossome(aptidao,sumFitness);
        i2 = selectChromossome(aptidao, sumFitness); 

        cruza = (rand()%100)/100.0;

        //aptidao[i1] *= 0.7;
        //aptidao[i2] *= 0.7;

        if(cruza <= txCrossover){
            
            chr1 = population[i1];
            chr2 = population[i2];

            cruzaCromossomos(&chr1, &chr2);      

            newPopulation[i_newPop++] = chr1;            
            if(i_newPop >= size_population){
                break;
            }
            newPopulation[i_newPop++] = chr2;      
        }  
        else{             
            newPopulation[i_newPop++] = population[i1];
            if(i_newPop >= size_population){
                break;
            } 
            newPopulation[i_newPop++] = population[i2];
        }
    }
}

/**
Este método implementa a roleta de quatro pontos
*/
void aplicaCrossover2(unsigned int population[], unsigned int newPopulation[],float aptidao[]){

    unsigned char i1, i2,i3,i4;
    unsigned int chr1, chr2, chr3, chr4, i_newPop;
    float sumFitness, cruza;
    int part;

    sumFitness = getSumFitness(aptidao);

    i_newPop = ceil(txElite*size_population);

    part = ceil(size_population/part);

    while(i_newPop < size_population){
    	i1 = selectChromossome(aptidao,sumFitness);        
        i2 = (i1+2*part) % (size_population-1);
        i3 = (i1+part) % (size_population-1);
        i4 = (i1+3*part) % (size_population-1);        

        chr1 = population[i1];
        chr2 = population[i2];
        chr3 = population[i3];
        chr4 = population[i4];

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
        	cruzaCromossomos(&chr1, &chr2);     
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= txCrossover){
        	cruzaCromossomos(&chr3, &chr4);     
        }

        if(i_newPop <= size_population-2){
        	newPopulation[i_newPop++] = chr1;
        	newPopulation[i_newPop++] = chr2;
        }
        else if(i_newPop <= size_population-1){
        	newPopulation[i_newPop++] = chr1;
        }

        if(i_newPop <= size_population-2){
        	newPopulation[i_newPop++] = chr3;
        	newPopulation[i_newPop++] = chr4;
        }
        else if(i_newPop <= size_population-1){
        	newPopulation[i_newPop++] = chr3;
        }        
    }
}

/*
Seleção por roleta simples
*/
unsigned char selectChromossome(float aptidao[],float sumFitness){
    float valuePopulation_sort, somaTemp;
    unsigned char j, chr;

    valuePopulation_sort = rand() % (int) sumFitness;
    chr = 0;
    for(j = 0; j < size_population; j++){

        somaTemp += aptidao[j];
        if(somaTemp >= valuePopulation_sort){
            chr = j;
            somaTemp = 0.0;
            break;
        }
    }

    return chr;
}

/*
Seleção por torneio
*/
unsigned char selectChromossome_torneio(float aptidao[]){

    unsigned int chr1,chr2;

    chr1 = rand() % size_population;
    chr2 = rand() % size_population;
    
    if(aptidao[chr1] >= aptidao[chr2]){
        return chr1;
    }
    else{
        return chr2;
    }
}

float getSumFitness(float aptidao[]){
    char i;
    float fit;
    fit = 0.0;
    for(i = 0; i < size_population; i++){
        fit  += aptidao[i];
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

void aplicaMutacao(unsigned int population[]){
    int i;
    float muta;
    for(i = 0; i <= size_population; i++){
        muta = (rand()%100)/100.0;
        if(muta <= txMutacao){
            mutaCromossomo(&population[i]);
        }        
    }
}

// Ok
void mutaCromossomo(unsigned int* chr){
    int pos;    
    pos = rand()%size_chromossome;
    *chr ^=  (1 << pos);
}

void avaliaPopulacao(unsigned int population[],float aptidao[]){

    getAptidao(aptidao,population);
    int i;
    
    
    for(i = 0; i < size_population; i++){
        aptidao[i] *= -1;
    }
    
    sortPopulation(population,aptidao,0,size_population-1);

    for(i = 0; i < size_population; i++){
        aptidao[i] *= -1;
    }
}


float normalizeChromossome(unsigned int chr){

    float value;
    value = minimo + (maximo - minimo)*chr/ MAX_SORT;
    return value;
}

/*
* aptidao out
* population in

    se tipo for igual a zero significa que a busca será pelo máximo valor, se 1, a busca é de minimização
    ok
*/
void getAptidao(float aptidao[], unsigned int population[]){

    int i;
    float chromossomeNorm;

    float aptidaoMinima,aptidaoMaxima;

    chromossomeNorm = normalizeChromossome(population[0]);    
    aptidaoMinima = feval(chromossomeNorm);

    for(i = 0; i < size_population; i++){
        chromossomeNorm = normalizeChromossome(population[i]);          
        aptidao[i] = feval(chromossomeNorm);    

        if(aptidao[i] < aptidaoMinima){
            aptidaoMinima = aptidao[i];            
        }        
    }    

    // dá um shift na aptidão para que seja todas positivas
    for(i = 0; i <= size_population;i++){
        aptidao[i] = aptidao[i] - aptidaoMinima;
    }

    if(MINIMIZE){
        aptidaoMaxima = aptidao[0];
        for(i = 0; i < size_population; i++){
            if(aptidao[i] > aptidaoMaxima){
            aptidaoMaxima = aptidao[i];
        }

        }
        for(i = 0; i < size_population;i++){
            aptidao[i] = (aptidaoMaxima - aptidao[i])/aptidaoMaxima;
        }
    }

    
    //printf("Aptidao Max: %f\n aptiao min: %f",aptidaoMaxima,aptidaoMinima );
}

float feval(float x){
    float valor;
    valor = x*x;
    //valor =  50*x*x;
    //valor = (0.05*pow(x,2))*sin(x);
    //valor = pow(x-5,2);//sin(0.2*x) + cos(0.8*x);//(x-3)*(x-20) + 90;
    //valor = x*x*cos(0.5*x);
    return valor;
}

/**Quicksort 
 O critério de ordenação é a aptidão do cromossomo
 ordenação ocorre em ordem crescente
*/
void sortPopulation(unsigned int population[], float aptidao[], char esquerda, char direita){
    char i, j;
    int y;
    float pivor,z;

    i = esquerda;
    j = direita;
    pivor = aptidao[(esquerda + direita) / 2];
    
    while(i <= j){

        while(aptidao[i] < pivor && i < direita){
            i++;
        }

        while(aptidao[j] > pivor && j > esquerda){
            j--;
        }

        if(i <= j){
            y = population[i];
            population[i] = population[j];
            population[j] = y;

            z = aptidao[i];
            aptidao[i] = aptidao[j];
            aptidao[j] = z;

            i++;
            j--;
        }
    }

    if(j > esquerda){
        sortPopulation(population,aptidao, esquerda, j);
    }

    if(i < direita){
        sortPopulation(population, aptidao, i, direita);
    }
}



