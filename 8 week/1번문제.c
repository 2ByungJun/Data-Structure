///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 2일
// 프로그램명   : 연결리스트 1
//   설  명     : 책 P.132의 프로그램 4.12를 작성하고 잘 돌아가는지 확인
//                하시오.
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
// 출력
void display(ListNode *head)
{
	ListNode *p=head;
	while( p != NULL) {
		printf("%d->",p->data);
		p = p->link;
	}
	printf("\n");
}
// 노드값 탐색
ListNode *search(ListNode *head,int x)
{
	ListNode *p;
	p = head;
	while( p != NULL ){
		if(p->data == x ) return p; // 탐색성공
		p = p->link;
	}
	return p; // 탐색에 실패한 경우 NULL 반환
}
// 연결 
ListNode *concat(ListNode *head1,ListNode *head2)
{
	ListNode *p;
	if( head1 == NULL ) return head2;       // head1이 NULL일 경우 head2 리턴
	else if ( head2 == NULL ) return head1; // head2이 NULL일 경우 head1 리턴
	else
	{
		p = head1;  // p노드에 head1노드를 대입
		while( p->link != NULL ) // p가 NULL일 경우까지 반복
			p = p->link;         // 다음 p를 가리킨다
		p->link = head2;         // p의 마지막 노드가 head2를 가리키도록 한다. 
		return head1;            // head1은 head2와 연결된 상태로 리턴
	}
}
// 역순
ListNode *reverse(ListNode *head)
{
	// 순회 포인터
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
// 동적으로 노드를 생성
ListNode *create(element data,ListNode *link) 
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// 테스트 프로그램
int main()
{
	ListNode *list1=NULL, *list2=NULL; // list1과 list2를 NULL로 초기화한 상태로 선언 
	ListNode *p;                       // p 리스트 생성

	// list1 = 30->20->10
	insert_node(&list1,NULL,create(10,NULL)); // list1에 있는 10을 NULL다음부분에 동적노드 생성
	insert_node(&list1,NULL,create(20,NULL)); // list1에 있는 20을 NULL다음부분에 동적노드 생성
	insert_node(&list1,NULL,create(30,NULL)); // list1에 있는 30을 NULL다음부분에 동적노드 생성
	display(list1);                           // list1 출력

	// list1 = 20->10
	remove_node(&list1,NULL,list1); // list1에서 NULL을 가리키는 노드값을 제거 
	display(list1);                 // list1 출력

	// list2 = 80->70->60
	insert_node(&list2,NULL,create(60,NULL)); // list2에 있는 60을 NULL다음부분에 동적노드 생성
	insert_node(&list2,NULL,create(70,NULL)); // list2에 있는 70을 NULL다음부분에 동적노드 생성
	insert_node(&list2,NULL,create(80,NULL)); // list2에 있는 80을 NULL다음부분에 동적노드 생성
	display(list2);                           // list2 출력

	// list1 = list1 + list2
	list1 = concat(list1 , list2); // list1에 list1과 list2를 연결하여 대입합니다.
	display(list1);                // list1+list2가 저장된 list1을 출력
	
	// list1을 역순으로
	list1 = reverse(list1);        // list1에 list1이 역순으로 표현된 리스트를 대입합니다.
	display(list1);                // list1 출력

	// list1에서 20탐색
	p = search(list1,20);          // list1에서 20을 탐색합니다.
	printf("탐색성공: %d\n", p->data);

	return 0;
}
