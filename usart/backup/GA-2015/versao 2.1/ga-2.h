
/*
  implementa multiplas variáveis  e
  usa uma variável diferente pra nova população
  seleção por roleta
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>

unsigned int const size_population = 110;
char const size_chromossome = 10; // acima de 31 dá erro
char const N = 1;

unsigned int  MAX_SORT;// // maior valor sorteado


float const txMutacao = 0.05;
float const txElite = 0.1;
float const txCrossover = 0.70;

float const minimo = -100;
float const maximo = 100;

const int MINIMIZE = 1;

void initializePopulation(unsigned int population[][N]);
void getAptidao(float aptidao[], unsigned int population[][N]);
void sortPopulation(unsigned int population[][N], float aptidao[], char esquerda, char direita);
void permutaLinhas(unsigned int population[][size_chromossome], int line1, int line2);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[][N],float aptidao[]);
float feval(float x[]);
float feval_rainhas(float x[]);
void aplicaMutacao(unsigned int population[][N]);
void normalizeChromossome(unsigned int chr[], float chrNorm[]);
void aplicaCrossover(unsigned int population[][N], unsigned int newPopulation[][N],float aptidao[]);
void aplicaCrossover2(unsigned int population[][N], unsigned int newPopulation[][N],float aptidao[]);
float getSumFitness(float aptidao[]);
unsigned char selectChromossome(float aptidao[],float sumFitness);
unsigned char selectChromossome_torneio(float aptidao[]);
void getElite(unsigned int population[][N], unsigned int newPopulation[][N]);
void getNewPopulation(unsigned int population[][N], unsigned int newPopulation[][N], float aptidao[]);
void transferePopulacao(unsigned int population[][N], unsigned int newPopulation[][N], int size_population);
void ga();


/**
*/
void ga(){

   /*unsigned int population[size_population][N];
    unsigned int newPopulation[size_population][N];
    float aptidao[size_population];


    //srand((unsigned) time(NULL));

    initializePopulation(population[][N]);
    getAptidao(aptidao,population[][N]);

    int i,T = 50;
    i = 0;

    while(1){

        getNewPopulation(population,aptidao, newPopulation);
        getAptidao(aptidao,newPopulation);avaliaPopulacao(newPopulation,aptidao);
        transferePopulacao(population,newPopulation,size_population);
        i++;
    }*/
}

/*
*population in
*aptidao in
*newPopulation out

*/
void getNewPopulation(unsigned int population[][N], unsigned int newPopulation[][N], float aptidao[]){
    getElite(population,newPopulation);
    aplicaCrossover(population,newPopulation, aptidao);
    aplicaMutacao(newPopulation);
}
//ok
void transferePopulacao(unsigned int population[][N],unsigned int newPopulation[][N], int size_population){
    int i,j;
    for(i = 0; i < size_population; i++){
        for(j = 0; j < N;j++){
            population[i][j] = newPopulation[i][j];
        }

    }
}

//ok
void initializePopulation(unsigned int population[][N]){
    MAX_SORT = pow(2,size_chromossome)-1;
    char i,j;
    for(i = 0; i < size_population; i++){
        for(j = 0; j < N;j++){
            population[i][j] = rand()%(MAX_SORT);
        }

    }
}

void getElite(unsigned int population[][N], unsigned int newPopulation[][N]){

    int qtdElite = ceil(txElite*size_population);

    int i,j;
    for(i = 0; i < qtdElite; i++){
        for(j = 0; j < N; j++){
            newPopulation[i][j] = population[i][j];
        }

    }
}

/**
Roleta simples
*/
void aplicaCrossover2(unsigned int population[][N], unsigned int newPopulation[][N], float aptidao[]){

    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float sumFitness, cruza;
    int j;

    sumFitness = getSumFitness(aptidao);

    i_newPop = ceil(txElite*size_population);

    while(i_newPop < size_population){

        i1 = selectChromossome(aptidao,sumFitness);
        i2 = selectChromossome(aptidao,sumFitness);

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
                newPopulation[i_newPop][j] = chr1[j];
                newPopulation[i_newPop+1][j] = chr2[j];
            }
            i_newPop += 2;

        }
        else if(i_newPop <= size_population-1){
            for(j = 0; j < N; j++){
                newPopulation[i_newPop][j] = chr1[j];
            }
            i_newPop++;
        }

    }
}

