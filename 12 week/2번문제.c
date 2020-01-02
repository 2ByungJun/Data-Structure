///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 6�� 5��
// ���α׷���   : ���Ḯ��Ʈ�� �̿��� ť ���α׷�
//   ��  ��     : ���Ḯ��Ʈ�� �̿��� ť ���α׷��� �̿��Ͽ� data.txt����
//                �� ����� �����͸� �Է� �޾� ť�� ����Ǵ� ������ �Ʒ�
//                �� ���ǿ� �°� ���α׷����Ͻÿ�.
//                - addq Ű���� �Է� �� ������ ����
//                - deleteq Ű���� �Է� �� ������ ����
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// ť ���� ťŸ�� ����
typedef int element;
typedef struct QueueNode{
	element item;
	struct QueueNode *link;
}QueueNode;
typedef struct {
	QueueNode *front, *rear;
}QueueType;
// ������� �Լ�
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = NULL;
}
// ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == NULL);
}
// ���� �Լ�
void enqueue(QueueType *q,element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if(temp == NULL ) // temp�� NULL�� ���
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->item = item; // item�� ����
		temp->link = NULL; // NULL�� ����Ų��
		if( is_empty(q) ) { // ������ ��� front,rear�� temp����
			q->front = temp; 
			q->rear = temp;
		}
		else { // ������ �ƴ� ���(�Ϲ���)
			q->rear->link = temp; // q->rear ��ũ�� temp�� ����Ű����
			q->rear = temp; // q->rear���� temp�� ����
		}
	}
}
// ���� �Լ�
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front; // q->front�� ����Ų��.
	element item;
	if( is_empty(q) ) // ������ ���
		error( "ť�� ��� �ֽ��ϴ�");
	else {
		item = temp->item; // item�� temp->item�� ����
		q->front = q->front->link; // front�� ������ ����Ű���Ѵ�.
		if( q->front == NULL ) // front�� NULL�� ��� rear�� NULL�� ����Ŵ
			q->rear = NULL;
		free(temp); // temp ����
		return item;// ������ temp�� ����
	}
}
// ��� �Լ�
// head : ť ����Ʈ
// qcount : ť ������ ����
void display(QueueType *head,int qcount)
{
	int i;
	QueueNode *temp = head->front; // temp�� head->front�� ����Ű���Ѵ�.

	// ť (��)��ȣ
	printf("����");
	for(i=0; i<qcount; i++)
		printf("������");
	printf("����\n");
    // ť ������ ���
	for(i=0; i<qcount; i++){ // ť ������ŭ ���
		printf("  %d",temp->item);
		temp = temp->link; // ���� ���� �̵�
	}
	printf("\n");
	// ť (��)��ȣ
	printf("����");
	for(i=0; i<qcount; i++)
		printf("������");
	printf("����\n");

}
int main()
{
	QueueType q;    // ť ����
	char nameq[10]; // addq,deleteq �Ǵ�
	int num;        // ���Լ���
	int step=1,qcount=0; // ����, ť ������ ����
	FILE *fp = fopen("data2.txt","r"); // data2.txt �б��������� ����
	if( fp==NULL ) // ���� ������
	{
		printf("���� ����\n");
		exit(1);
	}
	init(&q); // q �ʱ�ȭ

	while(!feof(fp))
	{
		fscanf(fp,"%s",nameq); // addq,deleteq�� ���Ͽ��� �޾ƿ�
		if( strcmp(nameq,"addq") == 0) // addq�� ���
		{
			fscanf(fp,"%d",&num); // num���� �޾ƿ´�.
			enqueue(&q,num);      // ť�� num����
			qcount++;             // ť �����Ͱ��� 1 ����
			printf("---Step %d : addq %d ---\n",step,num);
			display(&q,qcount);   // ����Լ� 
			step++; // ��������
		}
		else if( strcmp(nameq,"deleteq") == 0 ) // deleteq�� ���
		{
			dequeue(&q); // ť ����
			qcount--; // ť �����Ͱ��� 1 ����
			printf("---Step %d : deleteq ---\n",step);
			display(&q,qcount); // ����Լ� 
			step++; // ��������
		}
	}

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}
