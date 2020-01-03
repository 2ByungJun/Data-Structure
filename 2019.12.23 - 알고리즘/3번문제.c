///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 6월 5일
// 프로그램명   : 연결리스트를 이용한 덱 프로그램
//   설  명     : 연결리스트를 이용한 Deque 프로그램을 이용하여 data.txt
//                파일에 저장된 데이터를 입력 받아 Deque에 저장되는 과정
//                을 아래에 조건에 맞게 프로그래밍 하시오.
//                - add front 키워드 입력 시 앞쪽에 데이터 삽입
//                - add rear 키워드 입력 시 뒤쪽에 데이터 삽입
//                - delete front 키워드 입력 시 앞쪽에 데이터 삭제
//                - delete rear 키워드 입력 시 뒤쪽에 데이터 삭제
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// TRUE와 FALSE 정의
#define TRUE 1
#define FALSE 0
// 큐 노드
typedef int element;
typedef struct QueueNode{
	element data;
	struct DlistNode *llink; // 좌링크
	struct DlistNode *rlink; // 우링크
}DlistNode;
// 덱 타입
typedef struct DequeType {
	DlistNode *head; // 헤드
	DlistNode *tail; // 테일
} DequeType;

// 오류 출력 함수
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 초기화 함수
void init(DequeType *dq)
{
	dq->head=dq->tail=NULL;
}
// 공백 판단함수
int is_empty(DequeType *dq)
{
	if( dq->head == NULL )
		return TRUE;
	else return FALSE;
}
// 노드 생성 함수
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
	// DlistNode타입의 동적 생성
	DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
	if( node == NULL ) error("메모리 할당 오류");
	node->llink = llink; // 좌링크 대입
	node->data = item;   // data에 item값 대입
	node->rlink = rlink; // 우링크 대입
	return node; // 노드 리턴
}
// 뒤쪽 삽입 함수
void add_rear(DequeType *dq, element item)
{
	// DlistNode타입의 new_node생성( llink는 tail, rlink는 NULL )
	DlistNode *new_node = create_node(dq->tail,item,NULL);
	if( is_empty(dq)) // 공백일 경우
		dq->head = new_node; // head가 new_node
	else
		dq->tail->rlink = new_node; // tail->rlink가 new_node를 가리킴
	dq->tail = new_node; // tail을 이동
}
// 앞쪽 삽입 함수
void add_front(DequeType *dq, element item)
{
	// DlistNode타입의 new_node생성( llink는 NULL, rlink는 head )
	DlistNode *new_node = create_node(NULL,item,dq->head);

	if( is_empty(dq)) // 공백일 경우
		dq->tail = new_node; // tail이 new_node
	else
		dq->head->llink = new_node; // head->llink가 new_node를 가리킴
	dq->head = new_node; // head를 이동
}
// 앞쪽 삭제 함수
element delete_front(DequeType *dq)
{
	element item;
	DlistNode *removed_node; // removed_node생성
	 // 공백일 경우
	if( is_empty(dq)) error("공백 덱에서 삭제");
	else { // 아닌 경우
		removed_node = dq->head; // head를 가리킴
		item = removed_node->data;  // removed데이터 item에 대입 
		dq->head = dq->head->rlink; // head 이동
		free(removed_node);      // removed_node 삭제
		if( dq->head == NULL )   // head가 NULL일 경우
			dq->tail = NULL;     // tail도 NULL로 설정
		else
			dq->head->llink=NULL; // head->llink를 NULL로 대입
	}
	return item; // 값 리턴
}
// 뒤쪽 삭제 함수
element delete_rear(DequeType *dq)
{
	element item;
	DlistNode *removed_node; // removed_node생성
	 // 공백일 경우
	if( is_empty(dq)) error("공백 덱에서 삭제");
	else { // 아닌 경우
		removed_node = dq->tail; // tail에 가리킴
		item = removed_node->data;  // removed데이터 item에 대입 
		dq->tail = dq->tail->llink; // tail 이동
		free(removed_node);      // removed_node 삭제
		if( dq->tail == NULL )   // tail가 NULL일 경우
			dq->head = NULL;     // head도 NULL로 설정
		else
			dq->tail->rlink=NULL; // tail->llink를 NULL로 대입
	}
	return item; // 값 리턴
}
// 출력 함수
void display(DequeType *dq,int qcount)
{
	int i;
	DlistNode *temp = dq->head; // temp에 head를 위치
	// 큐 (상)괄호
	printf("┌─");
	for(i=0; i<qcount; i++)
		printf("──");
	printf("─┐\n");
    // 큐 데이터 출력
	for(i=0; i<qcount; i++){ // 큐 개수만큼 출력
		printf("  %d",temp->data );
		temp = temp->rlink; // 다음 노드로 이동
	}
	printf("\n");
	// 큐 (하)괄호
	printf("└─");
	for(i=0; i<qcount; i++)
		printf("──");
	printf("─┘\n");
}

int main()
{
	DequeType q; // 덱 생성
	char nameq1[30],nameq2[30];  // add,delete 판단/front,rear 판단
	int num; // 대입숫자
	int step=1,qcount=0; // 스텝, 큐 데이터 개수
	FILE *fp = fopen("data3.txt","r"); // data3.txt 읽기형식으로 오픈
	if( fp==NULL ) // 파일 에러시
	{
		printf("파일 에러\n");
		exit(1);
	}
	init(&q); // q 초기화

	while(!feof(fp))
	{
		fscanf(fp,"%s %s",nameq1,nameq2); // add,delete/front,rear를 파일에서 받아옴
		if( strcmp(nameq1,"add") == 0) // add일 경우
		{
			if( strcmp(nameq2,"front") == 0) // front일 경우
			{
				fscanf(fp,"%d",&num); // num값을 받아온다.
				add_front(&q,num);    // 앞쪽에 삽입
				qcount++;             // 큐 데이터개수 1 증가
				printf("---Step %d : add front %d ---\n",step,num);
				display(&q,qcount);   // 출력
				step++; // 스텝증가
			}
			else if( strcmp(nameq2,"rear") == 0) // rear일 경우
			{
				fscanf(fp,"%d",&num); // num값을 받아온다.
				add_rear(&q,num); // 뒤쪽에 삽입
				qcount++;             // 큐 데이터개수 1 증가
				printf("---Step %d : add rear %d ---\n",step,num);
				display(&q,qcount);   // 출력
				step++; // 스텝증가
			}
		}
		else if( strcmp(nameq1,"delete") == 0 ) // delete일 경우
		{
			if( strcmp(nameq2,"front") == 0) // front일 경우
			{
				delete_front(&q);     // 큐 삭제
				qcount--;             // 큐 데이터개수 1 감소
				printf("---Step %d : delete front ---\n",step);
				display(&q,qcount);   // 출력
				step++; // 스텝증가
			}
			else if( strcmp(nameq2,"rear") == 0) // rear일 경우
			{
				delete_rear(&q);      // 큐 삭제
				qcount--;             // 큐 데이터개수 1 감소
				printf("---Step %d : deleteq rear ---\n",step);
				display(&q,qcount);   // 출력
				step++; // 스텝증가
			}
		}
	}

	fclose(fp); // 파일을 닫아준다
	return 0;
}