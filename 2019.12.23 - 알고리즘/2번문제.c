///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 6월 5일
// 프로그램명   : 연결리스트를 이용한 큐 프로그램
//   설  명     : 연결리스트를 이용한 큐 프로그램을 이용하여 data.txt파일
//                에 저장된 데이터를 입력 받아 큐에 저장되는 과정을 아래
//                에 조건에 맞게 프로그래밍하시오.
//                - addq 키워드 입력 시 데이터 삽입
//                - deleteq 키워드 입력 시 데이터 삭제
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// 큐 노드와 큐타입 정의
typedef int element;
typedef struct QueueNode{
	element item;
	struct QueueNode *link;
}QueueNode;
typedef struct {
	QueueNode *front, *rear;
}QueueType;
// 에러출력 함수
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = NULL;
}
// 공백 상태 함수
int is_empty(QueueType *q)
{
	return (q->front == NULL);
}
// 삽입 함수
void enqueue(QueueType *q,element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if(temp == NULL ) // temp가 NULL일 경우
		error("메모리를 할당할 수 없습니다");
	else {
		temp->item = item; // item값 대입
		temp->link = NULL; // NULL을 가리킨다
		if( is_empty(q) ) { // 공백일 경우 front,rear에 temp설정
			q->front = temp; 
			q->rear = temp;
		}
		else { // 공백이 아닐 경우(일반적)
			q->rear->link = temp; // q->rear 링크가 temp를 가리키게함
			q->rear = temp; // q->rear값에 temp값 대입
		}
	}
}
// 삭제 함수
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front; // q->front로 가리킨다.
	element item;
	if( is_empty(q) ) // 공백일 경우
		error( "큐가 비어 있습니다");
	else {
		item = temp->item; // item에 temp->item값 대입
		q->front = q->front->link; // front를 다음을 가리키게한다.
		if( q->front == NULL ) // front가 NULL일 경우 rear도 NULL을 가리킴
			q->rear = NULL;
		free(temp); // temp 삭제
		return item;// 삭제한 temp값 리턴
	}
}
// 출력 함수
// head : 큐 리스트
// qcount : 큐 데이터 개수
void display(QueueType *head,int qcount)
{
	int i;
	QueueNode *temp = head->front; // temp를 head->front로 가리키게한다.

	// 큐 (상)괄호
	printf("┌─");
	for(i=0; i<qcount; i++)
		printf("───");
	printf("─┐\n");
    // 큐 데이터 출력
	for(i=0; i<qcount; i++){ // 큐 개수만큼 출력
		printf("  %d",temp->item);
		temp = temp->link; // 다음 노드로 이동
	}
	printf("\n");
	// 큐 (하)괄호
	printf("└─");
	for(i=0; i<qcount; i++)
		printf("───");
	printf("─┘\n");

}
int main()
{
	QueueType q;    // 큐 생성
	char nameq[10]; // addq,deleteq 판단
	int num;        // 대입숫자
	int step=1,qcount=0; // 스텝, 큐 데이터 개수
	FILE *fp = fopen("data2.txt","r"); // data2.txt 읽기형식으로 오픈
	if( fp==NULL ) // 파일 에러시
	{
		printf("파일 에러\n");
		exit(1);
	}
	init(&q); // q 초기화

	while(!feof(fp))
	{
		fscanf(fp,"%s",nameq); // addq,deleteq를 파일에서 받아옴
		if( strcmp(nameq,"addq") == 0) // addq일 경우
		{
			fscanf(fp,"%d",&num); // num값을 받아온다.
			enqueue(&q,num);      // 큐에 num삽입
			qcount++;             // 큐 데이터개수 1 증가
			printf("---Step %d : addq %d ---\n",step,num);
			display(&q,qcount);   // 출력함수 
			step++; // 스텝증가
		}
		else if( strcmp(nameq,"deleteq") == 0 ) // deleteq일 경우
		{
			dequeue(&q); // 큐 삭제
			qcount--; // 큐 데이터개수 1 감소
			printf("---Step %d : deleteq ---\n",step);
			display(&q,qcount); // 출력함수 
			step++; // 스텝증가
		}
	}

	fclose(fp); // 파일을 닫아준다
	return 0;
}
