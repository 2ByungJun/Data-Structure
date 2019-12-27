///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 18��
// ���α׷���   : �迭�� ������ ���Ḯ��Ʈ 3
//   ��  ��     : �л� �� �й�,����,����,������ ������ data.txt ���Ͽ�
//                ����Ǿ� �ִ�. �� ������ �����͸� �о� �鿩 ��������
//                ���� ����ü �迭�� �����ϰ�, �л��� �й� �Ǵ� �̸���
//                �Է� �޾� �� �л��� ���� �� ����, ���, ����� ����϶�
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // �迭�� �ִ� ũ��

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE]; // �迭�� ����
	int length; // ���� �迭�� ����� �ڷ���� ����
}ArrayListType;
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// ����Ʈ �ʱ�ȭ
void init(ArrayListType *L)
{
	L->length = 0;
}
// ����Ʈ�� ��� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_empty(ArrayListType *L)
{
	return L->length == 0;
}
// ����Ʈ�� ���� �� ������ 1�� ��ȯ
// �׷��� ������ 0�� ��ȯ
int is_full(ArrayListType *L)
{
	return L->length == MAX_LIST_SIZE;
}
// ����Ʈ ���
void display(ArrayListType *L)
{
	int i;
	for( i=0; i<L->length; i++){
		printf("%d ",L->list[i]);
		if ( i != L->length-1)
		printf("-> ");
	}
	printf("\n");
}
// position : �����ϰ��� �ϴ� ��ġ
// item : �����ϰ��� �ϴ� �ڷ�
void add(ArrayListType *L , int position,element item)
{
	if( !is_full(L) && (position >= 0) && (position <= L->length) ) 
	{
			int i;
			for( i=(L->length-1); i>=position; i--) 
				L->list[i+1] = L->list[i];
			L->list[position] = item;
			L->length++;
	}
}
// position : �����ϰ��� �ϴ� ��ġ
// ��ȯ �� : �����Ǵ� �ڷ�
element delete(ArrayListType *L, int position )
{
	int i;
	element item;

	if(  position < 0 || position >= L->length)
		error("��ġ ����");
	for(i=position; i<(L->length-1); i++)
	item = L->list[i] = L->list[i+1];
	L->length--;
	return item;
}

int main()
{
	ArrayListType *plist; // plist ����ü �迭 ����
	int count=0;          // ���� ������ ������ ���� ����
	int num;              // count�� ���ϱ� ���� ������ �о��� ����
	int i;                // �ݺ� ������ ����
	int delete1=1;        // Ȧ�� ��ġ�� ��Ÿ�� ����
	FILE *fp = fopen("data3.txt","r"); // data3.txt�� �б���·� ����
	if( fp == NULL)                    // ���Ͽ����� �������� ���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 0;
	}
	
	while(!feof(fp)) // count���� ���ϱ� ���� ������ �о��ִ� �ݺ���
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	// count���� ũ�⸸ŭ plist�迭 �����Ҵ�
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count);
	init(plist); // plist �迭 �ʱ�ȭ

	rewind(fp); // ���� ��������ġ �ʱ�ȭ
	for(i=0; i<count; i++) // countũ���� �ݺ���
	{
		fscanf(fp,"%d",&num);  // ���� �����Ͱ��� num���� ����
		add(plist , i , num ); // num���� plist����Ʈ�� i��ġ�� ����
	}

	display(plist); // plist ����Ʈ�� ���
	
	for ( i=0; i<count-1; i++) // count-1 ũ�⸸ŭ �ݺ�
	{
		if( i%2 == 1 ){        // i���� Ȧ���� ���
		delete( plist, delete1); // plist����Ʈ�� delete1��° ������ ����
		delete1++; // delete1���� ����
		}
	}
	display(plist); // plist���

	fclose(fp);  // ������ �ݾ��ش�
	free(plist); // plist����Ʈ ���� �޸� �ݳ�
}