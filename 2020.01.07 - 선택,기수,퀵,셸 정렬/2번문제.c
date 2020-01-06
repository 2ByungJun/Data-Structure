///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 16��
// ���α׷���   : ��� ���� ���α׷�
//   ��  ��     : data2.txt�� ����Ǿ� �ִ� 3�ڸ��� �����͸� �ҷ���
//                ������������ �����Ͽ� ����Ͻÿ�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10  // ��Ŷ����
#define MAX_QUEUE_SIZE 100 // ť ����������

typedef int element; // int�� element����
// ť Ÿ�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear;
} QueueType;
// ���� �Լ�
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ť�� ���ִ��� Ȯ���ϴ� �Լ�
int is_full(QueueType *q)
{
	return (q->rear+1)%MAX_QUEUE_SIZE == q->front;
}
// ť ���� �Լ�
void enqueue(QueueType *q,element item)
{
	if( is_full(q) )
		error("ť�� ��ȭ�����Դϴ�\n");
	q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// ť ���� �Լ�(������ Ȱ��)
element dequeue(QueueType *q)
{
	if( is_empty(q) )
		error("ť�� ��������Դϴ�.");
	q->front = (q->front +1)%MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// ��� ����
void radix_sort(int *list, int n)
{
	int i,b,d,factor=1; // i,b,d : �ݺ����� , factor : �ڸ���
	int count=1;
	QueueType queues[BUCKETS]; // ť ��Ŷ10�� ����

	for(b=0; b<BUCKETS; b++)  // ť���� �ʱ�ȭ
		init(&queues[b]);

	// 3�ڸ����� �ݺ�
	for(d=0; d<3; d++){
		printf("\n-Dight %d-\n",count++);

		for(i=0; i<n; i++)    // �����͵��� �ڸ����� ���� ť�� �Է�
			enqueue( &queues[(list[i]/factor)%10], list[i]);

		for(b=i=0; b<BUCKETS; b++)  // ���Ͽ��� ������ list�� ��ģ��.
		{
			printf("Bucket[%d] : ", b);
			if( is_empty(&queues[b]) ) // ��Ŷ�� �ƹ��͵� ���� ����
			{
				printf("Empty");
			}
			while( !is_empty(&queues[b]) ) // ��Ŷ�� ���� �ִٸ� ���
			{
				list[i] = dequeue(&queues[b]); // list[i]�� ������ ť�� ����
				printf("%d ",list[i]);
				i++;
			}
			printf("\n");
		}
		factor *= 10;          // �� ���� �ڸ����� ����.
	}
}

int main()
{
	int *temp;    // ������ temp �����迭 ����
	int num;      // ���� �����Ͱ� ������ �޾� �� ����
	int i=0;      // �ݺ�����
	int count=0;  // ���� ������ ����
	// ���� ����
	FILE *fp= fopen("data2.txt","r");
	if(fp == NULL){
		printf("���� ����\n");
		exit(1);
	}
	// ���� ������ ����üũ
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	// ���� �Ҵ�
	temp = (int *)malloc(sizeof(int)*count);

	// ���������� ����
	rewind(fp);
	// temp[i]�� ���� �����Ͱ� ����
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		temp[i] = num;
		i++;
	}
	// ���� �� ������ ���
	printf("< ������ ������ >\n");
	for( i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n\n");

	// ���� ���� ( ������� ��� )
	printf("< ���� ���� >");
	radix_sort(temp,count);

	// ���� �� ������ ���
	printf("\n< ������ ������ >\n");
	for( i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n");

	free(temp); // temp �����ݳ�
	fclose(fp); // fp ������ �ݽ��ϴ�.
	return 0;
}