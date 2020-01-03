///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 13��
// ���α׷���   : �����ͷ� ������ �ܼ� ���Ḯ��Ʈ
//   ��  ��     : Data.txt���Ͽ� ����� ������ ��ũ�� ����Ʈ�� ������
//                �ܼ� ���� ����Ʈ�� �����ϰ� Ű����� ���� �Է¹޾�
//                ����Ʈ�� �߾ӿ� �����ϰ� �� ����� ����Ͻÿ�.
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
// �������� ��带 ����
ListNode *create(element data,ListNode *link) 
{
	ListNode *new_node; // ��� ����
	new_node = (ListNode *)malloc(sizeof(ListNode)); // ��� �����Ҵ�
	if( new_node == NULL ) error("�޸� �Ҵ� ����"); // ������
	new_node->data = data; // data������ �ʱ�ȭ
	new_node->link = link; // link������ �ʱ�ȭ
	return(new_node); // new_node����
}
// ����
ListNode *reverse(ListNode *head)
{
	// ��ȸ ������
	ListNode *p,*q, *r; 
	p = head;           // head�� ����Ű�� p
	q = NULL;           // NULL�� ����Ű�� q
	while ( p != NULL){ // p����Ʈ�� ���� ������ ������
		r = q;          // r�� q�� ����Ŵ
		q = p;          // q�� p�� ����Ŵ
		p = p->link;    // p�� ������ũ�� �̵�
		q->link = r;    // r�� q������ũ�� �̵�
	}
	return q; // q��ȯ
}
// ���
void display(ListNode **head,int count)
{
	ListNode *p=*head; // ����������� ����Ű�� p
	int i;   // �ݺ���
	int num; // �Է¹��� ��
	int count1 = count; // count���� count1���� ����
	while(1){
		p = *head;
		// ���Ŀ� ���� ���
		printf("< ");
		while( p != NULL) {
			printf("%d ",p->data);
			p = p->link;
		}
		printf(">\n");

		// 0�Է½� ����
		printf("���� �� ���� �Է��ϼ���(0:����) : ");
		scanf("%d",&num);
		if ( num == 0 )
			break;
		// 0�� �ƴҰ��
		else{ 
			p = *head; // p�� ��������尪�� ����Ŵ
			for ( i=0; i<(count1-1)/2; i++){ // (�����Ͱ���-1)/2 ũ�⸸ŭ�� �ݺ���
				p=p->link; // p�� ������ũ�� �̵�
			}
			insert_node(head,p,create(num,NULL)); // w�߰������� num���� ����
		}
		count1++; // count1���� �÷��ش�
	}
}
int main()
{
	ListNode *list1=NULL; // list1����
	int num;              // �����͸� �޾� ������ ����
	int count=0;          // ���ϵ����� ����
	FILE *fp = fopen("data1.txt","r"); // "data1.txt"������ �б��������� ����
	if(fp ==NULL) // ���� ������
	{
		printf("���� ����\n");
		return 1;
	}

	while(!feof(fp)) // ���������Ͱ� �����Ҷ������� �ݺ���
	{
		fscanf(fp,"%d",&num); // num���� ���ϵ����Ͱ� �Է�
		insert_node(&list1,NULL,create(num,NULL)); // list1����Ʈ�� num���� ���� 
		count++; // ���ϵ����� �� ī����
	}
	list1 = reverse(list1); // list1�� ������
	display(&list1,count);  // ����Ʈ ���

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}