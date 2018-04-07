
/*Maria Bamundo 
This program adds the command line parameters 
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
int main(int argc, char *argv[]){
  int i;
  long j;
  long k;
  for(i = 1; i < argc; i++){
   j= strtol(argv[i], NULL, 10);
   k = k+j;
  if(errno){
    fprintf(stderr, "%s You lost.\n", argv[0]);
    exit(1);
  }

  }
  printf("%d\n", k);
}
