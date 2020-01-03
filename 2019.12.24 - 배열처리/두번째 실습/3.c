#include <stdio.h>

int main()
{
	int a;
	int i,j,k,l;

	printf("라인을 입력 : ");
	scanf("%d", &a);

	for(i=0; i<a; i++)
	{
		for(j=0; j<a-i; j++)
		{
			printf(" ");
		}
		for(k=i+1; k>=1; k--)
		{
			printf("%d",k);
		}
		for(l=0; l<i;l++)
		{
			printf("%d",l+2);
		}
		printf("\n");
	}

	return 0;

}
