#include <stdio.h>
#include <stdlib.h>

#define SWAP(a,b) { element t; t=a; a=b; b=t; } // ���������� ���� SWAP�Լ� ( �ڸ��� �ٲ��ش� )

typedef struct {
	int studentNumber;
	int kor;
	int eng;
	int math;
} element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

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
// ����
ListNode *reverse(ListNode *head)
{
	ListNode *p,*q, *r;
	p = head;
	q = NULL;
	while ( p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

// ��������
void sort(ListNode *head)
{
	ListNode *p = NULL; // p����Ʈ�� ���� �� NULL�� �ʱ�ȭ
	ListNode *q = NULL; // q����Ʈ�� ���� �� NULL�� �ʱ�ȭ
	element tmp;
	int sum_p;
	int sum_q;

	for(p=head; p!=NULL; p=p->link) // p�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
	{
		sum_p = p->data.eng + p->data.kor + p->data.math;
		for(q=head; q!=NULL; q=q->link) // q�� head�� �ʱ�ȭ �� ��� ������ �ݺ�
		{
			sum_q = q->data.eng + q->data.kor + q->data.math;
			if( sum_p > sum_q )       // p�� data���� q�� data�� ���� ���� ���
			{
				tmp = p->data;
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
	ListNode *p=head;
	int i;
	int sum;
	double average;
	while( p != NULL) {
		printf("�й�        ����   ����   ����   ����   ���\n");
		for (p = head; p !=NULL; p=p->link)
		{
			sum = p->data.eng + p->data.kor + p->data.math;
			average = (double)sum/3;
			printf("%d%7d%7d%7d", p->data,p->data,p->data,p->data);
			for( i=0; i<1; i++)
				printf("%7d%8.2lf\n",sum ,average );
		}
		printf("\n");
	}
}


int main()
{
	ListNode *plist=NULL;   // �����Ҵ� ���� ���� ����ü �迭 ����
	element tmp;
	int i=0,j=0;       // �ݺ������� ����
	
	FILE *fp = fopen("data4.txt","r");  // data4.txt������ �б��������� ����
	if( fp == NULL)                     // ���Ͽ����� ��¹���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 1;
	}

	while(!feof(fp))  // ����ī������ ���� ������ ������ �о��� �ݺ���
	{
		fscanf(fp,"%d %d %d %d", &tmp.studentNumber,&tmp.kor, &tmp.eng, &tmp.math );
	    insert_node(&plist,NULL,create(tmp,NULL));
	}
	printf("Before Sorting!!\n");
	plist = reverse(plist); // ����
	display(plist);         // plist���

	printf("After Sorting!!\n");
	sort(plist);
	display(plist);

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}