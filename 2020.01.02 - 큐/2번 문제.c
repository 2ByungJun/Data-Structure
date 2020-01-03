///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 31��
// ���α׷���   : ���� push pop ������� ���α׷�
//   ��  ��     : ���Ḯ��Ʈ�� �̿��� ���� ���α׷��� �̿��Ͽ� data.txt
//                ���Ͽ� ����� �����͸� �Է� �޾� 2���� ���ÿ� �����
//                �� ������ �Ʒ��� ���ǿ� �°� ���α׷��� �Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// int������ element ����
typedef int element; 
// ���� ���Ḯ��Ʈ ����ü
typedef struct StackNode{ 
	element item;
	struct StackNode *link;
}StackNode;
// ���� ��� top
typedef struct{
	StackNode *top;
} LinkedStackType;
// ���� ������ ����ī���� ����
static int stack1_count=0,stack2_count=0;
// ���� �ʱ�ȭ 
void init(LinkedStackType *s)		
{
	s->top = NULL;
}
// ������ ���������
int is_empty(LinkedStackType *s)	
{
	return (s->top == NULL);
}
// Push�Լ�
// *s : ���Ḯ��Ʈ ����
// item : ������ ��
void push(LinkedStackType *s,element item)	
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp ==NULL)
	{
		fprintf(stderr,"�޸� �Ҵ翡��\n");
		return;
	}
	else
	{
		temp->item =item;
		temp->link = s->top;
		s->top = temp;
	}
}
// Pop�Լ�
// s : ���Ḯ��Ʈ ����
element pop(LinkedStackType *s)				
{
	if(is_empty(s))
	{
		fprintf(stderr,"������ �������\n");
		return;
	}
	else
	{
		StackNode *temp=s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
// Peek�Լ�
// s : ���Ḯ��Ʈ ����
element peek(LinkedStackType *s)			
{
	if(is_empty(s))
	{
		fprintf(stderr,"������ �������\n");
		exit(1);
	}
	else
	{
		return s->top->item;
	}
}
// ���� ��� �Լ�
// head1 : ����1
// head2 : ����2
// count1 : ����1�� ������ ��
// count2 : ����2�� ������ ��
void display(LinkedStackType *head1,LinkedStackType *head2,int stack1_count, int stack2_count)
{
	int i=0;
	StackNode *temp1 = head1->top;
	StackNode *temp2 =	head2->top;

	// ����1�� ������ ������ ���������
	if(stack1_count > stack2_count)				
	{
		for(i=0; i<stack1_count-stack2_count; i++)
		{
			printf("�� <%2d>��  ��     ��  \n",temp1->item);
			temp1=temp1->link; // ����1�� ��������
		}
	}
	// ����2�� ������ ������ ���������
	if(stack1_count < stack2_count)				
	{
		for(i=0; i<stack2_count-stack1_count; i++)
		{
			printf("��     ��  �� <%2d>��  \n",temp2->item);
			temp2=temp2->link; // ����2�� ��������
		}
	}
	// ������ �κ� ���
	while ( temp1 != NULL && temp2 !=NULL)
	{
		printf("�� <%2d>��  ",temp1->item); printf("�� <%2d>��\n",temp2->item);
		temp1=temp1->link; // ����1�� ��������
		temp2=temp2->link; // ����2�� ��������
	}
	printf("��������������  ��������������\n");
}


void main()
{
	LinkedStackType s1,s2;		// ���� ����
	char stack_pp[10]={0};      // ����push,pop �Ǻ�
	int stack_number=0,data=0;  // ���ù�ȣ,�����Ͱ�
	int i=0;                    // ����Step

	// data2.txt������ �б��������� ����
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL) // ���� ����
	{
		fprintf(stderr,"���� ����\n");
		exit(1);
	}
	// ���� �ʱ�ȭ
	init(&s1);						
	init(&s2);						
	// ���� �����Ͱ� ������ �����Ҷ����� �ݺ�
	while(!feof(fp))
	{
		fscanf(fp,"%s",&stack_pp); // stack_pp�� push,pop�� �о�´�.

		// push�� ���
		if(strcmp(stack_pp,"push") == 0)
		{
			fscanf(fp,"%d %d",&stack_number,&data);
			// 1������ ���
			if(stack_number == 1)
			{
				push(&s1,data); // data�� ����1�� Ǫ��
				printf("---Step %d : ���� 1 %d �Է�---\n",i+1,data);

				stack1_count++; // ����1�� ī��Ʈ+1
				display(&s1,&s2,stack1_count,stack2_count);
				printf("\n");	
			}
			// 2������ ���
			else if(stack_number==2)
			{
				push(&s2,data); // data�� ����2�� Ǫ��
				printf("---Step %d : ���� 2 %d �Է�---\n",i+1,data);

				stack2_count++; // ����2�� ī��Ʈ+1
				display(&s1,&s2,stack1_count,stack2_count);
				printf("\n");				
			}
		}
		// pop�� ���
		else if(strcmp(stack_pp,"pop") == 0)
		{
			fscanf(fp,"%d",&stack_number);
			// 1������ ���
			if(stack_number==1)
			{
				printf("---Step %d : ���� 1 %d ����---\n",i+1,peek(&s1));
				pop(&s1); // ����1 pop

				stack1_count--; // ����1�� ī��Ʈ-1
				display(&s1,&s2,stack1_count,stack2_count);			
				printf("\n");	
			}
			// 2������ ���
			else if(stack_number==2)
			{
				printf("---Step %d : ���� 2 %d ����---\n",i+1,peek(&s2));
				pop(&s2); // ����2 pop

				stack2_count--; // ����2�� ī��Ʈ-1
				display(&s1,&s2,stack1_count,stack2_count);		
				printf("\n");	
			}	
		}
		i++;
	}
	
	fclose(fp); // ������ �ݾ��ش�
	return;
}