#include <stdio.h>

int main()
{

	int a,b;
	int i,j,k;
	a=0,b=0;
	


	printf("ù ���� ���� ������ �Է��Ͻÿ� : ");
	scanf("%d",&a);

	for(i=0; i<a-1; i++){
		printf("\n");
		for(j=0;j<i; j++)
			printf(" ");		
		for(k=0; k<a-i; k++)
			printf(" *");
	}
	for(i=0; i<=a; i++){
		for(j=i;j<a; j++)
			printf(" ");		
		for(k=0; k<i; k++)
			printf(" *");
		printf("\n");
	
	}
	printf("\n");
	return 0;
}


