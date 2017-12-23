#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ga-2.h"
#include <time.h>

int global_var;

global_var = 10;

int main(int argc, char const *argv[])
{
	int n;

	n = get_new_value(15);

	printf("n:%d\n", n);
	printf("n:%d\n", global_var);
	return 0;
}

int get_new_value(int global_var){

	return global_var;
}

	
	
	MPI_Recv(local_population, size_local_population, MPI_UNSIGNED, 0 , 0 , comm, MPI_STATUS_IGNORE);

   /**
   * funções MPI
   * Envia para todos os outros processos
   **/
   MPI_Bcast(void *buf,  int count, MPI_datatype, int root, MPI_COMM_WORLD comm);

   /**
   * Envio de dados de todos os outros processos para um processo específico
   **/
   MPI_Reduce(void * sendbuf, void * recvbuf, int counf, MPI_datatype datatype, MPI_Op MPO_op, int root, MPI_COMM_WORLD comm);

   /**
   * Divide em partes iguais os dados de uma mensagem e distrui entre os processos
   **/
   MPI_Scatter(void * sendbuf, int * sendcount, MPI_Datatype, sendtype, void * recvbuf, int recvcunt, 
      MPI_Datatype recvtype, int root, MPI_COMM_WORLD comm);

   /**
   * Recebe em um único processo um conjunto de dados enviados por todos os outros processos
   **/
   MPI_Gather(void * sendbuf, int * sendcount, MPI_Datatype, sendtype, void * recvbuf, int recvcunt, 
      MPI_Datatype recvtype, int root, MPI_COMM_WORLD comm);

   MPI_Allgather(void * sendbuf, int * sendcount, MPI_Datatype, sendtype, void * recvbuf, int recvcunt, 
      MPI_Datatype recvtype, int root, MPI_COMM_WORLD comm);

   /**
   * MPI data types : http://beige.ucs.indiana.edu/I590/node100.html
   **/