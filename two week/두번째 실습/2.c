#include <stdio.h>

int main()
{
	int a=0;
	int i=0, j=0, k=0;
	int odd=1, even=2;


	printf("줄을 입력 : ");
	scanf("%d",&a);

	for(i=0; i<=(a/2); i++)
	{
		for(j=0; j<i; j++)
		{
			if(odd>=10)
				odd=1;
			printf("%d ",odd);
			odd = odd+2;
		}
		printf("\n");
		for(k=0; k<i; k++)
		{
			if(even>=10)
				even=0;
			printf(" %d",even);
			even = even+2;
		}
		printf("\n");
		odd=1;
		even=2;
	}
	return 0;
}