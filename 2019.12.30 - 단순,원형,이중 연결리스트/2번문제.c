///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 2��
// ���α׷���   : ���Ḯ��Ʈ 2
//   ��  ��     : ������ ����� ������ ����ڿ��� �Է� �޾� 1~100������
//                ������ �����ͷ� ���� ��带 �����Ѵ�.
//                ������ ��带 ���� ��ũ�� ����Ʈ�� �����ϰ� �� ����Ʈ��
//                �����Ͽ� ����Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> // ����� �����Ҵ�
#include <time.h>   // srand�� rand�� ���

#define SWAP(a,b) { element t; t=a; a=b; b=t; } // ���������� ���� SWAP�Լ� ( �ڸ��� �ٲ��ش� )

typedef int element;       // element�� int �ڷ������� ����
typedef struct ListNode {  // ListNode����ü ����
	element data;          // int�� data
	struct ListNode *link; // ListNode link ������
}ListNode;

// ���� ���
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// phead: ����Ʈ�� ��� ����Ʈ�� ������
// p : ������
// new_node : ���Ե� ���
void insert_node(ListNode **phead,ListNode *p, ListNode *new_node)
{
	if( *phead == NULL ){  // ���� ����Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL ) { // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {  // p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}
// ����Ʈ �����Ҵ�
ListNode *create(element data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// ����Ʈ ���
void display(ListNode *head)
{
	ListNode *p=head;

	while( p != NULL) {
		printf("< %d >",p->data); // ������Ŀ� �°� printf�� �ۼ�
		p = p->link;
	}
	printf("\n");
}
// ����Ʈ ��������
void line(ListNode *head)
{
	ListNode *p = NULL; // p����Ʈ�� ���� �� NULL�� �ʱ�ȭ
	ListNode *q = NULL; // q����Ʈ�� ���� �� NULL�� �ʱ�ȭ

	for(p=head; p!=NULL; p=p->link) // p�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
	{

		for(q=head; q!=NULL; q=q->link) // q�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
		{
			if(p->data < q->data)       // p�� data���� q�� data�� ���� ���� ���
			{
				SWAP( p->data , q->data ) // p�����Ͱ��� q�����Ͱ��� �ٲ��ش�.
			}
		}
	}
}

int main()
{
	ListNode *temp=NULL; // ����Ʈ temp���� �� NULL�� �ʱ�ȭ
	int num;             // ����� ������ �Է¹��� ����
	int i;               // �ݺ��� ������ ����

	printf("������ ����� ������ �Է��ϼ��� : ");
	scanf("%d",&num);
	printf("\n");

	srand(time(NULL));    // time�� NULL�� �ξ� �Ź� �ٸ� ������ ���
	for( i=0; i<num; i++) // ����� ������ŭ �ݺ���
	insert_node(&temp,NULL,create(rand()%100,NULL)); // 1���� 100������ ������ temp ����Ʈ�� ����
	printf("< ������ ����Ʈ >\n");
	display(temp); // temp����Ʈ ���
	printf("\n");

	printf("< ���ĵ� ����Ʈ >\n");
	line(temp);    // ��������
	display(temp); // temp����Ʈ ���
	return 0;
}