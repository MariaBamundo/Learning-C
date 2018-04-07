/* This program prints farenheit to celsius conversions.
Maria Bamundo
*/

#include <stdio.h>
int main(int argc, char *argv[]){

  int i;
  double c;
  for(i=-100;i<=1000;i++){
    c=(i-32)/1.8;
    printf("%dF = %lfC\n",i,c);
  }
 
return 0;
}
