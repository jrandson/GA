/*
  código utilizado nas mediçoes de cada etapa do GA

  versão de produção

  compilação: gcc arquivo.c -o arquivo -lm
  execução: ./arquivo
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

//#include <avr/io.h>

  int const w = 4;

void sortPopulation(unsigned int aptidao[], char esquerda, char direita);
void showVector(int vetor[][w], int m);
void fillVector(int vetor[][w],int m);
void testaVetor(int vetor[][w],int l1,int l2);

int main(int argc, char const *argv[]) {
  
  srand((unsigned) time(NULL));  

  int vetor[10][w]; 

  fillVector(vetor,10);
  showVector(vetor,10);
  testaVetor(vetor,0,1);
  showVector(vetor,10);


} 

void testaVetor(int vetor[][w], int l1, int l2){
  int tmp;
  int i;

  for(i = 0; i < w; i++){
      tmp = vetor[l1][i];
      vetor[l1][i] = vetor[l2][i];
      vetor[l2][i] = tmp;    
  }  
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

void showVector(int vetor[][w], int m){
  int i,j;
  printf("\n");
  for(i = 0; i < m; i++){
    printf("%d : ",i);
    for(j = 0; j < w; j++){
      printf("%d ", vetor[i][j]);
    }
    printf("\n");
  }
}

void fillVector(int vetor[][w], int m){

  int i,j;
  for(i = 0; i < m; i++){
    for(j = 0; j < w; j++){
      vetor[i][j] = rand()%20;
    }
  }

}
