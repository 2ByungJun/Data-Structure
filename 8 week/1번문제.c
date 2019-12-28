///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 2��
// ���α׷���   : ���Ḯ��Ʈ 1
//   ��  ��     : å P.132�� ���α׷� 4.12�� �ۼ��ϰ� �� ���ư����� Ȯ��
//                �Ͻÿ�.
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
// ���
void display(ListNode *head)
{
	ListNode *p=head;
	while( p != NULL) {
		printf("%d->",p->data);
		p = p->link;
	}
	printf("\n");
}
// ��尪 Ž��
ListNode *search(ListNode *head,int x)
{
	ListNode *p;
	p = head;
	while( p != NULL ){
		if(p->data == x ) return p; // Ž������
		p = p->link;
	}
	return p; // Ž���� ������ ��� NULL ��ȯ
}
// ���� 
ListNode *concat(ListNode *head1,ListNode *head2)
{
	ListNode *p;
	if( head1 == NULL ) return head2;       // head1�� NULL�� ��� head2 ����
	else if ( head2 == NULL ) return head1; // head2�� NULL�� ��� head1 ����
	else
	{
		p = head1;  // p��忡 head1��带 ����
		while( p->link != NULL ) // p�� NULL�� ������ �ݺ�
			p = p->link;         // ���� p�� ����Ų��
		p->link = head2;         // p�� ������ ��尡 head2�� ����Ű���� �Ѵ�. 
		return head1;            // head1�� head2�� ����� ���·� ����
	}
}
// ����
ListNode *reverse(ListNode *head)
{
	// ��ȸ ������
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
// �������� ��带 ����
ListNode *create(element data,ListNode *link) 
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// �׽�Ʈ ���α׷�
int main()
{
	ListNode *list1=NULL, *list2=NULL; // list1�� list2�� NULL�� �ʱ�ȭ�� ���·� ���� 
	ListNode *p;                       // p ����Ʈ ����

	// list1 = 30->20->10
	insert_node(&list1,NULL,create(10,NULL)); // list1�� �ִ� 10�� NULL�����κп� ������� ����
	insert_node(&list1,NULL,create(20,NULL)); // list1�� �ִ� 20�� NULL�����κп� ������� ����
	insert_node(&list1,NULL,create(30,NULL)); // list1�� �ִ� 30�� NULL�����κп� ������� ����
	display(list1);                           // list1 ���

	// list1 = 20->10
	remove_node(&list1,NULL,list1); // list1���� NULL�� ����Ű�� ��尪�� ���� 
	display(list1);                 // list1 ���

	// list2 = 80->70->60
	insert_node(&list2,NULL,create(60,NULL)); // list2�� �ִ� 60�� NULL�����κп� ������� ����
	insert_node(&list2,NULL,create(70,NULL)); // list2�� �ִ� 70�� NULL�����κп� ������� ����
	insert_node(&list2,NULL,create(80,NULL)); // list2�� �ִ� 80�� NULL�����κп� ������� ����
	display(list2);                           // list2 ���

	// list1 = list1 + list2
	list1 = concat(list1 , list2); // list1�� list1�� list2�� �����Ͽ� �����մϴ�.
	display(list1);                // list1+list2�� ����� list1�� ���
	
	// list1�� ��������
	list1 = reverse(list1);        // list1�� list1�� �������� ǥ���� ����Ʈ�� �����մϴ�.
	display(list1);                // list1 ���

	// list1���� 20Ž��
	p = search(list1,20);          // list1���� 20�� Ž���մϴ�.
	printf("Ž������: %d\n", p->data);

	return 0;
}
