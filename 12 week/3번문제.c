///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 6�� 5��
// ���α׷���   : ���Ḯ��Ʈ�� �̿��� �� ���α׷�
//   ��  ��     : ���Ḯ��Ʈ�� �̿��� Deque ���α׷��� �̿��Ͽ� data.txt
//                ���Ͽ� ����� �����͸� �Է� �޾� Deque�� ����Ǵ� ����
//                �� �Ʒ��� ���ǿ� �°� ���α׷��� �Ͻÿ�.
//                - add front Ű���� �Է� �� ���ʿ� ������ ����
//                - add rear Ű���� �Է� �� ���ʿ� ������ ����
//                - delete front Ű���� �Է� �� ���ʿ� ������ ����
//                - delete rear Ű���� �Է� �� ���ʿ� ������ ����
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// TRUE�� FALSE ����
#define TRUE 1
#define FALSE 0
// ť ���
typedef int element;
typedef struct QueueNode{
	element data;
	struct DlistNode *llink; // �¸�ũ
	struct DlistNode *rlink; // �층ũ
}DlistNode;
// �� Ÿ��
typedef struct DequeType {
	DlistNode *head; // ���
	DlistNode *tail; // ����
} DequeType;

// ���� ��� �Լ�
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(DequeType *dq)
{
	dq->head=dq->tail=NULL;
}
// ���� �Ǵ��Լ�
int is_empty(DequeType *dq)
{
	if( dq->head == NULL )
		return TRUE;
	else return FALSE;
}
// ��� ���� �Լ�
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
	// DlistNodeŸ���� ���� ����
	DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
	if( node == NULL ) error("�޸� �Ҵ� ����");
	node->llink = llink; // �¸�ũ ����
	node->data = item;   // data�� item�� ����
	node->rlink = rlink; // �층ũ ����
	return node; // ��� ����
}
// ���� ���� �Լ�
void add_rear(DequeType *dq, element item)
{
	// DlistNodeŸ���� new_node����( llink�� tail, rlink�� NULL )
	DlistNode *new_node = create_node(dq->tail,item,NULL);
	if( is_empty(dq)) // ������ ���
		dq->head = new_node; // head�� new_node
	else
		dq->tail->rlink = new_node; // tail->rlink�� new_node�� ����Ŵ
	dq->tail = new_node; // tail�� �̵�
}
// ���� ���� �Լ�
void add_front(DequeType *dq, element item)
{
	// DlistNodeŸ���� new_node����( llink�� NULL, rlink�� head )
	DlistNode *new_node = create_node(NULL,item,dq->head);

	if( is_empty(dq)) // ������ ���
		dq->tail = new_node; // tail�� new_node
	else
		dq->head->llink = new_node; // head->llink�� new_node�� ����Ŵ
	dq->head = new_node; // head�� �̵�
}
// ���� ���� �Լ�
element delete_front(DequeType *dq)
{
	element item;
	DlistNode *removed_node; // removed_node����
	 // ������ ���
	if( is_empty(dq)) error("���� ������ ����");
	else { // �ƴ� ���
		removed_node = dq->head; // head�� ����Ŵ
		item = removed_node->data;  // removed������ item�� ���� 
		dq->head = dq->head->rlink; // head �̵�
		free(removed_node);      // removed_node ����
		if( dq->head == NULL )   // head�� NULL�� ���
			dq->tail = NULL;     // tail�� NULL�� ����
		else
			dq->head->llink=NULL; // head->llink�� NULL�� ����
	}
	return item; // �� ����
}
// ���� ���� �Լ�
element delete_rear(DequeType *dq)
{
	element item;
	DlistNode *removed_node; // removed_node����
	 // ������ ���
	if( is_empty(dq)) error("���� ������ ����");
	else { // �ƴ� ���
		removed_node = dq->tail; // tail�� ����Ŵ
		item = removed_node->data;  // removed������ item�� ���� 
		dq->tail = dq->tail->llink; // tail �̵�
		free(removed_node);      // removed_node ����
		if( dq->tail == NULL )   // tail�� NULL�� ���
			dq->head = NULL;     // head�� NULL�� ����
		else
			dq->tail->rlink=NULL; // tail->llink�� NULL�� ����
	}
	return item; // �� ����
}
// ��� �Լ�
void display(DequeType *dq,int qcount)
{
	int i;
	DlistNode *temp = dq->head; // temp�� head�� ��ġ
	// ť (��)��ȣ
	printf("����");
	for(i=0; i<qcount; i++)
		printf("����");
	printf("����\n");
    // ť ������ ���
	for(i=0; i<qcount; i++){ // ť ������ŭ ���
		printf("  %d",temp->data );
		temp = temp->rlink; // ���� ���� �̵�
	}
	printf("\n");
	// ť (��)��ȣ
	printf("����");
	for(i=0; i<qcount; i++)
		printf("����");
	printf("����\n");
}

int main()
{
	DequeType q; // �� ����
	char nameq1[30],nameq2[30];  // add,delete �Ǵ�/front,rear �Ǵ�
	int num; // ���Լ���
	int step=1,qcount=0; // ����, ť ������ ����
	FILE *fp = fopen("data3.txt","r"); // data3.txt �б��������� ����
	if( fp==NULL ) // ���� ������
	{
		printf("���� ����\n");
		exit(1);
	}
	init(&q); // q �ʱ�ȭ

	while(!feof(fp))
	{
		fscanf(fp,"%s %s",nameq1,nameq2); // add,delete/front,rear�� ���Ͽ��� �޾ƿ�
		if( strcmp(nameq1,"add") == 0) // add�� ���
		{
			if( strcmp(nameq2,"front") == 0) // front�� ���
			{
				fscanf(fp,"%d",&num); // num���� �޾ƿ´�.
				add_front(&q,num);    // ���ʿ� ����
				qcount++;             // ť �����Ͱ��� 1 ����
				printf("---Step %d : add front %d ---\n",step,num);
				display(&q,qcount);   // ���
				step++; // ��������
			}
			else if( strcmp(nameq2,"rear") == 0) // rear�� ���
			{
				fscanf(fp,"%d",&num); // num���� �޾ƿ´�.
				add_rear(&q,num); // ���ʿ� ����
				qcount++;             // ť �����Ͱ��� 1 ����
				printf("---Step %d : add rear %d ---\n",step,num);
				display(&q,qcount);   // ���
				step++; // ��������
			}
		}
		else if( strcmp(nameq1,"delete") == 0 ) // delete�� ���
		{
			if( strcmp(nameq2,"front") == 0) // front�� ���
			{
				delete_front(&q);     // ť ����
				qcount--;             // ť �����Ͱ��� 1 ����
				printf("---Step %d : delete front ---\n",step);
				display(&q,qcount);   // ���
				step++; // ��������
			}
			else if( strcmp(nameq2,"rear") == 0) // rear�� ���
			{
				delete_rear(&q);      // ť ����
				qcount--;             // ť �����Ͱ��� 1 ����
				printf("---Step %d : deleteq rear ---\n",step);
				display(&q,qcount);   // ���
				step++; // ��������
			}
		}
	}

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}