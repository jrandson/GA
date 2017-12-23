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
   int data[20];
   int local_data[5];

   /* Start up MPI */
   MPI_Init(NULL, NULL); 

   /* Get the number of processes */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

   /* Get my rank among all the processes */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
   
   
   MPI_Barrier(MPI_COMM_WORLD);

   if (my_rank == 0) {      

      MPI_Gather(local_data, 5, MPI_UNSIGNED, data, 5, MPI_UNSIGNED, 0, MPI_COMM_WORLD); 
      
      printf("----------------------------------------\n");
      int j;
      for(j = 0; j < 20; j++){
         printf("%d\n", data[j]);
      }
      printf("----------------------------------------\n");
                    
   } 
   else{

      int k;
      for(k = 0; k < 5; k++){
         local_data[k] = my_rank*k;
      }   

      MPI_Gather(local_data, 5, MPI_UNSIGNED, data, 5, MPI_UNSIGNED, 0, MPI_COMM_WORLD ); 
   }   
    

   /* Shut down MPI */
   MPI_Finalize(); 

   return 0;
}  /* main */


void scatter(){
   int j,k;
   int        comm_sz;               /* Number of processes    */
   int        my_rank;

   int data[20];
   int local_data[5];

   if (my_rank == 0) { 

      for(j = 0; j < 20; j++){
         data[j] = j*5;
      }   

      MPI_Scatter(data, 5, MPI_UNSIGNED, local_data, 5, MPI_UNSIGNED, 0, MPI_COMM_WORLD ); 

      printf("I am the proccess %d. Theses are my datas \n", my_rank);
      printf("----------------------------------------\n");
      for(k = 0; k < 5; k++){
         printf("%d\n", local_data[k]);
      }
      printf("----------------------------------------\n");              
   } 
   else{

      MPI_Scatter(data, 5, MPI_UNSIGNED, local_data, 5, MPI_UNSIGNED, 0, MPI_COMM_WORLD);  
      printf("I am the proccess %d. Theses are my datas \n", my_rank);
      printf("----------------------------------------\n");
      for(k = 0; k < 5; k++){
         printf("%d\n", local_data[k]);
      }
      printf("----------------------------------------\n");     
   } 

}