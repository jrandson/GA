
/*
  código utilizado nas mediçoes de cada etapa do GA

  versão de produção
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>
//#include <avr/io.h>

int const size_population = 60;
int const size_chromossome = 12;
int sumPopulation;

unsigned int MAX_SORT; // maior valor sorteado

/*
10% -> elitismo
80% -> cross
10% -> mutaçao
*/
unsigned char const cross_i = 2;
unsigned char const cross_f = 54;
unsigned char const muta_i = 55;
unsigned char const muta_f = 59;

const float txMutacao = 0.05;


unsigned int seed;

void initializePopulation(unsigned int population[], int* sumPopulation);
void getAptidao(float aptidao[], float populationNormalized[]);
void sortPopulation(unsigned int population[], float aptidao[], char esquerda, char direita);
void permutaLinhas(unsigned int population[][size_chromossome], int line1, int line2);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);
void mutaCromossomo(unsigned int* chr);
void avaliaPopulacao(unsigned int population[], float aptidao[],  float minimo, float maximo);
float feval(float x);
void aplicaCrossover(unsigned int population[], unsigned char first_i, unsigned char last_i);
void aplicaMutacao(unsigned int population[], int first_i, int last_i);
void normalizePopulation(float populationNormalized[],unsigned int population[], int sizePop, float minimo, float maximo, float MAX_SORT);
float normalizeChromossome(unsigned int chr, float minimo, float maximo, unsigned int max_sort);

float validaGA(unsigned int population[], float minimo, float maximo);
void exibePopulacao(int* population, int sizePop);
float getMinimoReal(int population[], int sizePop);
void exibeAptidao(float aptidao[], int sizePop);
void exibePopulacaoNormalizada(float populationNormalized[], int sizePop);
void aplicaMutacao2(unsigned int population[]);

int main(void){
  
    MAX_SORT = pow(2,size_chromossome);
    
    unsigned int population[size_population];
    float aptidao[size_population];
    float maximo, minimo;
    float valorMinimo;

    minimo = -15.0;
    maximo = 20.0;

    /*
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);

    //DDRB |= 0b10000000;
    */

    srand((unsigned) time(NULL));        
    initializePopulation(population,&sumPopulation);    
    avaliaPopulacao(population,aptidao, minimo, maximo);    

    int t;
	t = 0;

	while(t < 100){       
        
          /*
          if (t % 2 == 0)
              PORTB |= 0b10000000;
          else
              PORTB &= 0b01111111;    

           */      
          t++;
          
          aplicaCrossover(population,cross_i, cross_f);             
          aplicaMutacao2(population);          
          avaliaPopulacao(population,aptidao,minimo,maximo);
          
          valorMinimo = aptidao[0];
          
  	}

    validaGA(population, minimo, maximo);
    return 0;
}


/**===========================funções de depuração =============================*/

float validaGA(unsigned int population[], float minimo, float maximo){
    
    float start, end,bestFit, temp;
    start = minimo;
    end = maximo;
    bestFit = feval(start);
    while(start <= end){
    	start += 0.1;
    	temp = feval(start);
    	if(temp < bestFit) bestFit = temp;
    }
    float minimo_x;
    minimo_x = normalizeChromossome(population[0],minimo,maximo,MAX_SORT);
    
    printf("x:%f GA minimo:%f\n",minimo_x, feval(minimo_x));
    
    printf("Mínimo real:%f\n",bestFit);    
}

void exibePopulacao(int population[], int sizePop){
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

void exibePopulacaoNormalizada(float populationNormalized[], int sizePop){
	printf("\n----------------- População normaliza \n------------------------------------------------------------------\n");
    int i;
    for(i = 0; i < sizePop; i++){
        printf("%d: %f\n",i, populationNormalized[i]);
    }

    printf("\n------------------------------------------------------------------\n");
}

/**============================== funções GA ===================================*/

void initializePopulation(unsigned int population[], int* sumPopulation){

    char i;
    *sumPopulation = 0;
    for(i = 0; i < size_population; i++){
        population[i] = rand()%(MAX_SORT);//minimo + (maximo-minimo)*rand();
        *sumPopulation += population[i];
    }
}

void aplicaCrossover(unsigned int population[], unsigned char first_i, unsigned char last_i){
    unsigned char N = last_i - first_i + 1;
    unsigned char dist = N/4;
    unsigned char ch1,ch2,ch3,ch4;
    int valuePopulation_sort;
    int somaTemp = 0;
    unsigned char i,j;

    for(i = first_i; i <= last_i-3; i+=4){

        valuePopulation_sort = rand() % (int) sumPopulation;

        somaTemp = 0;

        for(j = 0; j < size_population; j++){

            somaTemp += population[j];
            if(somaTemp >= valuePopulation_sort){
                ch1 = j;
                somaTemp = 0;
                break;
            }
        }

        ch2 = (ch1 + dist) % N;
        ch3 = (ch1 + 2*dist) % N;
        ch4 = (ch1 + 3*dist) % N;

        cruzaCromossomos(&population[ch1], &population[ch3]);
        cruzaCromossomos(&population[ch2], &population[ch4]);
    }
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

void aplicaMutacao(unsigned int population[], int first_i, int last_i){
    int i;
    for(i = first_i; i <= last_i; i++){
        mutaCromossomo(&population[i]);
    }
}

void aplicaMutacao2(unsigned int population[]){
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

void avaliaPopulacao(unsigned int population[],float aptidao[], float minimo, float maximo){

    float populationNormalized[size_population];

    normalizePopulation(populationNormalized, population,size_population, minimo, maximo, MAX_SORT);

    getAptidao(aptidao,populationNormalized);

    sortPopulation(population,aptidao,0,size_population-1);
}

void normalizePopulation(float populationNormalized[], unsigned int population[], int sizePop, float minimo, float maximo, float MAX_SORT){
	int i;
    for(i = 0; i < size_population; i++){
        populationNormalized[i] = normalizeChromossome(population[i], minimo, maximo, MAX_SORT);
    }
}

float normalizeChromossome(unsigned int chr, float minimo, float maximo, unsigned int max_sort){
    float value;
    value = minimo + (maximo - minimo)*chr/(float)MAX_SORT;
    return value;
}

void getAptidao(float aptidao[], float populationNormalized[]){
  
    int i;
    for(i = 0; i < size_population; i++){
        aptidao[i] = feval(populationNormalized[i]);
    }
}

float feval(float x){
    float valor;
    valor =  x*(0.05*pow(x,2))*sin(10*x);
    //valor = x;//sin(x) + cos(3*x);//(x-3)*(x-20) + 90;
    return valor;
}

/**Quicksort 
 O critério de ordenação é a aptidão do cromossomo
*/
void sortPopulation(unsigned int population[], float aptidao[], char esquerda, char direita){
    char i, j;
    int y;
    float pivor,z;

    i = esquerda;
    j = direita;
    pivor = aptidao[(esquerda + direita) / 2];
    
    while(i <= j)
    {
        while(aptidao[i] < pivor && i < direita)
        {
            i++;
        }
        while(aptidao[j] > pivor && j > esquerda)
        {
            j--;
        }
        if(i <= j)
        {
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
    if(j > esquerda)
    {
        sortPopulation(population,aptidao, esquerda, j);
    }
    if(i < direita)
    {
        sortPopulation(population, aptidao, i, direita);
    }
}



