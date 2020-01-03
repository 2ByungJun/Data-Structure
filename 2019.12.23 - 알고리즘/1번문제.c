///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 6�� 5��
// ���α׷���   : �л����� �����ϴ� ť �迭
//   ��  ��     : Data.txt���Ͽ� ����Ǿ��ִ� �л� ����(�̸�,�й�,����,
//                ����,����)�� �����ϴ� �迭�� �� ���� ť�� �����ϰ�
//                �Ʒ��� ���� ����϶�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
// �л����� ����ü element ����
typedef struct {
	char name[20]; // �̸�
	int num;       // �й�
	int kor;       // ����
	int mat;       // ����
	int eng;       // ����
}element;
// ���� ťŸ�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear; 
} QueueType;
// ������� �Լ�
void error(char *message)
{
	fprintf(stderr, "%d\n" , message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0; // front�� rear�� 0���� �ʱ�ȭ
}
// ���� ���� Ȯ��
int is_empty(QueueType *q)
{
	return (q->front == q->rear); // front�� rear�� ���� ���� ����Ű�� ��� ��������̴�.
}
// ��ȭ ���� Ȯ��
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front); // �迭�� ũ�Ⱑ ���ѵǾ��ִ�.
}
// ť ����
// q : ť
// item : ����ü
void enqueue(QueueType *q,element item)
{
	if( is_full(q) ) // ��ȭ ���� Ȯ��
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = ( q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item; 
}
// ť ����
// q : ť
element dequeue(QueueType *q)
{
	if(is_empty(q)) // ���� ���� Ȯ��
		error("ť�� ��������Դϴ�");
	q->front = ( q->front+1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

int main()
{
	QueueType q;  // ť ����
	element temp; // temp ����ü����
	int front=0,rear=0; // front,rear ī����
	int i; // �ݺ�����
	FILE *fp = fopen("data1.txt","r"); // data1.txt������ �б��������� ����
	if( fp==NULL ) // ���� ������
	{
		printf("���Ͽ���\n");
		exit(1);
	}

	init(&q); // �ʱ�ȭ �Լ�
	while(!feof(fp))
	{
		fscanf(fp,"%s %d %d %d %d", temp.name, &temp.num, &temp.kor, &temp.mat, &temp.eng); // ����ü ���ϵ����� fscanf()
		enqueue(&q,temp); // q���ÿ� temp ����ü ����
		printf("add(%s %d %d %d %d)\n", temp.name, temp.num, temp.kor, temp.mat, temp.eng ); // ���
		rear++; // ���Խ� rear����
		printf("front = %d   rear = %d\n\n", front,rear);
	}

	for( i=0; i<rear; i++)
	{
		temp = dequeue(&q); // temp����ü�� dequeue(&q)�� ����
		printf("delete(%s %d %d %d %d)\n",temp.name,temp.num,temp.kor,temp.mat,temp.eng); // ������ ����ü ���� ���
		front++; // ������ front����
		printf("front = %d   rear = %d\n\n",front,rear);
	}

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}