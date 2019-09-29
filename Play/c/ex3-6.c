#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N (10)

int asc(const void *a, const void *b) {
  return *(int *)a - *(int *)b;
}

int main(void){
  int i, a[N], max, sum, b;
  float z[N], c, ave;
  srand (time(NULL));
  for (i = 0; i<10; ++i){
    a[i] = rand()%(10+1);
      }
  c = 0;
  max = a[0];
  ave = 0;
  sum = 0;
  for (i = 0; i<N; ++i){
    if(a[i]>max){
      max = a[i];
    }
    sum += a[i];
  }
  ave = sum/10;
  printf("max %d, ave %f\n", max, ave);
  for (i = 0; i < N ; ++i){
    c += pow(a[i] - ave, 2);
  }
  c /= N;
  c = sqrt(c);
  qsort(a, 10, sizeof(int), asc);
  for (i = 0; i< N ; ++i){
    z[i] = ((a[i]-ave)/c)*10+50;
    for (b = 0; b < a[i]; ++b){  printf("#");
    }
    for (b = a[i]; b <= N; ++b){
      printf(" ");
    }
    printf("(%u)  (%f)\n", a[i], z[i]);
  }
  return 0;
}