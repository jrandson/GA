/* 
 * Compile:  mpicc -g -Wall -o mpi_trap1 mpi_trap1.c
 * Run:      mpiexec -n <number of processes> ./mpi_trap1 
 */
#include <stdio.h>

/* We'll be using MPI routines, definitions, etc. */
#include <mpi.h>
#include "ga-2.h"


int main(void) {
   int my_rank, comm_sz;      
   int source;    

   unsigned int population[size_population][N];
   float fitness[size_population], feval_population[size_population];

   int size_local_population;
   size_local_population = size_population / comm_sz;

   unsigned int local_population[size_local_population][N]; 
   float local_fitness[size_local_population], local_feval_population[size_local_population];

   clock_t t = clock(); 
   srand((unsigned) time(NULL));      

   initializePopulation(population);    
   

   int i,T = 1;
   int j;

   i = 0;
   float best[T][N];
   float chrNorm[N];

   /* Let the system do what it needs to start up MPI */
   MPI_Init(NULL, NULL);

   /* Get my process rank */
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

   /* Find out how many processes are being used */
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
   
   /* compute GA here by each process */

   
   while(i < T){                    

               

      //normalizeChromossome(newPopulation[0],chrNorm);

      //share population and fitness data
      MPI_Bcast( population,  size_population, MPI_UNSIGNED, 0 , MPI_COMM_WORLD);
      //MPI_Bcast( fitnesse,  size_population, MPI_UNSIGNED, 0 , MPI_COMM_WORLD); 

      /* Communication between process*/
      if (my_rank != 0) {  // slavers  

         // calculate its new population part
         get_new_population(population, fitness, local_population, size_local_population);

         MPI_Gather(local_population, size_local_population, MPI_UNSIGNED, population, 
                    local_population, MPI_UNSIGNED, 0, MPI_COMM_WORLD ); 

         //get_feval_population(local_population, local_feval_population, size_local_population);

         //send its population part to the master
         // send its feval population to the master
         
      } 
      else { // master  

         MPI_Gather(local_population, size_local_population, MPI_UNSIGNED, population, 
                    local_population, MPI_UNSIGNED, 0, MPI_COMM_WORLD );                

         // calculate its population part
         get_new_population(population, fitness, local_population, size_local_population);
         get_feval_population(local_population, local_feval_population, size_local_population);



         //increment_population(population, feval_population, i);         
         // receive the population_part from other process
         /*for(i = 0; i < comm_sz; i++){
            increment_population(population,i);
         }*/

         // receive the feval population part from others proccess
         /*for(i = 0; i < comm_sz; i++){
            increment_feval_population(feval_population, i);
         }*/

         //calculate the fitness
         //getFitness(feval_population, fitness, size_population); 


      } 

      MPI_Barrier(MPI_COMM_WORLD);
                
   }
   /* end GA computation*/

   /* Print the result */
   if (my_rank == 0) {

      for(i = 0; i < size_population; i++){
         printf("%d\n", population[i]);
      }
     
   }

   for(j = 0; j < N; j++){
      best[i][j] = chrNorm[j];
   }      

   i++; 
   

   /* Shut down MPI */
   MPI_Finalize();


   return 0;
} /*  main  */

