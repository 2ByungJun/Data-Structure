///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 15��
// ���α׷���   : ���� 1
//   ��  ��     : ���ÿ� 1~20 ������ ���ڸ� �������� �����ϰ� �� ���� ��
//                �徿 �̾� ���ڰ����� 5ȸ �����Ͽ� ���и� ����Ͻÿ�.
//                (�� �徿 ���� ���ڰ� ���� ����� �¸��Ѵ�.)
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 100 // ���� ������ 100 
typedef int element; // �ڷ��� element ����
typedef struct { // ��������
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
// ���� �Լ�
void push(StackType *s,element item)
{
	if( is_full(s)  ) { // ���� �� ���� �� �������
		fprintf(stderr,"���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item; // ������ top�κк��� ������ ����( top�� ���Ե� ���� �ȴ� )
}
// ���� �Լ�
element pop(StackType *s)
{
	if( is_empty(s) ) { // ������ ������� �� �������
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top]; // top�κ��� ����
}

int main()
{
	StackType temp;  // ����Ÿ�� temp����
	int i=0,j=0,a=0; // ������ ��Ʈ�� ����
	int num[20];     // �����Լ��� ������ �迭
	int win=0 , lose=0;  // ��,�� Ƚ��
	int copy1=0,copy2=0; // ��,�� �񱳺���

	init(&temp); // temp �ʱ�ȭ

	// �ߺ��ȵǴ� �����Լ�
	srand((unsigned)time(NULL)); // �� �ð��� NULL�� �ʱ�ȭ
	while(i<20)
	{
		num[i]=rand()%20+1; // num���� 1~20������ ������ ����
		while(1) // ���ѷ���
		{
			for(j=0; j<i; j++) // num[i] ������� ��
			{
				while(num[i]==num[j])  // ���� ��� �ٸ� ���� ����
					num[i]=rand()%20+1;
			}
			for(j=0; j<i; j++) // num[i] ������� ��
			{
				if( num[i] != num[j]) // �ٸ� �� a���� ����
					a++;
			}
			if( a==(i)) // a�� i�� ���� ��� �� ������̸� break;
				break;

			a=0; // a�� 0���� �ʱ�ȭ
		}
		i++; // i�� ����
	}
	
	// temp.stack�� Ǫ��
	for(i=0;i<20;i++){
		push(&temp,num[i]);
	}

	// ��� ���
	j=0; // 0���� �ʱ�ȭ
	for(i=0; i<5; i++)   // 5�� ����
	{
		printf("< %dȸ�� >\n",i+1); // ȸ�� ���
		printf("A : %d - ", temp.stack[j] ); // A�� ���
		copy1 = temp.stack[j]; // ���� copy1�� ����
		j++; 
		printf("B : %d\n", temp.stack[j] ); // B�� ���
		copy2 = temp.stack[j]; // ���� copy2�� ����
		j++;
		// �� �� ���ϱ�
		if( copy1 > copy2 )
			win++; 
		else
			lose++;
	}
	// �� �� ���
	printf("\n< �� �� >\n");
	printf("A - �� : %d     �� : %d\n",win,lose); 
	printf("B - �� : %d     �� : %d\n",5-win,5-lose); 

	return 0;
}