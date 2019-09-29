#include <stdio.h>
#include <string.h>

int patatokukashi(char *s);

int main(void){
	int a;
	char input[200];
	printf("Please Word\n");
	fgets(input, 80, stdin);
    input[strlen(input) - 1] = '\0';
	patatokukashi(input);
	return 0;
}

int patatokukashi(char *s){
	int a, i;
	a = strlen(s)/2;
	char word[2*a];
	for(i=0;i<a;++i){
		word[i] = s[2*i];
		word[i+a] = s[2*i+1];
	}
	printf("%s",word);
	return 0;
}