

/*Esta versão implementa a semnete do rand a partir do contador
 * Cossover efetuado através de operação binária
*/

 /*Alterações feitas nos tipos de dados 05 de junho, 2015*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 #include<time.h>
//#include <avr/io.h>

int const size_population = 50;
int const size_chromossome = 16;
int sumPopulation;

unsigned int const MAX_SORT = 1000; // maior valor sorteado

unsigned char const cross_i = 1;
unsigned char const cross_f = 8;
unsigned char const muta_i = 9;
unsigned char const muta_f = 9;

unsigned int seed;

const float tx_elite = 0.1;
const float tx_cross = 0.8;
const float tx_muta = 0.1;

void initializePopulation(unsigned int population[], int* sumPopulation);
void getAptidao(float aptidao[], float populationNormalized[]);
void ordenaPopulacao(unsigned int population[], float aptidao[], unsigned char left, unsigned char right);
void permutaLinhas(unsigned int population[][size_chromossome], int line1, int line2);
void cruzaCromossomos(int* chr1, int* chr2);
void mutaCromossomo(int* chr);
void avaliaPopulacao(unsigned int population[], float aptidao[],  float minimo, float maximo);
float feval(float x);
void aplicaCrossover(unsigned int population[], unsigned char first_i, unsigned char last_i);
void aplicaMutacao(unsigned int population[], int first_i, int last_i);
void exibeAptidao(float aptidao[]);
float normaliza(unsigned int chr, float minimo, float maximo, unsigned int max_sort);

void exibePopulacao(int* population, int sizePop);
float getMinimoReal(int population[], int sizePop);

int main(void){

	unsigned int population[size_population];
	float aptidao[size_population];
    float maximo, minimo;

    minimo = 5.0;
    maximo = 20.0;

    /*
    TCCR1B |= 0b00000001;
    TCNT1 = 0x0;
    seed = TCNT1;
    srand(seed);
    */

    srand((unsigned) time(NULL));

    initializePopulation(population,&sumPopulation);
    exibePopulacao(population,size_population);

    int i;
    for(i = 0; i < size_population; i++){
        printf("%d\n",population[i]);
    }

	avaliaPopulacao(population,aptidao, minimo, maximo);

	float valorMinimo;
	valorMinimo = aptidao[0];

    //DDRB |= 0b10000000;

    int t;
	t = 0;

	while(t < 1000){
        //seed = TCNT1;
        srand((unsigned) time(NULL));
        srand(seed);
        /*
        if (t % 2 == 0)
            PORTB |= 0b10000000;
        else
            PORTB &= 0b01111111;
        */
        aplicaCrossover(population,cross_i, cross_f);
        aplicaMutacao(population, muta_i, muta_f);
        avaliaPopulacao(population,aptidao,minimo,maximo);
        valorMinimo = aptidao[0];
        t++;
	}

    printf("x:%f, Mínimo:%f\n",normaliza(population[0],minimo,maximo,MAX_SORT),valorMinimo);
    float minReal;
    minReal = 0;//getMinimoReal(population[0],size_population);
    printf("Mínimo real:%f\n",minReal);

    return 0;
}
/**===========================funções de depuração =============================*/

float getMinimoReal(int population[], int sizePop){
    int i;
    float minimo, value;

    minimo = feval(population[0]);
    for(i = 1; i < sizePop; i++){
        value = feval(population[i]);
        if(value < minimo)
            minimo = value;
    }
    return minimo;
}


void exibePopulacao(int population[], int sizePop){
    int i;
	for(i = 0; i < sizePop; i++){
        printf("%d\n",population[i]);
    }
}

/**============================== funções GA ===================================*/




/**medir o tempo dessa função principalmente*/
float feval(float x){
    float valor;
    valor =  (0.05*pow(x,2))*sin(x);
    return valor;
}

void initializePopulation(unsigned int population[], int* sumPopulation){

    char i;
    *sumPopulation = 0;
    for(i = 0; i < size_population; i++){
        population[i] = rand()%(MAX_SORT);//minimo + (maximo-minimo)*rand();
        *sumPopulation += population[i];
    }
}

void getAptidao(float aptidao[], float populationNormalized[]){
    int i;
    for(i = 0; i < size_population; i++){
        aptidao[i] = feval(populationNormalized[i]);
    }
}

/**Quicksort */
void ordenaPopulacao(unsigned int population[], float aptidao[], unsigned char left, unsigned char right) {
    unsigned char i,j,x,y;
    float z;
    i = left;
    j = right;
    x = aptidao[(left+right)/2];

    while( i <= j){
        while(aptidao[i] < x && i < right)
            i++;

        while(aptidao[j] > x && j > left)
            j--;

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
    if(j > left )
        ordenaPopulacao(population,aptidao, left, j);

    if(i < right)
        ordenaPopulacao(population, aptidao , i, right);
}

void aplicaCrossover(unsigned int population[], unsigned char first_i, unsigned char last_i){
    unsigned char N = last_i - first_i+1;
    unsigned char dist = N/4;
    unsigned char ch1,ch2,ch3,ch4;
    int valuePopulation_sort;
    int somaTemp = 0;
    unsigned char i,j,k;

    for(i = first_i; i <= last_i-3; i+=4){

        valuePopulation_sort = rand() % (int) sumPopulation;

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

void cruzaCromossomos(int* chr1, int* chr2){

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

// Ok
void mutaCromossomo(int* chr){
	int pos;
    srand(time(NULL));
    pos = rand()%size_chromossome;
    *chr ^=  (1 << pos);

    return chr;

}

void avaliaPopulacao(unsigned int population[],float aptidao[], float minimo, float maximo){
     ///normaliza vetor aqui

   // printf("max:%f, min:%f\n",maximo,minimo);
    float populationNormalized[size_population];

    int i;
    for(i = 0; i < size_population; i++){
        populationNormalized[i] = normaliza(population[i], minimo, maximo, MAX_SORT);
       // printf("%f\n",populationNormalized[i]);
    }

    getAptidao(aptidao,populationNormalized);

    for(i = 0; i > size_population; i++){
        printf("%f\n",aptidao[i]);
    }
    ordenaPopulacao(population,aptidao,0,size_population-1);
    //printf("------------------------------------\n");
    for(i = 0; i > size_population; i++){
        printf("%f\n",aptidao[i]);
    }
}

float normaliza(unsigned int chr, float minimo, float maximo, unsigned int max_sort){
    float value;
    value = minimo + (maximo - minimo)*chr/(float)MAX_SORT;
    return value;
}



