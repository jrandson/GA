/*
 * FloatToByte.c
 *
 * Created: 28/11/2012 23:29:47
 *  Author: Marcelo Fernandes
 */ 

//#include <avr/io.h>
#include "stdio.h"
#include <stdint.h>

void float_to_bytes(float f, char bytes[4]);
void bytes_to_float(char bytes[4], float *f);
void print_m(int ** m);
void int_to_float(int i, float *f);
void float_to_int(float f, int *i);


int main(void){
	int i = 10;
	float f1 = 12.098434, f2 = 0;

	float_to_int(f1,&i);
	int_to_float(i,&f2);
	printf("f1: %f\n", f1);
	printf("f2: %f\n", f2);
}
	


void print_m(int ** m){
	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}



void testa_float_to_bytes(){
	float f1 = 60.92389123;
	float f2 = 0;

	char bytes[4];
	float_to_bytes(f1, bytes);
	//bytes_to_float(bytes, f2);

	printf("f1: %f\n",f1);
	printf("f2: %f\n",&f2);
}

typedef union{
	float f;
	int i;
	char bytes[4];
} my_union;

void float_to_bytes(float f, char bytes[4]){
	my_union float_u;
	float_u.f = f;
	int i;
	for(i = 0; i < 4; i++){
		bytes[i] = float_u.bytes[i];
	}
}

void bytes_to_float(char bytes[4], float *f){
	my_union float_u;
	int i;
	for(i = 0; i < 4; i++){
		float_u.bytes[i] = bytes[i];
	}

	*f = float_u.f;
}

void float_to_int(float f, int *i){
	my_union float_u;

	float_u.f = f;
	*i = float_u.i;
}

void int_to_float(int i, float *f){
	my_union int_u;
	
	int_u.i = i;
	*f = int_u.f;
}