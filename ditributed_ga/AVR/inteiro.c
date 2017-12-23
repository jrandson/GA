

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define F_CPU 16000000UL  // 16 MHz

int main();
int  transfere(int srce);
void cruza_c(int *c1, int *c2);
void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2);

int size_chromossome;

int main()
{	

}

void cruzaCromossomos(unsigned int* chr1, unsigned int* chr2){
    unsigned int c1_tmp, c2_tmp, c1_part1, c1_part2, c2_part1, c2_part2;
    //cria uma mascara com tamanho igual a metade do tamanho do cromossomo   
    unsigned char mask = 0; 
    int i;
    for(i = 0; i < size_chromossome/2; i++){
        mask = (mask << 1) | 0b1;
    }    
    
    c1_tmp = *chr1;
    c2_tmp = *chr2;

    c1_part1 = c1_tmp & mask;    
    c1_part2 = (c1_tmp >> 4);
    c2_part1 = c2_tmp & mask;     
    c2_part2 = (c2_tmp >> 4);

    *chr1= (c2_part1 << 4) | (c1_part1);
    *chr2 = (c2_part2 << 4) | (c1_part2);

}

void teste_transfere(){

	unsigned int data_rcv = 0, tmp = 0, data = 2925;
	int i;
	unsigned char mask = 0b1111;
	int size_c = 16;

	printf("dado a ser enviado: %d\n", data);
	printf("dado a ser recebido: %d\n", data_rcv);

	for(i = 0; i < ceil(size_c/4); i++){
		printf("\n");
		tmp = data & mask;
		data = (data >> 4);

		data_rcv |= (tmp << 4*i);		
		printf("extraiu %d. Restou %d \n", tmp, data);
		printf("data_rcv %d \n", data_rcv);
	}
}

int  transfere(int srce){
	int size_c = 16, size_p = 4;
	int tmp = 0;
	int recv = 0;
	unsigned char mask = 0b1111;

	int i;
	for(i = 0; i < ceil(size_c/size_p); i++){	
		printf("srce %d, recv %d \n", srce,recv);	
		tmp = srce & mask;
		srce = (srce >> 4);
		recv |= (tmp << 4*i);
			
	}

	return recv;
}

void cruza_c(int *c1, int *c2){
	int c1_tmp, c2_tmp, c1_part1, c1_part2, c2_part1, c2_part2;
	unsigned char mask = 0b1111;

	c1_tmp = *c1;
	c2_tmp = *c2;

	c1_part1 = c1_tmp & mask;
	
	c1_part2 = (c1_tmp >> 4);

	c2_part1 = c2_tmp & mask; 
	
	c2_part2 = (c2_tmp >> 4);


	*c1= (c2_part1 << 4) | (c1_part1);
	*c2 = (c2_part2 << 4) | (c1_part2);

}
