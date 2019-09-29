#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int ret;
	long int sum;
	if (argc != 2){
		printf("Failed to open file \n");
		exit(EXIT_FAILURE);
	}
	char *fname = argv[1];
	FILE *fp;
	fp = fopen( fname, "r" );
	if (fp == NULL) {
		printf("Failed to open file %s\n", fname);
		exit(EXIT_FAILURE);
	}
	int x;
	char temp[1024];
	while ((ret=fscanf(fp, "%[^,],%d", temp, &x))!= EOF){
		sum += x;
	}
	sum *= 0.5;
	printf("electric power usage: %ld kWh", sum);
	return 0;
}
