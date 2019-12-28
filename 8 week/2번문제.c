///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 2일
// 프로그램명   : 연결리스트 2
//   설  명     : 생성할 노드의 개수를 사용자에게 입력 받아 1~100까지의
//                난수를 데이터로 가진 노드를 생성한다.
//                생성한 노드를 가진 링크드 리스트를 구현하고 이 리스트를
//                정렬하여 출력하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> // 노드의 동적할당
#include <time.h>   // srand와 rand의 사용

#define SWAP(a,b) { element t; t=a; a=b; b=t; } // 버블정렬을 위한 SWAP함수 ( 자리를 바꿔준다 )

typedef int element;       // element를 int 자료형으로 정의
typedef struct ListNode {  // ListNode구조체 정의
	element data;          // int형 data
	struct ListNode *link; // ListNode link 포인터
}ListNode;

// 오류 출력
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// phead: 리스트의 헤드 포인트의 포인터
// p : 선행노드
// new_node : 삽입될 노드
void insert_node(ListNode **phead,ListNode *p, ListNode *new_node)
{
	if( *phead == NULL ){  // 공백 리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL ) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {  // p 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}
// 리스트 동적할당
ListNode *create(element data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// 리스트 출력
void display(ListNode *head)
{
	ListNode *p=head;

	while( p != NULL) {
		printf("< %d >",p->data); // 출력형식에 맞게 printf문 작성
		p = p->link;
	}
	printf("\n");
}
// 리스트 버블정렬
void line(ListNode *head)
{
	ListNode *p = NULL; // p리스트를 생성 후 NULL로 초기화
	ListNode *q = NULL; // q리스트를 생성 후 NULL로 초기화

	for(p=head; p!=NULL; p=p->link) // p를 head로 초기화 후 노드 끝까지 반복
	{

		for(q=head; q!=NULL; q=q->link) // q를 head로 초기화 후 노드 끝까지 반복
		{
			if(p->data < q->data)       // p의 data값이 q의 data값 보다 작을 경우
			{
				SWAP( p->data , q->data ) // p데이터값과 q데이터값을 바꿔준다.
			}
		}
	}
}

int main()
{
	ListNode *temp=NULL; // 리스트 temp생성 후 NULL값 초기화
	int num;             // 노드의 개수를 입력받을 변수
	int i;               // 반복문 증가값 변수

	printf("생성할 노드의 갯수를 입력하세요 : ");
	scanf("%d",&num);
	printf("\n");

	srand(time(NULL));    // time을 NULL로 두어 매번 다른 랜덤값 출력
	for( i=0; i<num; i++) // 노드의 개수만큼 반복문
	insert_node(&temp,NULL,create(rand()%100,NULL)); // 1부터 100까지의 난수를 temp 리스트에 저장
	printf("< 생성된 리스트 >\n");
	display(temp); // temp리스트 출력
	printf("\n");

	printf("< 정렬된 리스트 >\n");
	line(temp);    // 버블정렬
	display(temp); // temp리스트 출력
	return 0;
}