/**
Este método implementa a roleta de quatro pontos
ok
*/
void aplicaCrossover(unsigned int population[][N], unsigned int newPopulation[][N], float aptidao[]){

    unsigned char i1, i2,i3,i4;
    unsigned int chr1[N], chr2[N], chr3[N], chr4[N], i_newPop;
    float sumFitness, cruza;
    int part,j;

    sumFitness = getSumFitness(aptidao);

    i_newPop = ceil(txElite*size_population);

    part = ceil(size_population/4);
    //printf("part: %d\n", part);
    while(i_newPop < size_population){

        //i_newPop++;
        //printf("%d\n", i_newPop);

		i1 = selectChromossome(aptidao,sumFitness);

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
                newPopulation[i_newPop][j] = chr1[j];
                newPopulation[i_newPop+1][j] = chr2[j];
            }
        	i_newPop += 2;

        }
        else if(i_newPop <= size_population-1){
        	for(j = 0; j < N; j++){
                newPopulation[i_newPop][j] = chr1[j];
            }
            i_newPop++;

        }

        if(i_newPop <= size_population-2){
        	for(j = 0; j < N; j++){
                newPopulation[i_newPop][j] = chr3[j];
                newPopulation[i_newPop+1][j] = chr4[j];
            }
            i_newPop += 2;
        }
        else if(i_newPop <= size_population-1){
        	for(j = 0; j < N; j++){
                newPopulation[i_newPop][j] = chr3[j];
            }
            i_newPop++;
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

    unsigned char i1,i2;

    i1 = rand() % size_population;
    i2 = rand() % size_population;

    if(aptidao[i1] >= aptidao[i2]){
        return i1;
    }
    else{
        return i2;
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


void aplicaMutacao(unsigned int population[][N]){
    int i,j;
    float muta;
    for(i = 0; i <= size_population; i++){
        for(j = 0; j < N; j++){
            muta = (rand()%100)/100.0;
            if(muta <= txMutacao){
                mutaCromossomo(&population[i][j]);
            }
        }

    }
}

// Ok
void mutaCromossomo(unsigned int* chr){
    int pos;
    pos = rand()%size_chromossome;
    *chr ^=  (1 << pos);
}

//ok
void avaliaPopulacao(unsigned int population[][N],float aptidao[]){

    int i;

    for(i = 0; i < size_population; i++){
        aptidao[i] *= -1;
    }

    sortPopulation(population,aptidao,0,size_population-1);

    for(i = 0; i < size_population; i++){
        aptidao[i] *= -1;
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
* aptidao out
* population in

    se tipo for igual a zero significa que a busca será pelo máximo valor, se 1, a busca é de minimização
    ok
*/
void getAptidao(float aptidao[], unsigned int population[][N]){

    int i;
    float chromossomeNorm[N];

    float aptidaoMinima,aptidaoMaxima;

    normalizeChromossome(population[0], chromossomeNorm);
    aptidaoMinima = feval(chromossomeNorm);

    for(i = 0; i < size_population; i++){
        normalizeChromossome(population[i],chromossomeNorm);
        aptidao[i] = feval(chromossomeNorm);

        if(aptidao[i] < aptidaoMinima){
            aptidaoMinima = aptidao[i];
        }
    }

    // dá um shift na aptidão para que seja todas positivas
    for(i = 0; i <= size_population;i++){
        aptidao[i] = aptidao[i] - aptidaoMinima;
    }

    /**
    /*Faz com que o cromossomo de menor valor tenha aptidão máxim
    */
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


    //printf("Aptidao Max: %f\n aptidao min: %f",aptidaoMaxima,aptidaoMinima );
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

float feval_rainhas(float x[]){

    int i,j;
    char conflito[N];
    int fitness;

    for(i = 0; i < N; i++){
        conflito[i] = 0;
    }

    fitness = N;
    for(i = 0; i < N; i++){
        for(j = i+1; j< N; j++){
            if(abs(i-j) == abs(x[i]-x[j]) || x[i] == x[j]){
                conflito[i] = 1;
                conflito[j] = 1;
            }
        }

        if(conflito[i]){
            fitness--;
        }
    }

    return fitness;

}

/**Quicksort
 O critério de ordenação é a aptidão do cromossomo
 ordenação ocorre em ordem crescente
*/
void sortPopulation(unsigned int population[][N], float aptidao[], char esquerda, char direita){
    char i, j,k;
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

            for(k = 0; k < N; k++){
                y = population[i][k];
                population[i][k] = population[j][k];
                population[j][k] = y;
            }

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
