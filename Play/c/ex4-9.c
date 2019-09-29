#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *Dec(int i, char *s);

int main(void)
{
  int a,i;
  char input[100];
  char name[][4] = {"A","B","C","D"};
  char b[100];

  for (i=1;i<=20;i++){
  
    sprintf(b,"%d", i);
    char *ans = Dec(i,b);

    if (i%4 == 1){
      printf("A:");
      fgets(input, 80, stdin);
      input[strlen(input) - 1] = '\0';

      if (!(strcmp(input,ans))){
        continue;
      }
      else {
        printf("B,C,D:Doubt!\n");
        return 0;
      }
    }

    else{
      printf("%s:%s\n", name[(i-1)%4], Dec(i,b));
    }
  }
  return 0;

}


char *Dec (int i, char *s)
{

  if (i%3 == 0){
    if (i%5 == 0){
      return "Fizz Buzz";
    }
    else {
      return "Fizz";
    }
  }
  else if (i%5 == 0){
    return "Buzz";
  }
  else {
    sprintf(s,"%d",i);
    return ("%s",s);
  }
}
