///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 3��
// ���α׷���   : ����� ���
//   ��  ��     : Data.txt ���Ͽ� �ִ� 3���� ����� ���� �������� ����
//                2�� �迭�� �����ϰ� ����� ���� ������ ����ϰ� ���.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h> // malloc�� �������� ���̺귯�� �Լ�

int main()
{
	int row1,col1; // 1����� ��� ��
	int row2,col2; // 2����� ��� ��
	int row3,col3; // 3����� ��� ��
	char name1,name2,name3; // ����� �̸��� ���Ͽ��� �о� ������ ����
	char cal[10]; // ����� ������ �о �����ų �迭

	int **tempA; // A����� �����������Ҵ�迭
	int **tempB; // B����� �����������Ҵ�迭
	int **tempC; // C����� �����������Ҵ�迭
	int **sum_temp; // ����� ������ ������ �����������Ҵ� �迭����
	int i,j,z;  // �ݺ��� ������ ����
	char fpline[5]; // ���� �������� �� ��ġ�� �������� �迭����

	FILE *fp = fopen("data3.txt","r"); // data3 ������ ���� �� ����
	if(fp==NULL)                       // ���� ������ ��� ����
	{
		printf("������ ���� ���߽��ϴ�.\n");
		return 0;
	}

	// A ��� ( ����� �̸��� �����ϰ� A�� �����Ͽ� �ּ��� �޾ҽ��ϴ�. )
	fscanf( fp , "%c%d%d",  &name1 , &row1, &col1 ); // ���� ù° ���� �о� ����� �̸��� ũ�⸦ �� ������ ����
	if ( row1 != col1 ){                             // ��� ���� �ٸ� �� ��� ����
		printf("����� ũ�Ⱑ ���� �ʽ��ϴ�!\n");
		return 0;
	}
	printf("%c��� ======================================\n",name1); // name1(=A) ��� ���
	tempA = (int**) malloc(sizeof(int *) * row1);  // tempA ������ ���� �޸� �Ҵ�
	for(i = 0; i < row1; i++)   // ��ũ�⸸ŭ �ݺ���
	{
		tempA[i] = (int*) malloc(sizeof(int ) * col1); // ����ŭ ���� �޸� �Ҵ�
	}
	// tmepA ����� ǥ��
	for(i=0; i<row1; i++)       // tempA ����� ���Ͽ��� �޾ƿ��� �ݺ���
	{
		for(j=0; j<col1; j++)
		{
			fscanf(fp,"%d",&tempA[i][j]);
		}
	}
	for(i=0; i<row1; i++)       // tempA ����� ������ִ� �ݺ���
	{
		for(j=0; j<col1; j++)
		{
			printf("%3d      ",tempA[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // ���� ����Ŀ���� ��ġ�� A����� ��������ġ�� B����� �������������� �ٹٲٱ� ����

	// B ��� ( ����� �̸��� �����ϰ� B�� �����Ͽ� �ּ��� �޾ҽ��ϴ�. )
	fscanf( fp , "%c%d%d",  &name2 , &row2, &col2 ); // ���� ù° ���� �о� ����� �̸��� ũ�⸦ �� ������ ����
	if ( row2 != col2 ){                             // ��� ���� �ٸ� �� ��� ����
		printf("����� ũ�Ⱑ ���� �ʽ��ϴ�!\n");
		return 0;
	}
	printf("%c��� ======================================\n",name2 ); // name2(=B) ��� ���
	tempB = (int**) malloc(sizeof(int *) * row2);  // tempB ������ ���� �޸� �Ҵ�
	for(i = 0; i < row2; i++)   // ��ũ�⸸ŭ �ݺ���
	{
		tempB[i] = (int*) malloc(sizeof(int ) * col2); // ����ŭ ���� �޸� �Ҵ�
	}
	// tmepB ����� ǥ��
	for(i=0; i<row2; i++)       // tempB ����� ���Ͽ��� �޾ƿ��� �ݺ���
	{
		for(j=0; j<col2; j++)
		{
			fscanf(fp,"%d",&tempB[i][j]);
		}
	}
	for(i=0; i<row2; i++)       // tempB ����� ������ִ� �ݺ���
	{
		for(j=0; j<col2; j++)
		{
			printf("%3d      ",tempB[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // ���� ����Ŀ���� ��ġ�� B����� ��������ġ�� C����� �������������� �ٹٲٱ� ����

	// C ��� ( ����� �̸��� �����ϰ� C�� �����Ͽ� �ּ��� �޾ҽ��ϴ�. )
	fscanf( fp , "%c%d%d",  &name3 , &row3, &col3 ); // ���� ù° ���� �о� ����� �̸��� ũ�⸦ �� ������ ����
	if ( row3 != col3 ){                             // ��� ���� �ٸ� �� ��� ����
		printf("����� ũ�Ⱑ ���� �ʽ��ϴ�!\n");
		return 0;
	}
	printf("%c��� ======================================\n",name3); // name3(=C) ��� ���
	tempC = (int**) malloc(sizeof(int *) * row3);  // tempC ������ ���� �޸� �Ҵ�
	for(i = 0; i < row3; i++)    // ��ũ�⸸ŭ �ݺ���
	{
		tempC[i] = (int*) malloc(sizeof(int ) * col3); // ����ŭ ���� �޸� �Ҵ�
	}
	// tmepC ����� ǥ��
	for(i=0; i<row3; i++)       // tempC ����� ���Ͽ��� �޾ƿ��� �ݺ���
	{
		for(j=0; j<col3; j++)
		{
			fscanf(fp,"%d",&tempC[i][j]);
		}
	}
	for(i=0; i<row3; i++)       // tempC ����� ������ִ� �ݺ���
	{
		for(j=0; j<col3; j++)
		{
			printf("%3d      ",tempC[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // ���� ����Ŀ���� ��ġ�� C����� ��������ġ�� ��� ������ �������������� �ٹٲٱ� ����

	// ��� ����
	while(!feof(fp)) // C����� ���� �������� ������ ������ �о��ش�
	{
		fscanf(fp , "%s", &cal); // fscanf�� ������ �о��ش�.
		printf("%s��� ======================================\n",cal); // ���� ����cal�� ���
		sum_temp = (int**) malloc(sizeof(int *) * row1); // ����� �հ����� ����Ͽ� ������ sum_temp �������迭 �����Ҵ缱��
		for(i = 0; i < row1; i++)  // ��ũ�⸸ŭ�� �ݺ���
		{
			sum_temp[i] = (int*) malloc(sizeof(int ) * col1); // ����ŭ ���� �޸� �Ҵ�
		}
		for(i=0; i<row1; i++) // �� ũ�⸸ŭ�� �ݺ���
		{
			for(j=0; j<col1; j++) // �� ũ�⸸ŭ�� �ݺ���
			{
				// ������ ù��° ��ķ� set_temp����� �ʱ�ȭ
				if( cal[0] == 'A' ){ 
					sum_temp[i][j] = tempA[i][j];}
				if( cal[0] == 'B' ){
					sum_temp[i][j] = tempB[i][j];}
				if( cal[0] == 'C' ){
					sum_temp[i][j] = tempC[i][j];}
				
				for( z=1; z<10; z++) // cal[] �迭�� �б� ���� �ݺ���
				{
					if( cal[z] == '+' ) // cal �迭�� +�� ���� ����
					{
						// z+1�� �����Ͽ� ���� ��İ� �����Ͽ� sum_temp�� ���� ������Ű�� ���ǹ�
						if( cal[z+1] == 'A' ){
							sum_temp[i][j] = sum_temp[i][j] + tempA[i][j];}
						else if( cal[z+1] == 'B' ){
							sum_temp[i][j] = sum_temp[i][j] + tempB[i][j];}
						else if( cal[z+1] == 'C' ){
							sum_temp[i][j] = sum_temp[i][j] + tempC[i][j];}
					}
					if( cal[z] == '-') // cal �迭�� -�� ���� ����
					{	
						// z+1�� �����Ͽ� ���� ��İ� �����Ͽ� sum_temp�� ���� ������Ű�� ���ǹ�
						if( cal[z+1] == 'A' ){
							sum_temp[i][j] = sum_temp[i][j] - tempA[i][j];}
						else if( cal[z+1] == 'B' ){
							sum_temp[i][j] = sum_temp[i][j] - tempB[i][j];}
						else if( cal[z+1] == 'C' ){
							sum_temp[i][j] = sum_temp[i][j] - tempC[i][j];}
					}			
				}	
			}
		}
		for (i=0; i< row1; i++) // ��ũ�⸸ŭ�� �ݺ���
		{
			for(j=0; j<col1; j++) // ��ũ�⸸ŭ�� �ݺ���
			{
				printf("%3d      ",sum_temp[i][j]); // sum_temp ����� ���
			}
			printf("\n");
		}
	}
	for(i = 0; i < row1; i++)  free(temp[i]); // tempA ������ �����޸��Ҵ��� �ݳ�
	free(tempA);
	for(i = 0; i < row2; i++)  free(temp[i]); // tempB ������ �����޸��Ҵ��� �ݳ�
	free(tempB);
	for(i = 0; i < row3; i++)  free(temp[i]); // tempC ������ �����޸��Ҵ��� �ݳ�
	free(tempC);
	for(i = 0; i < row1; i++)  free(temp[i]); // sum_temp ������ �����޸��Ҵ��� �ݳ�
	free(sum_temp);

	fclose(fp); // ���� �ݱ�
	return 0;
}