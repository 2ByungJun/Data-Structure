///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 9�� 5��
// ���α׷���   : ���Ͽ��� �ڷ� �о���� 1
//   ��  ��     : ���Ͽ��� �ڷḦ �о�� ��ũ�� ����Ʈ�� �����ϴ� ������
//                �ۼ��ϰ� �Ʒ� ������ �����ϰ� ����ϴ� ���α׷��� �ۼ��϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ( (t) = (x), (x)=(y), (y)=(t)); // ��������

typedef int element;
typedef struct ListNode {
	element data;           // ����Ʈ ������ ��
	struct ListNode *link;  // ����Ʈ ��ũ(��:1����,2����...)
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
// data : ����Ʈ ��
// link : ����Ʈ ��ũ
ListNode *create_node(element data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// ��������
// list : ����Ʈ
// n : ���� ������ ��
void bubble_sort_up(ListNode *list,int n)
{
	ListNode *p=list; // ����Ʈp�� list�� ����ʱ�ȭ
	int i,j,temp; // �ݺ�����,��ȯ����temp

	for( i=n-1; i>0; i--) { // i���� ��-1���� �ʱ�ȭ �� ����
		p=list;             // p�� list����� �ʱ�ȭ
		for(j=0; j<i; j++)  // j���� 0���� �ʱ�ȭ �� ����
		{
			if(p->data > p->link->data )            // ����Ʈp �����Ͱ��� ���� �����Ͱ��� ��
				SWAP(p->data, p->link->data ,temp); // ����
			p = p->link;    // ���� ���� �̵�
		}
	}
}

// ��������
// list : ����Ʈ
// n : ���� ������ ��
void bubble_sort_down(ListNode *list,int n)
{
	ListNode *p=list; // ����Ʈp�� list�� ����ʱ�ȭ
	int i,j,temp; // �ݺ�����,��ȯ����temp

	for( i=n-1; i>0; i--) {
		p=list;           
		for(j=0; j<i; j++) 
		{
			if(p->data < p->link->data )            // ���������� �ٸ��� ���������Ͱ����� ���� ���
				SWAP(p->data, p->link->data ,temp); // ����
			p = p->link;
		}
	}
}

// ���
void display(ListNode *head)
{
	ListNode *p=head;
	while( p != NULL ) {
		if( p->link == NULL) // ������ NULL���� ���� '->' ���� ���
			printf("%d ",p->data);
		else
			printf("%d ->", p->data);
		p = p->link;
	}
	printf("\n");
}

int main()
{
	ListNode *list=NULL; // ����Ʈ ����
	int count=0;         // ���� ������ �� ��
	int num;             // ���� �����͸� �޾ƿ� ����

	FILE *fp = fopen("data1.txt","r"); // data1.txt�� �б��������� ����
	if( fp==NULL) // ���� ������
	{
		error("���� �б� ����\n");
		return 1;
	}

	while(!feof(fp)) // ���������� ��ġ�� ���� ���� ������ �ݺ�
	{
		fscanf(fp,"%d", &num ); // ���� �����Ͱ��� num���� �Է�
		insert_node(&list,NULL,create_node(num,NULL)); // num���� NULL��ġ�� �������� �� ����
		count++; // ī����
	}

	bubble_sort_up(list,count);  // �����Ʈ up����(��������)
	printf("<�������� ����>\n"); 
	display(list); // ����Ʈ���

	printf("\n");

	bubble_sort_down(list,count);  // �����Ʈ down����(��������)
	printf("<�������� ����>\n");
	display(list); // ����Ʈ���

	fclose(fp); // ������ �ݾ��ش�.
	return 0;
}