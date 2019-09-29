#include <stdio.h>
#include <stdlib.h>

int gcc(int a, int b);

int main(void) 
{ 
	int a, b, n, tmp; 
	
	printf("please input two natural  number.\n"); 
	printf("first number = "); 
	scanf("%d", &a); 
	
	printf("second number = "); 
	scanf("%d", &b); 
	
	if ((a<0)||(b<0)){	
		printf("error\n");
		exit(EXIT_FAILURE);
	}
	if ((a<1)||(b<1)){
		printf("Greatest common factor = 0");
		return 0;
	}
  
	if (a<b){
		tmp = a;
		a = b;
		b = tmp;
	}
  
	n = gcc(a, b);
	printf("Greatest common factor = %d\n", n); 
	return 0; 
}  

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
      