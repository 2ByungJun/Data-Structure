///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 13일
// 프로그램명   : 포인터로 구현된 단순 연결리스트
//   설  명     : Data.txt파일에 저장된 정보를 링크드 리스트로 구현된
//                단순 연결 리스트에 저장하고 키보드로 값을 입력받아
//                리스트의 중앙에 삽입하고 그 결과를 출력하시오.
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
// 동적으로 노드를 생성
ListNode *create(element data,ListNode *link) 
{
	ListNode *new_node; // 노드 생성
	new_node = (ListNode *)malloc(sizeof(ListNode)); // 노드 동적할당
	if( new_node == NULL ) error("메모리 할당 에러"); // 에러시
	new_node->data = data; // data값으로 초기화
	new_node->link = link; // link값으로 초기화
	return(new_node); // new_node리턴
}
// 역순
ListNode *reverse(ListNode *head)
{
	// 순회 포인터
	ListNode *p,*q, *r; 
	p = head;           // head를 가리키는 p
	q = NULL;           // NULL을 가리키는 q
	while ( p != NULL){ // p리스트가 끝에 도달할 때까지
		r = q;          // r은 q를 가리킴
		q = p;          // q는 p를 가리킴
		p = p->link;    // p가 다음링크로 이동
		q->link = r;    // r이 q다음링크로 이동
	}
	return q; // q반환
}
// 출력
void display(ListNode **head,int count)
{
	ListNode *p=*head; // 포인터헤더를 가리키는 p
	int i;   // 반복문
	int num; // 입력받을 값
	int count1 = count; // count값은 count1값에 대입
	while(1){
		p = *head;
		// 형식에 맞춰 출력
		printf("< ");
		while( p != NULL) {
			printf("%d ",p->data);
			p = p->link;
		}
		printf(">\n");

		// 0입력시 종료
		printf("삽입 할 값을 입력하세요(0:종료) : ");
		scanf("%d",&num);
		if ( num == 0 )
			break;
		// 0이 아닐경우
		else{ 
			p = *head; // p는 포인터헤드값을 가리킴
			for ( i=0; i<(count1-1)/2; i++){ // (데이터개수-1)/2 크기만큼의 반복문
				p=p->link; // p가 다음링크로 이동
			}
			insert_node(head,p,create(num,NULL)); // w중간지점에 num값을 삽입
		}
		count1++; // count1값을 늘려준다
	}
}
int main()
{
	ListNode *list1=NULL; // list1선언
	int num;              // 데이터를 받아 저장할 변수
	int count=0;          // 파일데이터 개수
	FILE *fp = fopen("data1.txt","r"); // "data1.txt"파일을 읽기형식으로 오픈
	if(fp ==NULL) // 파일 에러시
	{
		printf("파일 에러\n");
		return 1;
	}

	while(!feof(fp)) // 파일포인터가 도달할때까지의 반복문
	{
		fscanf(fp,"%d",&num); // num값에 파일데이터값 입력
		insert_node(&list1,NULL,create(num,NULL)); // list1리스트에 num값을 삽입 
		count++; // 파일데이터 수 카운팅
	}
	list1 = reverse(list1); // list1을 리버스
	display(&list1,count);  // 리스트 출력

	fclose(fp); // 파일을 닫아준다
	return 0;
}