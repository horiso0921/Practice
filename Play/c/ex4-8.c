#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int a, i;
  a = atoi(argv[1]);
  if (argc < 1) {
    printf("error");
    exit(EXIT_FAILURE);
  }
  for (i=1; i <= a;++i){
    if (i%3 == 0){
      if (i%5 == 0){
        printf("Fizz Buzz\n");
      }
      else {
        printf("Fizz\n");
      }
    }
    else if (i%5 == 0){
      printf("Buzz\n");
    }
    else {
      printf("%d\n",i);
        }
  }
  return 0;
}
