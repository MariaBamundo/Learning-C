/*
  A simple adder that takes input from the user
  
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
  int x;
  int retval;
  int sum;
  int stop = 1;

  while(stop != 0){
    printf("Enter an integer: ");
    retval = scanf("%d", &x);
    if(retval !=  1) {
      stop = 0;
    }
    else{
    sum = sum + x;
    }
  }
  printf("Sum: %d\n", sum);
  
  return 0;
}
