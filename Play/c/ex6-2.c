#include <stdio.h>
int main(void)
{
	int *p;
	int q;
	q = 199;
	p = &q;
	*p = 200;
	printf("%d¥n", q);
	return 0;
}