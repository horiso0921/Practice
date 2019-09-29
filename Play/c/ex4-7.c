#include <stdio.h>
#include <stdlib.h>

int gcc(int a, int b);

int main(int argc, char *argv[])
{ int a, b, n, tmp;
  if (argc < 3){
    printf("the number of number is less\n");
    exit(EXIT_FAILURE);
  }
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  if (a<0||b<0){
    printf("error\n");
    exit(EXIT_FAILURE);
  }
  if ((a<1) || (b<1)){
    printf("Greatest common factor = 0\n");
    return 0;
  }
  /* change a<b */
  if (a<b){
    tmp = a;
    a = b;
    b = tmp;
  }
  /* print */
  n = gcc(a, b);
  printf("Greatest common factor = %d\n", n);
  return 0;
}
/* define gcc*/
int gcc(int a,int b)
{
  int r;
  r = a%b;
  while (r!=0){
    a = b;
    b = r;
    r = a % b;
  }
  return b;
}
