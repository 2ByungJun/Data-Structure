///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 16일
// 프로그램명   : 기수 정렬 프로그램
//   설  명     : data2.txt에 저장되어 있는 3자릿수 데이터를 불러와
//                오름차순으로 정렬하여 출력하시오.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10  // 버킷정의
#define MAX_QUEUE_SIZE 100 // 큐 사이즈정의

typedef int element; // int형 element정의
// 큐 타입 정의
typedef struct {
	element queue[MAX_QUEUE_SIZE]; 
	int front, rear;
} QueueType;
// 에러 함수
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 큐가 비어있는지 확인하는 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 큐가 차있는지 확인하는 함수
int is_full(QueueType *q)
{
	return (q->rear+1)%MAX_QUEUE_SIZE == q->front;
}
// 큐 삽입 함수
void enqueue(QueueType *q,element item)
{
	if( is_full(q) )
		error("큐가 포화상태입니다\n");
	q->rear = (q->rear+1)%MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
// 큐 삭제 함수(꺼내어 활용)
element dequeue(QueueType *q)
{
	if( is_empty(q) )
		error("큐가 공백상태입니다.");
	q->front = (q->front +1)%MAX_QUEUE_SIZE;
	return q->queue[q->front];
}
// 기수 정렬
void radix_sort(int *list, int n)
{
	int i,b,d,factor=1; // i,b,d : 반복변수 , factor : 자릿수
	int count=1;
	QueueType queues[BUCKETS]; // 큐 버킷10개 생성

	for(b=0; b<BUCKETS; b++)  // 큐들의 초기화
		init(&queues[b]);

	// 3자리까지 반복
	for(d=0; d<3; d++){
		printf("\n-Dight %d-\n",count++);

		for(i=0; i<n; i++)    // 데이터들을 자릿수에 따라 큐에 입력
			enqueue( &queues[(list[i]/factor)%10], list[i]);

		for(b=i=0; b<BUCKETS; b++)  // 버켓에서 꺼내어 list로 합친다.
		{
			printf("Bucket[%d] : ", b);
			if( is_empty(&queues[b]) ) // 버킷에 아무것도 없을 조건
			{
				printf("Empty");
			}
			while( !is_empty(&queues[b]) ) // 버킷에 값이 있다면 출력
			{
				list[i] = dequeue(&queues[b]); // list[i]에 삭제한 큐값 대입
				printf("%d ",list[i]);
				i++;
			}
			printf("\n");
		}
		factor *= 10;          // 그 다음 자릿수로 간다.
	}
}

int main()
{
	int *temp;    // 정수형 temp 동적배열 생성
	int num;      // 파일 데이터값 정수를 받아 올 변수
	int i=0;      // 반복변수
	int count=0;  // 파일 데이터 개수
	// 파일 오픈
	FILE *fp= fopen("data2.txt","r");
	if(fp == NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 파일 데이터 개수체크
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	// 동적 할당
	temp = (int *)malloc(sizeof(int)*count);

	// 파일포인터 리셋
	rewind(fp);
	// temp[i]에 파일 데이터값 대입
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		temp[i] = num;
		i++;
	}
	// 정렬 전 데이터 출력
	printf("< 정렬전 데이터 >\n");
	for( i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n\n");

	// 정렬 과정 ( 기수정렬 사용 )
	printf("< 정렬 과정 >");
	radix_sort(temp,count);

	// 정렬 후 데이터 출력
	printf("\n< 정렬후 데이터 >\n");
	for( i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n");

	free(temp); // temp 동적반납
	fclose(fp); // fp 파일을 닫습니다.
	return 0;
}