///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 16��
// ���α׷���   : �� ���� ���α׷�
//   ��  ��     : data4.txt�� �л��� ������ �̸�, �й�, ��ȭ��ȣ�� ����
//                �Ǿ� �ִ�. �̸��о�� �й� ������ �������� �����Ͽ�
//                ����Ͻÿ�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// element ����ü ����
typedef struct element{
	char name[20]; // �̸�
	int schoolnum; // �й�
	char phone[20];// �ڵ��� ��ȣ
}element;

// �� ���� ���԰���
// *list : ����ü �迭
// first : �迭 ù �ε���
// last : �迭 �� �ε���
// gap : �� ���Ŀ��� �����ֱ����� �ε��������� ����
void inc_insertion_sort(element *list,int first,int last,int gap)
{
	int i,j;
	element	key; // �����͸� ��� ������ key����ü
	for(i=first+gap; i<=last; i=i+gap){
		key = list[i]; // �����͸� gap���̸�ŭ �̾� key�� ����
		for(j=i-gap; j>=first && key.schoolnum>list[j].schoolnum; j=j-gap)
			list[j+gap]=list[j]; // key���� �й��� �������� ����
		list[j+gap] = key; // ���� �� ����
	}
}
// �� ����
// *list : ����ü �迭
// n : ���� ������ ����
void shell_sort(element *list,int n)
{
	int i,gap;
	for(gap=n/2; gap>0; gap=gap/2) { 
		if( (gap%2) == 0 ) // ���� ¦�� �ϰ�� ����
			gap++;
		for(i=0; i<gap; i++) // ������ �ݺ�
			inc_insertion_sort(list,i,n-1,gap); // ���� ����
	}
}

int main(){
	element *temp; // ����ü�迭 temp
	element e;     // ����ü e
	int count=0;   // ���� ����
	int i=0;       // �ݺ� ����
	// ���� ����
	FILE *fp= fopen("data4.txt","r");
	if(fp == NULL){
		printf("���� ����\n");
		exit(1);
	}
	// ���� ������ ����üũ
	while(!feof(fp)){
		fscanf(fp,"%s %d %s",e.name,&e.schoolnum,e.phone);
		count++;
	}
	// ���� �Ҵ�
	temp = (element *)malloc(sizeof(element)*count);

	// ���������� ����
	rewind(fp);

	// ���� �� ���
	// temp[i]�� ���� �����Ͱ� ����
	printf("<���� ��>\n");
	for( i=0; i<count; i++)
	{
		fscanf(fp,"%s %d %s",temp[i].name,&temp[i].schoolnum,temp[i].phone);
		printf("%s %d %s\n",temp[i].name,temp[i].schoolnum,temp[i].phone);
	}

	// ���� �� ���
	// �� ���� ���
	printf("\n<���� ��>\n");
	shell_sort(temp,count);
	for( i=0; i<count; i++)
	{
		printf("%s %d %s\n",temp[i].name,temp[i].schoolnum,temp[i].phone);
	}

	free(temp); // temp �����ݳ�
	fclose(fp); // fp ������ �ݽ��ϴ�.
	return 0;
}