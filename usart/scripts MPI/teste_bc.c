/* File:       
 *    mpi_hello.c
 *
 * Purpose:    
 *    A "hello,world" program that uses MPI
 *
 * Compile:    
 *    mpicc -g -Wall -std=C99 -o mpi_hello mpi_hello.c
 * Usage:        
 *    mpiexec -n<number of processes> ./mpi_hello
 *
 * Input:      
 *    None
 * Output:     
 *    A greeting from each process
 *
 * Algorithm:  
 *    Each process sends a message to process 0, which prints 
 *    the messages it has received, as well as its own message.
 *
 * IPP:  Section 3.1 (pp. 84 and ff.)
 */
#include <stdio.h>
#include <string.h>  /* For strlen             */
#include <mpi.h>     /* For MPI functions, etc */ 
 #include <time.h>


int main(void) {
   int        comm_sz;               /* Number of processes    */
   int        my_rank;               /* My process rank        */
   int N = 20;              
   int data[N];
   int local_data[5];


   srand((unsigned) time(NULL)); 
   

   /* Start up MPI */
   MPI_Init(NULL, NULL); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 

   if (my_rank == 0){  
      int i;
      for(i = 0; i < N; i++){
         data[i] = rand() % 20;
      }
                    
   } 

   MPI_Bcast(data,N,MPI_UNSIGNED,0,MPI_COMM_WORLD);   

   int k;
   for(k = 0; k < comm_sz; k++){
      if (my_rank == k) { 
         int j;
         printf("eu sou o processo %d\n", my_rank);
         for(j = 0; j < N; j++){
            printf("%d\n", data[j]);
         }   
         printf("------------------------------------------\n");                   
      } 
   }    

   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */

