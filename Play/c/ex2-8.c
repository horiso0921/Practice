#include <stdio.h>
#include <stdlib.h>

/* function prototype */
int calc_area_of_rectangular(int l,int w);

int main(void)
{
  int l, w, a;
  /* input L & W from keyboard */
  scanf("%d", &l);
  scanf("%d", &w);
  
  /* error check for zero or negative value */
  if (l <= 0 || w <= 0){
    exit(EXIT_FAILURE);
  } 
  a = calc_area_of_rectangular(l, w);
  printf("L= %d, W= %d, Area= %d\n", l, w, a);
  return 0; 
}

/* calc_area_of_rectangular*/
int calc_area_of_rectangular(int l, int w){
  return l * w;
    }
