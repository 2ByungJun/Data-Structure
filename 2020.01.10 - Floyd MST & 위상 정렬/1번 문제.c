///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 20��
// ���α׷���   : Floyd�� �ִ� ��� �˰���
//   ��  ��     : p451�� �����Ͽ� Floyd�� �ִ� ��� ���α׷��� �����Ͽ�
//                ��� ����� ������ �°� ����ϴ� ���α׷�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define INF 1000

int **A;         // Floyd�� ����� �ӽù迭
int **weight;    // ���� �迭(���)
int max_num = 0; // ���� ����

// Floyd
void floyd(int n)
{
	int i,j,k; // �ݺ� ����
	int row=0; // 0~6 ���

	// A�� weight ����
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			A[i][j] = weight[i][j];

	// ������� ������ϴ� ����
	for(k=0; k<n; k++)
	{
		// ���
		printf("< %d�� ���� ���� >\n  ",k);
		// �� ���� ǥ��
		while(row < max_num){
			printf(" %2d ",row);
			row++;
		}
		row=0;
		printf("\n");
		printf(" |---------------------------|\n");
		// �� �κ� �ݺ�
		for(i=0; i<n; i++)
		{
			// �� ���� ǥ��
			printf("%d|",i);
			// �� �κ� �ݺ�
			for(j=0; j<n; j++)
			{
				if(A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					printf("*%2d|",A[i][j]);     // ����� �� *��� 
				}
				else
				{
					if( A[i][j] == INF ) // INF�� ���� x���
						printf(" %2 x|");
					else
						printf(" %2d|",A[i][j]); // �ƴ� ��� ����ġ ���
				}
			}
		printf("\n");
		}
		printf(" |---------------------------|\n\n");
	}
}

int main()
{
	char ch;     // v ,e �Ǵ�
	int num;     // ����
	int num_x;   // ���� x 
	int num_y;   // ���� y
	int num_add; // ����ġ
	int i,j;     // �ݺ� ����
	int row=0;   // �� ���� ǥ��

	// ���� ���� fp
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}

	// max_num �� (���ϰ��� ��) ���ϱ�
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v'){
			fscanf(fp, "%d", &num);
			max_num++;  // 0 ~ 6
		}
	}

	// ���� �Ҵ�
	weight = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<max_num; i++){
		weight[i] = (int *)malloc(sizeof(int)*max_num);
	}
	A = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<max_num; i++){
		A[i] = (int *)malloc(sizeof(int)*max_num);
	}

	// �迭 �ʱ�ȭ
	for( i=0; i<max_num; i++){
		for( j=0; j<max_num; j++){
			if( i == j ) // i = j�� 0���� �ʱ�ȭ
				weight[i][j] = 0;
			else         // ������ INF�� �ʱ�ȭ
			    weight[i][j] = INF;
		}
	}

	// weight �迭(���) ����
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v' )             // �ǹ̾��� ����
			fscanf(fp, "%d", &num);
		if( ch == 'e' ){
			fscanf(fp,"%d %d %d",&num_x, &num_y, &num_add);
			weight[num_x][num_y] = num_add; 
			weight[num_y][num_x] = num_add;
		}
	}

	// �ʱ� ���� 
	printf("< �ʱ� ���� >\n  ");
	// �� ���� ǥ��
	while(row < max_num){
		printf(" %2d ",row);
		row++;
	}
	printf("\n");
	printf(" |---------------------------|\n");
	// �� �ݺ�
	for( i=0; i<max_num; i++){
		// �� ���� ǥ��
		printf("%d|",i);
		// �� �ݺ�
		for( j=0; j<max_num; j++){
			if( weight[i][j] == INF ) // INF�� ��� x�� ���
				printf(" %2 x|");
			else                      // ������ ���� ���
				printf("*%2d|",weight[i][j]);
		}
		printf("\n");
	}
	printf(" |---------------------------|\n");

	// Floyd ����
	floyd(max_num);

	// ���� �Ҵ� �ݳ�
	for(i=0; i<max_num; i++) free(weight[i]);
	free(weight);
	for(i=0; i<max_num; i++) free(A[i]);
	free(A);

	// ������ �ݾ��� �� ����
	fclose(fp);
	return 0;
}