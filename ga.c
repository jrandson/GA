#include "ga.h"


void get_new_population(chrsize_t population[][N], float fitness[]){
    chrsize_t best_chromossome[N];
    chrsize_t population_tmp[SIZE_POPULATION][N];

    get_elite(population, best_chromossome, fitness);
    applyCrossover_by_torneio(population, population_tmp,fitness);
    aplicaMutacao(population_tmp);
    transferePopulacao(population, population_tmp);

    uint8_t i;
    for(i = 0; i < N; i++){
        population[0][i] = best_chromossome[i];
    }
}

//ok
void transferePopulacao(chrsize_t population[][N], chrsize_t population_tmp[][N]){
    uint8_t i,j;
    for(i = 0; i < SIZE_POPULATION; i++){
        for(j = 0; j < N;j++){
            population[i][j] = population_tmp[i][j];
        }
    }
}

//ok
void init_population(chrsize_t population[][N]){
    uint8_t i,j;
    for(i = 0; i < SIZE_POPULATION; i++){
        for(j = 0; j < N;j++){
            population[i][j] = rand();
        }
    }
}

void get_elite(chrsize_t population[][N], chrsize_t best_chromossome[N],float fitness[]){
    uint8_t i;
    int best_chromossome_i = 0;

    best_chromossome_i = get_best_chromossome_i(fitness);

    for(i = 0; i < N; i++){
        best_chromossome[i] = population[best_chromossome_i][i];
    }
}

int get_best_chromossome_i(float fitness[]){
    uint8_t i;
    int best_fitness_i = 0;

    for(i = 1; i < SIZE_POPULATION; i++){
        if(fitness[i] < fitness[best_fitness_i]){
            best_fitness_i = i;
        }
    }

    return best_fitness_i;
}

void get_best_chromossome(chrsize_t population[][N], float fitness[], float chromossome[]){
    int chromossome_i;
    chromossome_i = get_best_chromossome_i(fitness);
    normalizeChromossome(population[chromossome_i],chromossome);
}

void applyCrossover_by_torneio(chrsize_t population[][N], chrsize_t population_tmp[][N],float fitness[]){

    uint8_t i1, i2;
    chrsize_t chr1[N], chr2[N];
    uint8_t i,j;
    float cruza;

    for(i = 0; i < SIZE_POPULATION; i += 2){
        i1 = selectChromossome_torneio(fitness);
        i2 = selectChromossome_torneio(fitness);

        for(j = 0; j < N; j++){
            chr1[j] = population[i1][j];
            chr2[j] = population[i2][j];
        }

        cruza = (rand() % 100) / 100.0;

        if(cruza <= txCrossover ){
            for(j = 0; j < N; j++){
                crossover(& chr1[j], & chr2[j]);
            }
        }

        for(j = 0; j < N; j++){
            population_tmp[i][j] = chr1[j];
            population_tmp[i+1][j] = chr2[j];
        }
    }
}

int selectChromossome_torneio(float fitness[]){
    uint16_t i1,i2;

    i1 = rand() & (SIZE_POPULATION - 1);
    i2 = rand() & (SIZE_POPULATION - 1);

    if(fitness[i1] <= fitness[i2]){
        return i1;
    }
    else{
        return i2;
    }
}

void crossover(chrsize_t* chr1, chrsize_t* chr2){
    chrsize_t chr1_ = *chr1;
    chrsize_t chr2_ = *chr2;

    *chr1 = (chr1_ & mask) | (chr2_ & ~mask);
    *chr2 = (chr1_ & ~mask) | (chr2_ & mask);
}


void aplicaMutacao(chrsize_t population[][N]){
    uint8_t i,j;
    int pos;
    for(i = 1; i <= COUNT_MUTE_CHROMOSSOME; i++){
        for(j = 0; j < N; j++){
            pos = rand()%SIZE_CHROMOSSOME;
            population[i][j] ^=  (1 << pos);
        }
    }
}

// Ok
void mutaCromossomo(chrsize_t* chr){
    int pos;
    pos = rand()%SIZE_CHROMOSSOME;
    *chr ^=  (1 << pos);
}


void get_fitness(chrsize_t population[][N], float fitness[]){

    uint8_t i;
    float chromossome_normalized[N];
    for (i = 0; i < SIZE_POPULATION; i++){
        normalizeChromossome(population[i], chromossome_normalized);
        fitness[i] = feval(chromossome_normalized);
    }
}

void normalizeChromossome(chrsize_t chr[], float chrNorm[]){
    uint8_t i;
    for(i = 0; i < N; i++){
        chrNorm[i] = MINIMO + (MAXIMO - MINIMO)*chr[i]/ MAX_SORT;
    }
}

float feval(float x[]){
    //float pi = 3.141592653589793;

    //Zhang Zhang
    //return 21.5 + x[0]*( sin(40*pi*x[0]) + cos(20*pi*x[0]) );
    //return pow(1 - 2*pow(sin(3*pi*x[0]),20) + pow(sin(20*pi*x[0]),20),20);
    //return x[0]*x[1]*exp(-1*pow(x[0]-pi,2) +pow(x[1]-pi,2));

    //return x[0];// 2.0*x[0] + 5.0;

    //Rastrigin’s
    //return 100 + (pow(x[0],2) - 10*cos(2*pi*x[0])) + (pow(x[1],2) - 10*cos(2*pi*x[1]));

    //dist euclidiana
    //return pow(x[0]*x[0] + x[1]*x[1], 0.5);

    return x[0]*x[0] + x[1]*x[1];

}
