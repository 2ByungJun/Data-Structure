///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 9월 5일
// 프로그램명   : 파일에서 자료 읽어오기 1
//   설  명     : 파일에서 자료를 읽어와 링크드 리스트에 저장하는 파일을
//                작성하고 아래 조건을 만족하게 출력하는 프로그램을 작성하라.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y,t) ( (t) = (x), (x)=(y), (y)=(t)); // 스왑정의

typedef int element;
typedef struct ListNode {
	element data;           // 리스트 데이터 값
	struct ListNode *link;  // 리스트 링크(예:1번지,2번지...)
} ListNode;

// 오류출력
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}

// 삽입
// phead: 리스트의 헤드 포인트의 포인터
// p : 선행노드
// new_node : 삽입될 노드
void insert_node(ListNode **phead,ListNode *p,ListNode *new_node)
{
	if( *phead == NULL ){ // 공백 리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL ){ // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else { // p 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}

// 노드 동적생성
// data : 리스트 값
// link : 리스트 링크
ListNode *create_node(element data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// 오름차순
// list : 리스트
// n : 파일 데이터 값
void bubble_sort_up(ListNode *list,int n)
{
	ListNode *p=list; // 리스트p를 list로 헤더초기화
	int i,j,temp; // 반복변수,교환변수temp

	for( i=n-1; i>0; i--) { // i값을 값-1으로 초기화 후 감소
		p=list;             // p를 list헤더로 초기화
		for(j=0; j<i; j++)  // j값을 0으로 초기화 후 증가
		{
			if(p->data > p->link->data )            // 리스트p 데이터값과 다음 데이터값을 비교
				SWAP(p->data, p->link->data ,temp); // 스왑
			p = p->link;    // 다음 노드로 이동
		}
	}
}

// 내림차순
// list : 리스트
// n : 파일 데이터 값
void bubble_sort_down(ListNode *list,int n)
{
	ListNode *p=list; // 리스트p를 list로 헤더초기화
	int i,j,temp; // 반복변수,교환변수temp

	for( i=n-1; i>0; i--) {
		p=list;           
		for(j=0; j<i; j++) 
		{
			if(p->data < p->link->data )            // 오름차순과 다르게 다음데이터값보다 작을 경우
				SWAP(p->data, p->link->data ,temp); // 스왑
			p = p->link;
		}
	}
}

// 출력
void display(ListNode *head)
{
	ListNode *p=head;
	while( p != NULL ) {
		if( p->link == NULL) // 마지막 NULL값일 경우는 '->' 제외 출력
			printf("%d ",p->data);
		else
			printf("%d ->", p->data);
		p = p->link;
	}
	printf("\n");
}

int main()
{
	ListNode *list=NULL; // 리스트 생성
	int count=0;         // 파일 데이터 값 수
	int num;             // 파일 데이터를 받아올 변수

	FILE *fp = fopen("data1.txt","r"); // data1.txt를 읽기형식으로 오픈
	if( fp==NULL) // 파일 에러시
	{
		error("파일 읽기 실패\n");
		return 1;
	}

	while(!feof(fp)) // 파일포인터 위치가 끝에 닿을 때까지 반복
	{
		fscanf(fp,"%d", &num ); // 파일 데이터값을 num값에 입력
		insert_node(&list,NULL,create_node(num,NULL)); // num값을 NULL위치에 동적생성 후 삽입
		count++; // 카운팅
	}

	bubble_sort_up(list,count);  // 버블소트 up정렬(오름차순)
	printf("<오름차순 정렬>\n"); 
	display(list); // 리스트출력

	printf("\n");

	bubble_sort_down(list,count);  // 버블소트 down정렬(내림차순)
	printf("<내림차순 정렬>\n");
	display(list); // 리스트출력

	fclose(fp); // 파일을 닫아준다.
	return 0;
}