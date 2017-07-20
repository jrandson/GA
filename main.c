#include "ga.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

void compute_ga(float best[], int count_gen);

int main(){
  int seed;
  TCCR1B |= 0b00000001;
  TCNT1 = 0x0;
  //seed = TCNT1;
  srand(seed);

  USART_init();
  int compute = 1;

  float tmp_f, send_f[41];
  uint32_t  qtd_gen;
  int i;

  float chromossome[N];

  while(1){
    qtd_gen = USART_rcve_int();
    float best[qtd_gen];

    compute_ga(best,qtd_gen);

    for(i = 0; i < qtd_gen; i++){
      USART_send_float(best[i]);
    }
   }
  return 0;
}

/*
 *    //********************************************
    chromossome[0] = USART_rcve_float();
    tmp_f = feval(chromossome);
    USART_send_float(tmp_f);
    //********************************************
 *
 */
void compute_ga(float best[], int count_gen){

  uint32_t population[SIZE_POPULATION][N];
  float fitness[SIZE_POPULATION];
  float chromossome[N];

  init_population(population, SIZE_POPULATION);
  get_fitness(population, fitness, SIZE_POPULATION);
  int gen = 0;
  while(gen < count_gen){

    get_new_population(population, fitness, SIZE_POPULATION);
    get_fitness(population, fitness, SIZE_POPULATION);

    get_best_chromossome(population, fitness, chromossome, SIZE_POPULATION);
    best[gen] = feval(chromossome);

    gen++;
  }
}
