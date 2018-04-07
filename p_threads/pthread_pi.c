/* This program approximates pi using the Monte Carlo method 
 * Maria Bamundo 
 */

#include <stdio.h>      
#include <stdlib.h>  
#include <math.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>

/*Global Variabls*/
long num_points;


/*Thread Function which computes points in circle*/
void *thread(void *args){
  double x,y;
  double dist;
  long i;
  /*create random points and check if they are in the circle*/
    long *c_points=(long*)args;
    *c_points = 0;
    for(i = 1; i <= num_points; i++){
      x = drand48();
      y = drand48();

      //distance from the origin                                                
      dist = sqrt(x * x + y * y);

      if (dist <= 1){
        (*c_points)++;
      }
    }
    pthread_exit(0);
}
int main(int argc, char *argv[]) {
  int num_threads = 0;
  int rc;
  num_points = 0;
  srand48(time(NULL)); 
  
  if(argc != 3){
      fprintf(stderr,"Usage: %s num_threads num_points", argv[0]);
  }
    
  else{
      num_threads  = atoi(argv[1]);
      num_points = atol(argv[2]);
      printf("Will use %d threads and %ld points per thread \n",num_threads,  num_points);
  }

  /*create threads*/
  pthread_t children[num_threads];
  long c_points_array[num_threads];
  int i;
  for (i = 0; i < num_threads; i++){
    c_points_array[i] = 0;
    rc = pthread_create(&children[i], NULL, thread, (void *)&(c_points_array[i]));
    if(rc != 0){
      fprintf(stderr,"Could not create child thread %d \n", i);
    }
  }
  //join threads
  for(i = 0; i < num_threads; i++){
    pthread_join(children[i], NULL);
  }

 
    //Main thread computations
      double apx_pi = 0;
      double final_apx_pi = 0;
      long max_c_points = 0;
      long min_c_points = c_points_array[0];
      for(i = 0; i< num_threads; i++){
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
      final_apx_pi = final_apx_pi/num_threads;
      printf("Final approximation of pi: %f \n", final_apx_pi);
    
}
