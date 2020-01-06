///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 16��
// ���α׷���   : ���� ���� ���α׷�
//   ��  ��     : data1.txt�� �л��� ������ �̸�, �й�, ����� ����Ǿ�
//                �ִ�. �̸� �о�� �й� ��, ��� ������ �����Ͽ� ���
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// ��������
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

// element����ü ����
typedef struct element{
	char name[20]; // �̸�
	int schoolnum; // �й�
	int num;       // ���
}element;

// �й�����
void schoolnum_sort(element *list,int n)
{
	int i,j,least; // i.j:�ݺ����� , least:�ּҰ� �ڸ� �ε���
	element temp;  // SWAP�� ���� element����
	for(i=0; i<n-1; i++) {
		least = i; 
		for(j=i+1; j<n; j++)
			if(list[j].schoolnum < list[least].schoolnum) least=j; // �й���� ��
		SWAP(list[i],list[least],temp); 
	}
}
// �������
void num_sort(element *list,int n)
{
	int i,j,least; // i.j:�ݺ����� , least:�ּҰ� �ڸ� �ε���
	element temp;  // SWAP�� ���� element����
	for(i=0; i<n-1; i++) {
		least = i;
		for(j=i+1; j<n; j++)
			if(list[j].num<list[least].num) least=j; // ������ ��
		SWAP(list[i],list[least],temp);
	}
}

int main()
{
	element *temp; // ����ü�迭 temp
	element e;     // ����ü e
	int count=0;   // ���� ����
	int i=0;       // �ݺ�����
	// ���� ����
	FILE *fp= fopen("data1.txt","r");
	if(fp == NULL){
		printf("���� ����\n");
		exit(1);
	}
	// ���� ������ ����üũ
	while(!feof(fp)){
		fscanf(fp,"%s %d %d",e.name,&e.schoolnum,&e.num);
		count++; // ���ϰ��� ī����
	}
	// ���� �Ҵ�
	temp = (element *)malloc(sizeof(element)*count);

	// ���������� ����
	rewind(fp);
	// temp[i]�� ���� �����Ͱ� ����
	for( i=0; i<count; i++)
	{
		fscanf(fp,"%s %d %d",temp[i].name,&temp[i].schoolnum,&temp[i].num);
	}
	
	// ������ ������
	printf("< ������ ������ >\n");
	printf(" ---------------------\n");
	printf("| �̸� |  �� ��  |���|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");


	// �й�����
	schoolnum_sort(temp,count);
	printf("< �й� ������ ������ >\n");
	printf(" ---------------------\n");
	printf("| �̸� |  �� ��  |���|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");

	// ��� ����
	num_sort(temp,count);
	printf("< ��� ������ ������ >\n");
	printf(" ---------------------\n");
	printf("| �̸� |  �� ��  |���|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");


	free(temp); // temp �����ݳ�
	fclose(fp); // fp ������ �ݽ��ϴ�.
	return 0;
}