#include <stdio.h>
#include <math.h>

int main(void){
	int i, j;
	
	double a[3][3] = {
		{cos(M_PI_2), -sin(M_PI_2), 0}, 
		{sin(M_PI_2), cos(M_PI_2), 0}, 
		{0, 0, 1}
	};
	
	double b[3] = {0.5, 0.5, 0};
	double c[3] = {0, 0, 0};
	
	for (i=0; i<3; i++){
		for (j=0; j<3; j++){
			 c[i] += a[i][j] * b[j];
		}
		printf("y[%d]= %lf\n", i+1, c[i]);
		
	}
	return 0;
}