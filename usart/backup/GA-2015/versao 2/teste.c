/*
  código utilizado nas mediçoes de cada etapa do GA

  versão de produção

  compilação: gcc arquivo.c -o arquivo -lm
  execução: ./arquivo
*/
/*#include <stdio.h>
#include <stdlib.h>
#include <math.h>*/
#include<time.h> 

//#include <avr/io.h>

void exibe(int vetor[], int tam);
void sortPopulation(unsigned int aptidao[], char esquerda, char direita);

int main(int argc, char const *argv[]) {
  
  float a, b;
  int c;

    a = 10.0;
    b = 4.0;
    c =  a/b;

    printf("%d\n", c);
    return;

  srand((unsigned) time(NULL));  

 

} 

void sortPopulation(unsigned int aptidao[], char esquerda, char direita){
    char i, j;
    int y;
    int pivor,z;

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

            z = aptidao[i];
            aptidao[i] = aptidao[j];
            aptidao[j] = z;

            i++;
            j--;
        }
    }

    if(j > esquerda){
        sortPopulation(aptidao, esquerda, j);
    }

    if(i < direita){
        sortPopulation(aptidao, i, direita);
    }
}

void exibe(int vetor[], int tam){
    printf("\n----------------- vetor\n");
    int i;
    for(i = 0; i < tam; i++){
        printf("%d: %d\n",i,vetor[i]);
    }

    printf("\n------------------------------------------------------------------\n");
}
