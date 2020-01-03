///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 9월 5일
// 프로그램명   : 파일에서 자료 읽어오기 2
//   설  명     : data.txt에 학생,이름,수학/영어/국어 점수가 저장되어있고,
//                조건에 맞는 프로그램을 작성하라
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// student 구조체 생성
typedef struct {
	int studentNumber; // 학번
	char name[10];     // 이름
	int math;          // 수학
	int eng;           // 영어
	int kor;           // 국어
}student;

typedef struct ListNode {
	student data;
	struct ListNode *link;
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
ListNode *create_node(student data,ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// 버블정렬
void sort(ListNode *head)
{
	ListNode *p = NULL; // p리스트를 생성 후 NULL로 초기화
	ListNode *q = NULL; // q리스트를 생성 후 NULL로 초기화
	student tmp;
	double average_p; // 평균값p
	double average_q; // 평균값q

	for(p=head; p!=NULL; p=p->link) // p를 head로 초기화 후 노드 끝까지 반복
	{
		average_p = (p->data.eng + p->data.kor + p->data.math)/3; // p평균값
		for(q=head; q!=NULL; q=q->link) // q를 head로 초기화 후 노드 끝까지 반복
		{
			average_q = (q->data.eng + q->data.kor + q->data.math)/3; // q평균값
			if( average_p > average_q )       // p의 평균 값이 q의 평균 값 보다 작을 경우
			{
				tmp = p->data;     // tmp를 이용하여 p->data(구조체값)을 q->data값으로 교환시켜준다.
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
	for( ; p!=NULL; p=p->link)
	{
		head->data = p->data;
		head = head->link;
	}
}

// 출력
void display(ListNode *head)
{
	ListNode *p=head; // p를 head헤더로 초기화
	int i;            // 반복변수
	int sum=0;        // 총점
	double average=0; // 평균

	printf("|========================================================|\n");
	printf("|  학  번  |  이 름 | 수학 | 영어 | 국어 | 총 점 | 평 균 |\n");
	printf("|========================================================|\n");

	for (p = head; p !=NULL; p=p->link) // p를 head로 초기화하며 NULL까지 반복
	{
		sum = p->data.eng + p->data.kor + p->data.math; // 총점계산
		average = (double)sum/3; // 평균계산
		// 학번,이름,수학,영어,국어 출력
		printf("| %d | %s | %3d  | %3d  | %3d  |", p->data.studentNumber, p->data.name ,p->data.math , p->data.eng ,p->data.kor );
		for( i=0; i<1; i++) // 총점,평균 출력
			printf(" %4d  | %3.2lf |\n", sum ,average );
	}
	printf("|========================================================|\n");
}

int main()
{
	ListNode *plist=NULL;   // 동적할당 받을 메인 구조체 배열 선언
	student tmp;

	FILE *fp = fopen("data2.txt","r");  // data4.txt파일을 읽기형식으로 오픈
	if( fp == NULL)                     // 파일에러시 출력문구
	{
		printf("파일이 열리지 않았습니다\n");
		return 1;
	}

	while(!feof(fp))  // 파일카운팅을 위해 파일을 끝까지 읽어줄 반복문
	{
		// 학번,이름,수학,영어,국어 값들을 tmp구조체에 대입
		fscanf(fp,"%d %s %d %d %d", &tmp.studentNumber, &tmp.name ,&tmp.math, &tmp.eng, &tmp.kor); 
	    insert_node(&plist,NULL,create_node(tmp,NULL)); // tmp구조체 동적생성 후 리스트 삽입
	}

	sort(plist);    // 총점순으로 정렬
	display(plist); // 리스트 출력

	fclose(fp); // 파일을 닫아준다
	return 0;
}