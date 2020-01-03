///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 18��
// ���α׷���   : �迭�� ������ ���Ḯ��Ʈ 1
//   ��  ��     : ����ڰ� �Է��� ���ڸ�ŭ ���� ���ڵ��� �����Ͽ� �迭��
//                ������ ���Ḯ��Ʈ�� �߰��ϰ� �ִ밪�� �ּҰ��� �Ʒ�
//                ����� ���� ��� �Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>  // malloc,srand,rand�� ���� ���� ���̺귯�� �Լ�
#include <time.h>    // time�� �������� ���̺귯�� �Լ�

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

// ����Ʈ ���
void display(ArrayListType *L)
{
	int cmp[MAX_LIST_SIZE]={0};
	int i,j;
	int count=0;
	int max=0;
	int min=999;

	// �ִ밪 �ּҰ� �ش� �� ã�� �ݺ���
    for(i=0; i<(L->length); i++)
	{
		if ( max < L->list[i] )
			max = L->list[i];    // �ִ밪 ����
		else if ( min > L->list[i] )
			min = L->list[i];    // �ּҰ� ����
	}

	// �ִ밪 �ּҰ� ��ġ�� cmp[]�� ����
	for(i=0; i<(L->length); i++)
	{
		if ( max == L->list[i] )
			cmp[i] = 1; // �ִ밪�� ��� 1 ����
		else if ( min == L->list[i] )
			cmp[i] = 2; // �ּҰ��� ��� 2 ����
	}
	printf("�ִ�:%d �ּ�:%d\n",max,min);

	// �ִ� �ּҰ� 
	for( i = 0; i < L->length; i+=15)        // i+=15�� �־� 15�� �ڸ����� ū �ݺ�Ʋ�� �����Ѵ�.             
   {
	    for(j = 0; j < 15; j++)      // z���� �̿��� 1�� �ڸ����� �ݺ��Ͽ� ����ϴ� �ݺ���
		{
			if( i + j >= L->length)  // C[�����Ͱ�]�� �����Ⱚ�� ������ �ʰ� ���ִ� ���ǹ�
				break;               // '���Ž�'���� �ڿ� ������ �������ּҰ��� ���´�.

			printf("%d  \t", L->list[i+j]);  // C[0]~C[i]���� ��½����ش�.
		}
		printf("\n");

		for(j = 0; j < 15; j++)       // �ִ밪 �ּҰ� ��ġ Ž�� �ݺ���
		{
			if(cmp[i+j] == 1) {         // �ִ밪 ��ġ�� 1�� �����Ͽ��� cmp[j] 1�ϰ�� �� ��ġ�� "�ִ밪"�� ������ش�.
				printf("Max   ");
			}
			if(cmp[i+j] == 2)  {        // �ּҰ� ��ġ�� 2�� �����Ͽ��� cmp[j] 2�ϰ�� �� ��ġ�� "�ּҰ�"�� ������ش�.
				printf("Min   ");
			}
			if(cmp[i+j] == 0)  {        // �ִ밪�� �ּҰ� �ƴ� ���� ������ ������ִ� ���ǽ�
				printf("\t");
			};
		}
		printf("\n");		
   }
}

int main()
{
	ArrayListType *plist;  // plist �����迭 ����
	int n; // ���� ������ ���� ����
	int i; // �ݺ��� ������ ����

	// ������ ���� �Է�
	printf("������ ���� ���� ������ �Է��ϼ��� : ");
	scanf("%d",&n);
	printf("[ �迭�� ������ ���Ḯ��Ʈ�� �߰��� ������ ]");
	
	// plist�� ���� ����ü �Ҵ�
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*n);
	init(plist); // ����Ʈ �ʱ�ȭ

	srand(time(NULL)); // �ð��� �ʱ�ȭ ���� ������ ������ �����ϰ� ���
	for(i=0; i<n; i++) // �����Լ� ���
	{
		add(plist,i,rand()%1000); // plist�� �������� ����
	}

	printf("\n");
	display(plist); // plist ���
	free(plist);    // plist ���� �޸� �ݳ�
}

