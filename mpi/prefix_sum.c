/*
*Computes the prefix sum using mpi message passing
*/
#include <time.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int rank,size, i;
  const int root=0;        

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

        //initialize arrays
        int local_array[size];
	int recv_array[size];
	
	//seed random number generator
	srand(time(NULL) + rank);
	
	//poppulate local array
        printf("Process %d array:", rank);	
	for(i=0; i < size; i++){
	  local_array[i] = rand() % 20;
	  printf("%d ", local_array[i]);
	}
	printf("\n");

	//scan
        MPI_Scan(&local_array,&recv_array, size, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);

	//print sum arrays
        printf("Process %d pref sum: ", rank);
	for(i = 0; i < size; i++){
	  printf("%d ", recv_array[i]);
	}
	printf("\n");
	

        MPI_Finalize();
        return 0;
}
