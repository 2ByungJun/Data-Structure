///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 2��
// ���α׷���   : ���Ḯ��Ʈ 3
//   ��  ��     : ��ũ�� ����Ʈ�� ������ ������ �ε����� Ȧ����° ��ġ��
//                �����ϴ� �Լ��� �����Ͽ� ��� �Ͻÿ�.
//                - Ȧ����° ��ġ�� �����͸� �����ϴ� �Լ� ����
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int element;       // element�� int �ڷ������� ����
typedef struct ListNode {  // ListNode����ü ����
	element data;          // int�� data
	struct ListNode *link; // ListNode link ������
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
// phead: ��� ����Ʈ�� ���� ������
// p : ������ ����� ������
// removed : ������ ���
void remove_node(ListNode **phead,ListNode *p, ListNode *removed)
{
	if ( p == NULL )  // p�� NULL�� ���
		*phead = ( *phead)->link; // (*phead)�� ��尡 ����Ű�� ���� (*phead)�� ����Ų��
	else              // p�� NULL�� �ƴ� ���
		p->link = removed->link;  // ������ ��尡 ����Ű�� ���� p ��尡 ����Ų��
	free(removed); // removed ����
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
// ����Ʈ ���
void display(ListNode *head)
{
	ListNode *p=head;

	while( p != NULL) {
		if( p->link == NULL){ // p�� NULL�� ����Ų�ٸ�
			printf("%d ",p->data); // ->�� ������ p���� ����Ѵ�
			break;
		}
		printf("%d -> ",p->data);
		p = p->link;
	}
	printf("\n");
}
// Ȧ�� ��° ��ġ ������ ���� �Լ�
void num_removed( ListNode **phead )
{
	ListNode *ph, *prev = NULL; // ph�� prev����Ʈ ����
	int count = 0; // Ȧ�� ��ġ�� �Ǻ��� ����
	ph = *phead;   // ph����Ʈ�� *phead������ �ʱ�ȭ

	while( ph != NULL) 
	{
		if ( count % 2 == 1 ) // Ȧ���� ���
		{
			remove_node(phead,prev,ph); // ��� ���� ����

			if ( prev != NULL)   // ���� ��尡 �����ϴ� ���
				ph = prev->link; // ph�� prev�� ����Ű�� ���� ����Ű�� �Ѵ�.
			else                 // ���� ��尡 �������� ���� ���
				ph = *phead;     // ph�� ������ *phead�� ����
		}
		else // ������ ���� ã�� ���� ���, ���� ���� �̵�
		{
			prev = ph;     // prev�� ph�� ����
			ph = ph->link; // ���� ���� �̵�
		}
		count++;
	}
}
int main()
{
	ListNode *plist=NULL; // plist ���Ḯ��Ʈ ����
	int count=0;          // ���� ������ ������ ���� ����
	int num;              // count�� ���ϱ� ���� ������ �о��� ����
	int i;                // �ݺ� ������ ����

	FILE *fp = fopen("data3.txt","r"); // data3.txt�� �б���·� ����
	if( fp == NULL)                    // ���Ͽ����� �������� ���
	{
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 0;
	}
	
	while(!feof(fp)) // count���� ���ϱ� ���� ������ �о��ִ� �ݺ���
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	rewind(fp); // ���� ��������ġ �ʱ�ȭ
	for(i=0; i<count; i++) // countũ���� �ݺ���
	{
		fscanf(fp,"%d",&num);  // ���� �����Ͱ��� num���� ����
		insert_node(&plist,NULL,create(num,NULL)); // num���� plist����Ʈ�� ����
	}
	plist = reverse(plist); // �����Լ��� �̿��Ͽ� plist�� ����
	display(plist);      // plist���
	
	num_removed(&plist); // plist����Ʈ�� Ȧ����° ����
	display(plist);      // Ȧ����° ������ plist���
	
	fclose(fp);          // ������ �ݾ��ش�
	return 0;
}