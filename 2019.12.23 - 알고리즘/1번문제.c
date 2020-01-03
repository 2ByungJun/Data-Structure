///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 6월 5일
// 프로그램명   : 학생정보 저장하는 큐 배열
//   설  명     : Data.txt파일에 저장되어있는 학생 정보(이름,학번,국어,
//                수학,영어)를 저장하는 배열로 된 원형 큐에 저장하고
//                아래와 같이 출력하라.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
// 학생정보 구조체 element 선언
typedef struct {
	char name[20]; // 이름
	int num;       // 학번
	int kor;       // 국어
	int mat;       // 수학
	int eng;       // 영어
}element;
// 원형 큐타입 선언
typedef struct {
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear; 
} QueueType;
// 에러출력 함수
void error(char *message)
{
	fprintf(stderr, "%d\n" , message);
	exit(1);
}
// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0; // front와 rear를 0으로 초기화
}
// 공백 상태 확인
int is_empty(QueueType *q)
{
	return (q->front == q->rear); // front와 rear이 같은 곳을 가리키는 경우 공백상태이다.
}
// 포화 상태 확인
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front); // 배열은 크기가 제한되어있다.
}
// 큐 삽입
// q : 큐
// item : 구조체
void enqueue(QueueType *q,element item)
{
	if( is_full(q) ) // 포화 상태 확인
		error("큐가 포화상태입니다");
	q->rear = ( q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item; 
}
// 큐 삭제
// q : 큐
element dequeue(QueueType *q)
{
	if(is_empty(q)) // 공백 상태 확인
		error("큐가 공백상태입니다");
	q->front = ( q->front+1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

int main()
{
	QueueType q;  // 큐 선언
	element temp; // temp 구조체선언
	int front=0,rear=0; // front,rear 카운팅
	int i; // 반복변수
	FILE *fp = fopen("data1.txt","r"); // data1.txt파일을 읽기형식으로 오픈
	if( fp==NULL ) // 파일 에러시
	{
		printf("파일에러\n");
		exit(1);
	}

	init(&q); // 초기화 함수
	while(!feof(fp))
	{
		fscanf(fp,"%s %d %d %d %d", temp.name, &temp.num, &temp.kor, &temp.mat, &temp.eng); // 구조체 파일데이터 fscanf()
		enqueue(&q,temp); // q스택에 temp 구조체 삽입
		printf("add(%s %d %d %d %d)\n", temp.name, temp.num, temp.kor, temp.mat, temp.eng ); // 출력
		rear++; // 삽입시 rear증가
		printf("front = %d   rear = %d\n\n", front,rear);
	}

	for( i=0; i<rear; i++)
	{
		temp = dequeue(&q); // temp구조체에 dequeue(&q)를 대입
		printf("delete(%s %d %d %d %d)\n",temp.name,temp.num,temp.kor,temp.mat,temp.eng); // 삭제한 구조체 내용 출력
		front++; // 삭제시 front증가
		printf("front = %d   rear = %d\n\n",front,rear);
	}

	fclose(fp); // 파일을 닫아준다
	return 0;
}