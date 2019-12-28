///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 2일
// 프로그램명   : 연결리스트 3
//   설  명     : 링크드 리스트로 구성된 내에서 인덱스상 홀수번째 위치만
//                삭제하는 함수를 구현하여 출력 하시오.
//                - 홀수번째 위치의 데이터를 삭제하는 함수 구현
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int element;       // element를 int 자료형으로 정의
typedef struct ListNode {  // ListNode구조체 정의
	element data;          // int형 data
	struct ListNode *link; // ListNode link 포인터
} ListNode;
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
// phead: 헤드 포인트의 대한 포인터
// p : 삭제될 노드의 선행노드
// removed : 삭제될 노드
void remove_node(ListNode **phead,ListNode *p, ListNode *removed)
{
	if ( p == NULL )  // p가 NULL일 경우
		*phead = ( *phead)->link; // (*phead)의 노드가 가리키는 값을 (*phead)가 가리킨다
	else              // p가 NULL이 아닐 경우
		p->link = removed->link;  // 삭제될 노드가 가리키는 값을 p 노드가 가리킨다
	free(removed); // removed 삭제
}
// 역순
ListNode *reverse(ListNode *head)
{
	ListNode *p,*q, *r;
	p = head;
	q = NULL;
	while ( p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}
// 리스트 출력
void display(ListNode *head)
{
	ListNode *p=head;

	while( p != NULL) {
		if( p->link == NULL){ // p가 NULL을 가르킨다면
			printf("%d ",p->data); // ->를 제외한 p값만 출력한다
			break;
		}
		printf("%d -> ",p->data);
		p = p->link;
	}
	printf("\n");
}
// 홀수 번째 위치 데이터 삭제 함수
void num_removed( ListNode **phead )
{
	ListNode *ph, *prev = NULL; // ph와 prev리스트 생성
	int count = 0; // 홀수 위치를 판별할 변수
	ph = *phead;   // ph리스트를 *phead값으로 초기화

	while( ph != NULL) 
	{
		if ( count % 2 == 1 ) // 홀수일 경우
		{
			remove_node(phead,prev,ph); // 노드 삭제 진행

			if ( prev != NULL)   // 선행 노드가 존재하는 경우
				ph = prev->link; // ph를 prev가 가리키는 곳을 가리키게 한다.
			else                 // 선행 노드가 존재하지 않을 경우
				ph = *phead;     // ph를 현재의 *phead를 대입
		}
		else // 데이터 값을 찾지 않은 경우, 다음 노드로 이동
		{
			prev = ph;     // prev에 ph값 대입
			ph = ph->link; // 다음 노드로 이동
		}
		count++;
	}
}
int main()
{
	ListNode *plist=NULL; // plist 연결리스트 선언
	int count=0;          // 파일 데이터 개수를 구할 변수
	int num;              // count를 구하기 위한 파일을 읽어줄 변수
	int i;                // 반복 증가값 변수

	FILE *fp = fopen("data3.txt","r"); // data3.txt를 읽기상태로 오픈
	if( fp == NULL)                    // 파일오류시 에러문구 출력
	{
		printf("파일이 열리지 않았습니다\n");
		return 0;
	}
	
	while(!feof(fp)) // count값을 구하기 위해 파일을 읽어주는 반복문
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	rewind(fp); // 파일 포인터위치 초기화
	for(i=0; i<count; i++) // count크기의 반복문
	{
		fscanf(fp,"%d",&num);  // 파일 데이터값을 num값에 대입
		insert_node(&plist,NULL,create(num,NULL)); // num값을 plist리스트의 삽입
	}
	plist = reverse(plist); // 역순함수를 이용하여 plist에 대입
	display(plist);      // plist출력
	
	num_removed(&plist); // plist리스트의 홀수번째 삭제
	display(plist);      // 홀수번째 삭제된 plist출력
	
	fclose(fp);          // 파일을 닫아준다
	return 0;
}