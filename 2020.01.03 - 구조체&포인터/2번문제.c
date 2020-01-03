///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 9�� 5��
// ���α׷���   : ���Ͽ��� �ڷ� �о���� 2
//   ��  ��     : data.txt�� �л�,�̸�,����/����/���� ������ ����Ǿ��ְ�,
//                ���ǿ� �´� ���α׷��� �ۼ��϶�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// student ����ü ����
typedef struct {
	int studentNumber; // �й�
	char name[10];     // �̸�
	int math;          // ����
	int eng;           // ����
	int kor;           // ����
}student;

typedef struct ListNode {
	student data;
	struct ListNode *link;
} ListNode;

// �������
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}

// ����
// phead: ����Ʈ�� ��� ����Ʈ�� ������
// p : ������
// new_node : ���Ե� ���
void insert_node(ListNode **phead,ListNode *p,ListNode *new_node)
{
	if( *phead == NULL ){ // ���� ����Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL ){ // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else { // p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}

// ��� ��������
ListNode *create_node(student data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// ��������
void sort(ListNode *head)
{
	ListNode *p = NULL; // p����Ʈ�� ���� �� NULL�� �ʱ�ȭ
	ListNode *q = NULL; // q����Ʈ�� ���� �� NULL�� �ʱ�ȭ
	student tmp;
	double average_p; // ��հ�p
	double average_q; // ��հ�q

	for(p=head; p!=NULL; p=p->link) // p�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
	{
		average_p = (p->data.eng + p->data.kor + p->data.math)/3; // p��հ�
		for(q=head; q!=NULL; q=q->link) // q�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
		{
			average_q = (q->data.eng + q->data.kor + q->data.math)/3; // q��հ�
			if( average_p > average_q )       // p�� ��� ���� q�� ��� �� ���� ���� ���
			{
				tmp = p->data;     // tmp�� �̿��Ͽ� p->data(����ü��)�� q->data������ ��ȯ�����ش�.
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
	for( ; p!=NULL; p=p->link)
	{
		head->data = p->data;
		head = head->link;
	}
}

// ���
void display(ListNode *head)
{
	ListNode *p=head; // p�� head����� �ʱ�ȭ
	int i;            // �ݺ�����
	int sum=0;        // ����
	double average=0; // ���

	printf("|========================================================|\n");
	printf("|  ��  ��  |  �� �� | ���� | ���� | ���� | �� �� | �� �� |\n");
	printf("|========================================================|\n");

	for (p = head; p !=NULL; p=p->link) // p�� head�� �ʱ�ȭ�ϸ� NULL���� �ݺ�
	{
		sum = p->data.eng + p->data.kor + p->data.math; // �������
		average = (double)sum/3; // ��հ��
		// �й�,�̸�,����,����,���� ���
		printf("| %d | %s | %3d  | %3d  | %3d  |", p->data.studentNumber, p->data.name ,p->data.math , p->data.eng ,p->data.kor );
		for( i=0; i<1; i++) // ����,��� ���
			printf(" %4d  | %3.2lf |\n", sum ,average );
	}
	printf("|========================================================|\n");
}

int main()
{
	ListNode *plist=NULL;   // �����Ҵ� ���� ���� ����ü �迭 ����
	student tmp;

	FILE *fp = fopen("data2.txt","r");  // data4.txt������ �б��������� ����
	if( fp == NULL)                     // ���Ͽ����� ��¹���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 1;
	}

	while(!feof(fp))  // ����ī������ ���� ������ ������ �о��� �ݺ���
	{
		// �й�,�̸�,����,����,���� ������ tmp����ü�� ����
		fscanf(fp,"%d %s %d %d %d", &tmp.studentNumber, &tmp.name ,&tmp.math, &tmp.eng, &tmp.kor); 
	    insert_node(&plist,NULL,create_node(tmp,NULL)); // tmp����ü �������� �� ����Ʈ ����
	}

	sort(plist);    // ���������� ����
	display(plist); // ����Ʈ ���

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}