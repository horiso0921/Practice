#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  unsigned int n, i, b;
  b = 1;
  /* input n from keyboard */
  printf("Please number = ");
  scanf("%u", &n);

  /* error check for zero or negative value */
  if (n <= 0){
    exit(EXIT_FAILURE);
  } 
  for(i=1; i<=n; ++i) { 
    if (4200000000 / i < b){
      exit(EXIT_FAILURE);
    }
    b = b * i;
  }
  printf("factorial of %u is %u\n", n, b);
  return 0;
}
