
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int m, n, i, j;
  double *a, *x, *y;

  if (argc != 3) {
    printf("Usage: %s nrow ncol\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  m = atoi(argv[1]);
  n = atoi(argv[2]);
  a = (double *) malloc(m*n*sizeof(double));
  x = (double *) malloc(n*sizeof(double));
  y = (double *) malloc(m*sizeof(double));

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++)
      a[i*n+j] = 1.0;
  for (i = 0; i < n; i++)
    x[i] = 1.0;

  for (i = 0; i < m; i++) {
    y[i] = 0.0;
    for (j = 0; j < n; j++)
      y[i] += a[i*n+j] * x[j];
  }

  printf("%f\n", y[0]);

  free(a);
  free(x);
  free(y);
}
