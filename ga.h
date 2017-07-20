#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

//typedef uint8_t chrsize_t;
//typedef uint16_t chrsize_t;
typedef uint32_t chrsize_t;

#define SIZE_CHROMOSSOME 8*sizeof(chrsize_t)
#define MAX_SORT pow(2,SIZE_CHROMOSSOME)-1

//#define mask 0b11110000;
//#define mask 0b1111111100000000
#define mask 0b11111111111111110000000000000000

// size pop must be one of them: 32, 64, 128 and 256
#define SIZE_POPULATION 64
#define N 2

#define COUNT_MUTE_CHROMOSSOME ceil(SIZE_POPULATION*txMutacao)

float const txMutacao = 0.1;
float const txCrossover = 0.75;

#define MINIMO -50.0 //-5.12;
#define MAXIMO  50.0 //5.12;

void init_population(chrsize_t population[][N]);
void get_fitness(chrsize_t population[][N], float fitness[]);
void crossover(chrsize_t* chr1, chrsize_t* chr2);
void mutaCromossomo(chrsize_t* chr);
float feval(float x[]);
void get_feval_population(chrsize_t population[][N], float feval_population[]);
void aplicaMutacao(chrsize_t population[][N]);
void normalizeChromossome(chrsize_t chr[], float chrNorm[]);
void normalizePopulation(chrsize_t population[][N], float population_norm[][N]);
void applyCrossover_by_torneio(chrsize_t population[][N], chrsize_t population_tmp[][N], float fitness[]);
int selectChromossome_torneio(float fitness[]);
void get_elite(chrsize_t population[][N], chrsize_t best_chromossome[N],float fitness[]);
void get_new_population(chrsize_t population[][N], float fitness[]);
void transferePopulacao(chrsize_t population[][N], chrsize_t population_tmp[][N]);
void get_best_chromossome(chrsize_t population[][N], float fitness[], float chromossome[]);
int  get_best_chromossome_i(float fitness[]);
