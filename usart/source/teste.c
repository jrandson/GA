#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int teste(int i, int j, int (*inc)(int , int ));
int soma(int i,int j);
int prod(int i, int j);
float compute(float input[], float (*funcao)(float []));
float fitness(float chr[]);
void bit();


int main(int argc, char const *argv[]){
	int i = 8, j = 12;	
	float crm[] = {1.2, 3.4, 1.9};

	printf("%f\n",compute(crm,fitness));

	return 0;
}

void bit(){
	int j = 370497;
	int z = 19;
	int mask = 0b1111;
	int i;
	int v = ceil(z/4.0);
	printf("j:%d\n-----------------\n",j);
	int w = 0;	
	for(i = 0; i < v ;i++){
		//separa cada parte para ser enviada
		printf("%d:%d\n",i, (j >> i*4) & mask);
		//reconstroi o valor enviado
		w |= ((char)((j >> i*4) & mask)<< i*4); 
	}
	printf("---------------------\nj:%d\n", w);
}


int soma(int i,int j){
	return i+j;
}

int prod(int i, int j){
	return i*j;
}

float compute(float input[], float (*funcao)(float [])){
	return funcao(input);
}

float fitness(float chr[]){
	return chr[0]*chr[1]+chr[2];
}

int teste(int i,int j, int (*funcao)(int , int )){
   return funcao(i,j);
}

