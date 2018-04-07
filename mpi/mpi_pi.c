
/* This program approximates pi using the Monte Carlo method 
 * Maria Bamundo 10/15/17
 */

#include <stdio.h>      
#include <stdlib.h>  
#include <math.h>
#include <mpi.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char *argv[]) {
  long num_points, c_points;
  int rank, num_procs, i;
  double drand48();
  double x, y, apx_pi, dist;

  num_points = 0;
  c_points = 0;
  
  //initialize MPI
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  //allocate array for number of points to be gathered from each process
  long *c_points_array = malloc(num_procs * sizeof(long));

  if(rank == 0){
    if(argc != 2){
      fprintf(stderr,"Usage: %s num_points", argv[0]);
      MPI_Abort(MPI_COMM_WORLD,1);
    }
    
    else{
      num_points  = atol(argv[1]);
      printf("Will use %ld points per process", num_points);

    }
  }  
    MPI_Bcast(&num_points, 1,  MPI_LONG, 0, MPI_COMM_WORLD);   
  
  
  //create random points and check if they are in the circle  
    srand48(time(NULL)+rank);
    for(i = 1; i <= num_points; i++){
      x = drand48();
      y = drand48();

      //distance from the origin
      dist = sqrt(x * x + y * y);

      if (dist <= 1){
	c_points++;
      }    
    }
    
    //send points num points in circle to rank 0
    MPI_Gather(&c_points, 1 , MPI_LONG, c_points_array, 1, MPI_LONG, 0,  MPI_COMM_WORLD );
    if( rank == 0){
      double final_apx_pi = 0;
      long max_c_points = 0;
      long min_c_points = c_points_array[0];
      for(i = 0; i< num_procs; i++){
	apx_pi = (double)c_points_array[i] / num_points*4;
	printf("[%d] %ld in circle, pi approx = %f \n", i, c_points_array[i], apx_pi);
	if(c_points_array[i] > max_c_points){
	  max_c_points = c_points_array[i];
	}

	if(c_points_array[i] < min_c_points){
	  min_c_points = c_points_array[i];
	}
	
	 final_apx_pi = apx_pi + final_apx_pi;
      }
      printf("in circle values range from %ld to %ld \n", min_c_points,max_c_points);
      // compute avg of all compute pi vals
      final_apx_pi = final_apx_pi/num_procs;
      printf("Final approximation of pi: %f", final_apx_pi);
    }

    MPI_Finalize();
}
