
/*
* implementa multiplas variáveis  e
* usa uma variável diferente pra nova população
* algoritmo distribuído
* seleção por torneio
* A elite é constituída do indivíduo mais ápito da ultima geração
* Uso de definers
* Seleção por torneio
* Faz apenas minização da função para efeito de simplicação
*
* a macro COUNT_SLAVERS define o numero de slavers usados no algoritmo
*/

#include <math.h>


#define SIZE_POPULATION 60
#define COUNT_SLAVERS 0
#define SZ_LOCAL_POPULATION SIZE_POPULATION/(COUNT_SLAVERS+1)

#define SIZE_CHROMOSSOME 12
#define  N 1

// maior valor sorteado
#define MAX_SORT (int) pow(2, SIZE_CHROMOSSOME)-1
#define TX_MUTACAO 0.05
#define  TX_CROSSOVER 0.75

/************************************************************************/
/* range de busca do GA                                                 */
/************************************************************************/
#define MINIMO -500.0
#define  MAXIMO 500.0

void init_population(unsigned int population[][N], int size_population);
void get_fitness(unsigned int population[][N], float fitness[], int size_population);
void sortPopulation(unsigned int population[][N], float fitness[], char esquerda, char direita);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void cruzaCromossomos2(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[][N],float fitness[], int size_population);
float feval(float x[]);
void aplicaMutacao(unsigned int population[][N], int size_population);
void normalizeChromossome(unsigned int chr[], float chrNorm[]);
void normalizePopulation(unsigned int population[][N], float population_norm[][N], int size_population);
void select_population_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population);
unsigned char selectChromossome(float fitness[],float sumFitness, int size_population);
unsigned char selectChromossome_torneio(float fitness[], int size_population);
void get_new_population(unsigned int population[][N],unsigned int new_population[][N], float fitness[] , int size_population);
void transferePopulacao(unsigned int population[][N],unsigned int new_population[][N], int size_population);
void get_best_chromossome(unsigned int population[][N], float fitness[], float chromossome[], int size_population);
void getElite(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population);



/*
*population in
*fitness in
*newPopulation out
*/
void get_new_population(unsigned int population[][N],unsigned int new_population[][N], float fitness[] , int size_population){

    getElite(population,new_population, fitness, size_population);
    select_population_by_torneio(population,new_population,fitness, size_population);
    aplicaMutacao(new_population, size_population);
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
void init_population(unsigned int population[][N], int size_population){
    int i,j;
    for(i = 0; i < size_population; i++){
        for(j = 0; j < N; j++){
            population[i][j] = rand()%(MAX_SORT);
        }
    }
}

/*
* A elite é formada pelo único melhor indivíduo da população anteriror
*/
void getElite(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population){

    int i,j;
    // get the optimal chromossome from the last generation
    int best_fitness_i = 0;
    for(i = 1; i < size_population; i++){
        if(fitness[i] < fitness[best_fitness_i]){
            best_fitness_i = i;
        }
    }

    for(j = 0; j < N; j++){
        new_population[0][j] = population[best_fitness_i][j];
    }
}

/**
 seleção por torneio
*/
void select_population_by_torneio(unsigned int population[][N], unsigned int new_population[][N], float fitness[], int size_population){
    unsigned char i1, i2;
    unsigned int chr1[N], chr2[N], i_newPop;
    float cruza;
    int j;

    i_newPop = 1; // o melhor indivíduo da ultima geração

    while(i_newPop < size_population){

        i1 = selectChromossome_torneio(fitness, size_population);
        i2 = selectChromossome_torneio(fitness, size_population);

        for(j = 0; j < N; j++){
            chr1[j] = population[i1][j];
            chr2[j] = population[i2][j];
        }

        cruza = (rand()%100)/100.0;
        if(cruza <= TX_CROSSOVER){
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

unsigned char selectChromossome_torneio(float fitness[], int size_population){
    unsigned char i1,i2;
    char opt;
    int i;

    opt = rand() % size_population;
    for(i = 0; i < 1; i++){
        i = rand() % size_population;
        if(fitness[i] < fitness[opt]){
            opt = i;
        }
    }

    return opt;

}

void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2){
    unsigned int c1_tmp, c2_tmp, c1_part1, c1_part2, c2_part1, c2_part2;
    //cria uma mascara com tamanho igual a metade do tamanho do cromossomo
    unsigned char mask = 0b1;
    int i;
    for(i = 0; i < SIZE_CHROMOSSOME/2; i++){
        mask = (mask << 1) | 0b1;
    }
    int half = SIZE_CHROMOSSOME/2;
    c1_tmp = *chr1;
    c2_tmp = *chr2;

    c1_part1 = c1_tmp & mask;
    c1_part2 = (c1_tmp >> half);
    c2_part1 = c2_tmp & mask;
    c2_part2 = (c2_tmp >> half);

    *chr1= (c2_part1 << half) | (c1_part1);
    *chr2 = (c2_part2 << half) | (c1_part2);
}

//ok
void aplicaMutacao(unsigned int population[][N], int size_population){
    int i,j, chromossome_i, qtd_chromossome;

    qtd_chromossome = ceil(size_population*TX_MUTACAO);

    for(i = 0; i <= qtd_chromossome; i++){
         chromossome_i = rand() % size_population;
		 if(chromossome_i == 0) chromossome_i++;
        for(j = 0; j < N; j++){
            mutaCromossomo(&population[chromossome_i][j]);
        }
    }
}
// Ok
void mutaCromossomo(unsigned int* chr){
    int pos;
    pos = rand()%SIZE_CHROMOSSOME;
    // inverte o bit na posição pos
    *chr ^=  (1 << pos);
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
        chrNorm[i] = MINIMO + (MAXIMO - MINIMO)*chr[i]/ MAX_SORT;
    }
}

/**
* get the function value to the population
**/
void get_fitness(unsigned int population[][N], float fitness[], int size_population){

    float population_norm[size_population][N];
    int i;

    normalizePopulation(population, population_norm, size_population);

    for (i = 0; i < size_population; i++){
        fitness[i] = feval(population_norm[i]);
    }
}


float feval(float x[]){

  float valor = -2.718;
  int i;
  for(i = 0; i < N; i++){
      valor += x[i]*x[i];
  }

  return valor ;
}

/*
* return the best normalized chromossome
*/
void get_best_chromossome(unsigned int population[][N], float fitness[], float chromossome[], int size_population){

    //sortPopulation(population,fitness,0,size_population-1);
    int i;
    int best_fitness_i = 0;
    for(i = 1; i < size_population; i++){
        if(fitness[i] < fitness[best_fitness_i]){
            best_fitness_i = i;
        }
    }
    normalizeChromossome(population[best_fitness_i],chromossome);
}
