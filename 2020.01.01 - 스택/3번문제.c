///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 22��
// ���α׷���   : ���� 2
//   ��  ��     : Data.txt���� �����͸� ������ �̸�,��ȭ��ȣ, ������ ����
//                ����ü�� �����϶�. ���� �� ���� ���ÿ� ���� ���ڿ� ����
//                �� �ְ� �� ���ÿ��� �ϳ��� �̾� ¦�� ���� �Ʒ��� ����
//                ����϶�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ������
#define MAX_STACK_SIZE 100
// ����ü element ����
typedef struct element{
	char name[20];  // �̸�
	char phone[20]; // ����ȣ
	char sex[20];   // ����
}element;
// ���� ����
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

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
	if( is_full(s)  ) { // ��ȭ�� ���
		fprintf(stderr,"���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// ���� �Լ�
element pop(StackType *s)
{
	if( is_empty(s) ) { // ������ ���
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else return s->stack[s->top--]; // top--����
}

int main()
{
	StackType man,girl; // ���� man,girl ����
	element A,man_str,girl_str; // ����ü ����
	int i=1; // <%dȣ> ǥ������
	int count_man=0,count_girl=0; // ��,�� ���ϵ����� ����

	// data3.txt ������ �б��������� ����
	FILE *fp = fopen("data3.txt","r");
	if(fp==NULL){ // ���� ������
		printf("���� ����\n");
		return 1;
	}

	// Ǫ��
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s", A.name , A.phone , A.sex );
		if ( strcmp( A.sex , "��") == 0 ){ // ������ ���
			push(&man,A); // man�� Ǫ��
			printf("<Push> ���� - %s\n", A.name );
			count_man++;  // manī���� 
		}
		else if ( strcmp( A.sex , "��" ) == 0 ){ // ������ ���
			push(&girl,A); // girl�� Ǫ��
			printf("<Push> ���� - %s\n", A.name );
			count_girl++;  // girlī����
		}
	}
	printf("\n");

	// ��
	while(1)
	{
		man_str = pop(&man);   // man_str����ü�� pop(&man)�� ����
		girl_str = pop(&girl); // girl_str����ü�� pop(&girl)�� ����

		if( count_man != 0 && count_girl != 0 ) // ��,�� ������ ���� �� �� 0�� �ƴҰ��
		{
			printf("<%dȣ> ",i);
			printf(" %s(%s) -", man_str.name , man_str.phone );
			printf(" %s(%s)\n", girl_str.name , girl_str.phone );
		}
		else if ( count_girl == 0 && count_man>0 ) // ���̻� ���� ������ ���� ���� ���
		{
			printf("%s���� ¦�� �����ϴ�...\n",man_str.name); // ���� �����̸� ���
			break;
		}
		else if ( count_man == 0 && count_girl>0 ) // ���̻� ���� ������ ���� ���� ���
		{
			printf("%s���� ¦�� �����ϴ�...\n",girl_str.name); // ���� �����̸� ���
			break;
		}
		else if ( count_man <= 0 && count_girl <= 0 ) // �� ������ ���� ���� ���
			break;
		count_man--;  // count_man����
		count_girl--; // count_girl����
		i++;          // i����
	}

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}