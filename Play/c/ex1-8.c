#include <stdio.h>
#include <limits.h>

int main(void)
{
  printf("signed char: %d -%d\n", SCHAR_MIN, SCHAR_MAX);
  printf("unsigned char: %d -%d\n", 0, UCHAR_MAX);

  printf("signed short int: %d -%d\n", SHRT_MIN, SHRT_MAX);
  printf("unsigned short int: %d -%u\n", 0, USHRT_MAX);

  printf("signed int: %d -%d\n", INT_MIN, INT_MAX);
  printf("unsigned int: %d -%u\n", 0, UINT_MAX);
  
  printf("signed long int: %ld -%ld\n", LONG_MIN, LONG_MAX);
  printf("unsigned long int: %d -%lu\n", 0, ULONG_MAX);
  return 0;
}