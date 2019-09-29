#include <stdio.h>

int main(void){
	int y, m, d, D, Y, C, G;
	
	printf("Please year\n");
	scanf("%d", &y);
	printf("Please month\n");
	scanf("%d", &m);
	printf("Please day\n");
	scanf("%d", &d);
	
	Y = y%100;
	C = y/100;
	G = 5*C+(C/4);
	
	D = ((d + (26*(m+1)/10) + Y + (Y/4) + G + 5) % 7) + 1;
	
	switch (D) {
		case 1:
			printf("It is Monday");
			break;
		case 2:
			printf("It is Tuesday");
			break;
		case 3:
			printf("It is Wednesday");
			break;
		case 4:
			printf("It is Thursday");
			break;
		case 5:
			printf("It is Friday");
			break;
		case 6:
			printf("It is Saturday");
			break;
		case 7:
			printf("It is Sunday");
			break;
	}
	
	return 0;
}
	