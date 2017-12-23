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
void ordenaPopulacao(unsigned int population[], float aptidao[], unsigned char left, unsigned char right){
    unsigned char r;
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
