///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 13��
// ���α׷���   : �����ͷ� ������ �ܼ� ���Ḯ��Ʈ
//   ��  ��     : Data.txt���Ͽ� ����� ������ ���� ���� ����Ʈ�� �����ϰ� 
//                172�� ���� ��带 �����ѵ� ����ȭ�Ͽ� ù ���,������ 
//                ���,������ ����� ��ũ�� ����Ű�� �ִ� ����� ���� ����Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int element;
// ����ü ����
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
// �������� ��带 ����
ListNode *create_node(element data,ListNode *link) 
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// �����Լ�
void insert_last(ListNode **phead, ListNode *node)
{
    if (*phead == NULL) { // *phead�� NULL���
        *phead = node;
        node->link = node;
    }
    else { // *phead�� NULL�� �ƴ� ���
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node;
    }
}
// �����Լ�
void remove_first(ListNode **phead)
{
    ListNode* removed;
    if (*phead == NULL) return;      //���鸮��Ʈ�� ��� �������� �ʰ� �׳� �Լ� ����
    else if (*phead == (*phead)->link) {//��尡 �ϳ��� ���
        removed = *phead;
        *phead = NULL;
    }
    else {//��尡 �� �̻��� ���
        removed = (*phead)->link; //���۳�尡 ������ ����.
        (*phead)->link = removed->link;     
    }//(*phead)->link�� ���۳������ ����Ű�µ� �װ� removed�� ���۳���� ���������removed->link�� ���ش� 
    free(removed);              //������ ���� free�Լ��� �޸� ������ �ݵ�� ������Ѵ�.
}
void remove_middle(ListNode **phead, ListNode *pre) //pre�� ������ ����� ������ ���
{
    ListNode* removed;
    if (*phead == NULL) return;      //���鸮��Ʈ�� ��� �������� �ʰ� �׳� �Լ� ����
    else if (*phead == pre->link) {      //�����ڳ���� ������尡 phead�� ������ ��尡 ������ ����� ��� 
        removed = *phead;
        pre->link = (*phead)->link;
        *phead = pre;
    }
    else {//��尡 ���۳���̰ų� �߰������ ���        
        removed = pre->link;
        pre->link = removed->link; //ù��°�� ����°��̱� ������ phead�� ����� �ʿ䰡 ����.
    }
    free(removed);               //������ ���� free�Լ��� �޸� ������ �ݵ�� ������Ѵ�.
}
void remove_last(ListNode **phead)
{
    ListNode* removed, *pre;    //pre�� ������ ����� ������ ���
    if (*phead == NULL) return;      //���鸮��Ʈ�� ��� �������� �ʰ� �׳� �Լ� ����
    else if (*phead == (*phead)->link) {//��尡 �ϳ��� ���
        removed = *phead;
        *phead = NULL;
    }
    else {//��尡 �� �̻��� ���
        pre = (*phead)->link;
        while (*phead != pre->link)
            pre = pre->link;       //phead�� ������ ��� ��ġ Ž��(�������� ��ũ�ʵ尡 �����ڳ���� �ּҰ� �Ǿ�� �Ѵٴ� ��)
        removed = *phead;       //phead�� ������ ���
        pre->link = removed->link; //���۳���� �ּҸ� ����.
        *phead = pre;           //������ ��尡 ������ ���� �������ش�.
 
    }
    free(removed);               //������ ���� free�Լ��� �޸� ������ �ݵ�� ������Ѵ�.
}
// ����
ListNode *reverse(ListNode *phead)
{
	ListNode *p, *q, *r;
	p = phead->link;    // ���۳�� �ּ� ����
	q = phead;         // q�� �������� ���� ���
	while (p != phead) {
		r = q;         // r�� �������� �� ����Ʈ, r�� q , q�� p�� ���ʷ� ����
		q = p;
		p = p->link;
		q->link = r; // q�� ��ũ ������ ����
	}
	phead = phead->link;
	p->link = q;
	return phead;
}
// ����Ʈ�� �׸� ���
void display(ListNode *head)
{
	ListNode *p;  // p����Ʈ ����
	int head_num; // ��� ����
	int tail_num; // ���� ����
	if( head == NULL ) return; // ��尡 NULL ��� ����

	p = head; // p�� head�� ����Ű�� �Ѵ�
	head_num = p->link->data; // ��忡 p�� ������ũ �����͸� �����Ѵ�
	printf("< ");
	do {
		if( p->link == head )         // p������ũ�� ����� ���
			tail_num = p->link->data; // ���Ͽ� p�� ������ũ �����͸� ����
		p = p->link; // p�� �������� �Ѿ��
		printf("%d ",p->data); // p������ ���
	}while( p != head); // p�� ��忡 �����Ҷ����� �ݺ���
	printf(">\n");

	printf("Head : %d\n",head_num);
	printf("Tail : %d\n",tail_num);
	printf("Tail Next : %d\n",head_num);
	printf("\n");
}
// display������
void display_reverse(ListNode *head)
{
	ListNode *p;
	int head_num;
	int tail_num;
	if( head == NULL ) return;

	p = head;
	head_num = p->data;
	printf("< ");
	do {
		if( p->link == head )
			tail_num = p->data;
		printf("%d ",p->data);
		p = p->link;
	}while( p != head);
	printf(">\n");

	printf("Head : %d\n",head_num);
	printf("Tail : %d\n",tail_num);
	printf("Tail Next : %d\n",head_num);
	printf("\n");
}
// �� �װ� �� �� ��� ����
void delete_node(ListNode *head,int count)
{
	ListNode *p = head; // p�� ��带 ����Ų��
	ListNode *q = NULL; // q�� NULL�� ����Ų��
	int i=0; // ����������

	if( p->data == 172 ){ // ù��° ��尡 172�� ���
		remove_first(&p); // ù��° ��� ����
		p=p->link; // p�� ������ũ�� ����Ų��
	}
	else{  // �ƴҰ��
		p=p->link;} // p�� ������ũ�� ����Ų��

	q = head; // q�� ����� ����Ų��
	while(i<count-2){ // count-2��(ù��,������ ����)ũ���� �ݺ���
		 // �߰� ��� �� 172��� ����
		if( p->data == 172 )
			remove_middle(&p,q);
		p=p->link; // p�� ������带 ����Ų��
		q=q->link; // q�� ������带 ����Ų��
		i++; // i�� ����
	}
}
// Ž��
ListNode* search(ListNode *head, element x)
{
    ListNode *p;             
    p = head->link;          //ù��° ��������Ʈ���� ���� ���� p= head �� �ϰ� ������ ������ �����ص� �������.
    do {
        if (p->data == x)  // ���� ���ٸ� 
			return p; //Ž�� ����
 
        p = p->link;      //if�� �������� ������ p�� �̵�������
    } while (p != head->link);
    return NULL; //Ž�� ����  //if���� �������� �ʾƼ� ������ ���������� �ȴٸ�, �׳� null�� return�ؼ� ������ ����.
 
}
int main()
{
	ListNode *list1=NULL; // list1 ����
	int num;              // ���� �����Ͱ� ����
	int count=0;          // ���� ������ ����

	FILE *fp = fopen("data2.txt","r"); // "data2.txt"�� �б��������� ����
	if(fp==NULL){  // ���� ������
		printf("������ ������ �ʾҽ��ϴ�\n");
		return 1;
	}
	while(!feof(fp)) // ���������Ͱ� ���� �����Ҷ����� �ݺ�
	{
		fscanf(fp,"%d",&num); // num���� ���ϵ����� ����
		insert_last(&list1, create_node(num,NULL) ); // list1�� num���� NULL�� ����Ű�� ��带 ������ ����
		count++; // ī����
	}
	display(list1); // list1 ���

	// ����Ʈ172
	printf("< Delete 172 >\n");
	delete_node(list1,count); // ù��° ��尪�� �߰���尪�� 172�� ���
	if( search(list1,172) ) // ������ ��尪�� 172�� ���
	remove_last(&list1); // �� ��尪 ����
	// ������
	printf("< Reverse >\n\n");
	reverse(list1); // list1 ������
	display_reverse(list1); // list1 ���

	fclose(fp); // ������ �ݾ��ش�
	return 0;   
}