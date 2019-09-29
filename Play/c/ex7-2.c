
#include <stdio.h>
#include <math.h>

/* define structure */
struct complex{
  double real;
  double imag;
};

void complex_mul(struct complex x, struct complex y, struct complex *z)
{
  /* multiply x and y */
  z->real = (x.real * y.real) - (x.imag * y.imag);
  z->imag = (x.real * y.imag) + (x.imag * y.real);
}

int main(void)
{
  struct complex z, z1, z2;

  z1.real = sqrt(2.0)*cos(M_PI/4.0);
  z1.imag = sqrt(2.0)*sin(M_PI/4.0);
  z2.real = cos(M_PI/2.0);
  z2.imag = sin(M_PI/2.0);

  complex_mul(z1, z2, &z);
  printf("%f %f\n", z.real, z.imag);

  return 0;
}
