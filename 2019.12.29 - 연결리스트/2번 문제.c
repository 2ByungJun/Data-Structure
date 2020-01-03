///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 18��
// ���α׷���   : �迭�� ������ ���Ḯ��Ʈ 2
//   ��  ��     : �迭�� ������ ���Ḯ��Ʈ ������ ����ڰ� �Է���
//                ���ڰ� �� ��°�� �ִ��� �˻��ϴ� �Լ��� �����ϰ� ���
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> // malloc�� ����ϱ� ���� ���̺귯�� �Լ�

#define MAX_LIST_SIZE 10000 // �迭�� �ִ� ũ��

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE]; // �迭�� ����
	int length; // ���� �迭�� ����� �ڷ���� ����
}ArrayListType;

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

// ���ڰ� �� ��°�� �ִ��� �˻��ϴ� �Լ�
int find( ArrayListType *L, int count )
{
	int i=0, j;  // �ݺ� ������ ����
	int zero=0;  // ����Ʈ�� ���� ��츦 ���� ī���� ����
	int value;   // �Է¹��� ���� �����ϴ� ����

	while ( 1 )  // ���ѷ��� �ݺ���
	{
		if ( i == 0 ) // i == 0 �ϰ�� ���� �Է¹޴� ����
		{
			printf("���� �Է��ϼ���<0:����> : ");
			scanf("%d",&value);
			if ( value == 0 )
				return 0;
		}
		// ���� ������ ���
		if ( value == L->list[i] ){
			printf("%d��(��) ����Ʈ ", value );
			for( j = 0; j< count; j++ )     // ���� ��ġ�� �˷��� �ݺ���
			{
				if ( value == L->list[j] )  // ���� list�� ���� ������ ���
					printf("%d ",j+1);      // ��ġ�� ���
			}
			printf("��°�� �ֽ��ϴ�.\n\n");
			i = 0;    // ��õ��� ���� i�� 0���� �ʱ�ȭ
			continue; // ��ݺ�
		}
		else if ( value != L->list[i] ) // ����Ʈ�� Ž���ϸ鼭 ���� ��� zero�� ī����
			zero++;

		// ���� ����Ʈ�� ���� ���
		if( zero == count )  // zero�� count�� ���� ���� Ž���� ������ ��ģ �� ���� ���� ����̴�
		{
			printf("%d��(��) ����Ʈ�� �����ϴ�.\n\n",value);
			i = 0;    // ��õ��� ���� i�� 0���� �ʱ�ȭ
			zero = 0; // ��õ��� ���� zero�� 0���� �ʱ�ȭ
			continue; // ��ݺ�
		}
		i++;
	}
}

int main()
{
	ArrayListType *plist; // ����ü �����Ҵ���� �迭
	int count=0;          // ���� ������ ����
	int num;              // count�� ���� ������ �о��� ����
	int i;                // �ݺ� ������ ����
	FILE *fp = fopen("data2.txt","r"); // data2.txt������ �б� �������� ����
	if( fp == NULL)                    // ������ ������ �ʾ��� ��� �������� ���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 0;
	}
	
	while(!feof(fp)) // count���� ��� ���� ������ ������ �д� �ݺ���
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	// count ũ�⸸ŭ plist ����ü�迭�� �����޸� �Ҵ�
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count);
	init(plist); // plist ����Ʈ �ʱ�ȭ

	rewind(fp);
	for(i=0; i<count; i++)  // count ũ�⸸ŭ �ݺ���
	{
		fscanf(fp,"%d",&num);  // ���Ͽ��� �����͸� num���� �Է¹޴´�
		add(plist , i , num ); // num���� plist����Ʈ�� ���������� ����
	}
	fclose(fp); // ������ �ݾ��ش�
	display(plist); // plist ����Ʈ ���

	find(plist,count); // find�Լ��� plist�� ���ڰ� ���°�ִ��� �˻����ش�

	free(plist); // plist����Ʈ �����޸� �ݳ�
	return 0;
}