///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 19��
// ���α׷���   : �迭�� ������ ���Ḯ��Ʈ 4
//   ��  ��     : ����� ���� data.txt���Ͽ� �й�,����,����,���� ������
//                �ԷµǾ� �ִ�. �� ������ �̿��Ͽ� ����ü ���� ����ü
//                �迭�� �ʱ�ȭ �ϰ� �̸� �̿��Ͽ� ������� ������
//                Sorting�Ͽ� �Ʒ��� ���� ����ϴ� ���α׷��� �ۼ��Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // �迭�� �ִ� ũ��

typedef struct {  // student ����ü
	int number;   // �й�
	int korean;   // ����
	int english;  // ����
	int math;     // ����
}student;

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE];
	int length; // ���� �迭�� ����� �ڷ���� ����
}ArrayListType;

// ����Ʈ �ʱ�ȭ
void init(ArrayListType *L)
{
	L->length = 0;
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
void display(ArrayListType *L,int count)
{
	int i,j=0,z=0;     // �ݺ��� ������
	int sum[20];       // ���� �迭
	double average[20];// ��� �迭
	int tmp;           // �������� ���Ժ���
	int index_num;     // After Sorting!! sum��ġ ��Ʈ�� ����
	int x;             // After Sorting!! ��� ��Ʈ�� ����

	// ������ ��� �迭 ���ϱ�
	for( i=0; i<count; i++)
	{
		sum[i] = L->list[1+j]+ L->list[2+j] + L->list[3+j]; // ������ ���ϴ� ����
		average[i] = (double)sum[i]/3;                      // ����� ���ϴ� ����
		j+=4; // j�� +4������
	}

	// Before Sorintg!!
	printf("Before Sorting!!\n");
	printf("�й�           ����    ����    ����     ����     ���\n");
	// �ʱ�ȭ�� ������
	j=0;
	// ��¹�
	for( i=0; i<=L->length; i++){ // ����Ʈ ũ�⸸ŭ �ݺ� 
		if( i != 0 && i%4 == 0 )  // i���� 0�� �ƴϸ� i�� 4����ϰ��
		{
			printf("%d \t%.2lf \t",sum[j] , average[j]); // ������ ��� ���
			j++;
			printf("\n");
		}
		if( L->length != i )        // ����Ʈ�� ũ�Ⱑ i���� �ٸ����
		printf("%d \t",L->list[i]); // ����Ʈ ���
	}
	printf("\n\n\n");

	// sum , average �������� - ū���� ���� ����ϱ� ����
	for( i=0; i<count; i++)
	{ 
		for(j=0; j<count-1; j++)
		{
			if(sum[j]<sum[j+1])    // sum���� ���� �װ� ���Ͽ� ���� ���� �� Ŭ ���
			{
				tmp = sum[j];      // ���� sum���� tmp�� ����
				sum[j] = sum[j+1]; // ���� sum���� ���� ���� ����
				sum[j+1] = tmp;    // ���� �׿� ���� sum���� ����
			}
			if(average[j]<average[j+1])    // average���� ���� �װ� ���Ͽ� ���� ���� �� Ŭ ���
			{
				tmp = average[j];          // ���� average���� tmp�� ����
				average[j] = average[j+1]; // ���� average���� ���� ���� ����
				average[j+1] = tmp;        // ���� �׿� ���� average���� ����
			}
		}
	}

	// After Sorting!!
	printf("After Sorting!!\n");
	printf("�й�           ����    ����    ����     ����     ���\n");
	// �ʱ�ȭ�� ������
	index_num=0;
	j=0;
	x=0;
	// ��¹�
	for( i=0; i<=L->length; i++)
	{
		if( i != 0 && i%4 == 0 )  // i���� 0�� �ƴϸ� i���� 4����ϰ��
		{
			printf("%d \t%.2lf \t",sum[j] , average[j]); 
			j++;
			x--; // ������ ����� ��µɶ����� ����� �ȵǰ� �ϴ� ��Ʈ�� ���� ����
			printf("\n");
		}
		for ( z=0; z<L->length; z+=4) // ����Ʈ ũ�⸸ŭ�� �ݺ����̸� �������� z�� +4�� �����Ѵ�
		{
			 // ������ ���Ͽ� �ش���ġ�� ����Ʈ���� ���
			if(  sum[index_num] ==  L->list[z+1]+ L->list[z+2]+L->list[z+3] && x == 0 )
			{
				printf("%d \t%d \t%d \t%d \t",L->list[z],L->list[z+1],L->list[z+2],L->list[z+3]);
				index_num++;
				x++; // ������ ����� ��µɶ����� ����� �ȵǰ� �ϴ� ��Ʈ�� ���� ����
				break;
			}
		}
	}
}

int main()
{
	ArrayListType *plist; // �����Ҵ� ���� ���� ����ü �迭 ����
	student *list;        // ����ü�� �ʱ�ȭ�� �迭 ����
	int count=0;          // ���� ���� ī����
	int F_line;           // ī������ ���� ������ �о��� ����
	int i=0,j=0;          // �ݺ������� ����
	
	FILE *fp = fopen("data4.txt","r");  // data4.txt������ �б��������� ����
	if( fp == NULL)                     // ���Ͽ����� ��¹���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 0;
	}

	while(!feof(fp))  // ����ī������ ���� ������ ������ �о��� �ݺ���
	{
		F_line = fgetc(fp); // ���� ������ �о��ش�
		if(F_line == '\n')  // �ٹٲ޽� ī����
			count++; // �����Ͱ� ī���� ������
	}
	count++; // ������ ������ �о�������� ����

	list = (student *)malloc(sizeof(student)*count); // count��ŭ�� list�����Ҵ�
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count); // count��ŭ�� plist�����Ҵ�
	init(plist); // plist ����Ʈ �ʱ�ȭ

	rewind(fp);
	while(!feof(fp))   // ���������Ͱ� ������ �����Ҷ����� �ݺ��ϴ� �ݺ���
	{ 
		// ����ü �迭�� �������� ���ϵ����Ͱ� ����
		fscanf(fp,"%d %d %d %d", &list[i].number,  &list[i].korean, &list[i].english,&list[i].math);
		add( plist , j , list[i].number );  // list -> plist�� �й�����
		j++;
		add( plist , j , list[i].korean );  // list -> plist�� ������������
		j++;
		add( plist , j , list[i].english ); // list -> plist�� ������������
		j++;
		add( plist , j , list[i].math );    // list -> plist�� ������������
		j++;
		i++; // i���� ����
	}

	display(plist,count); // plist ���

	fclose(fp);  // ������ �ݾ��ش�
	free(plist); // plist�� �����Ҵ��� �ݳ����ش�.
	free(list);  // list�� �����Ҵ��� �ݳ����ش�.

	return 0;
}