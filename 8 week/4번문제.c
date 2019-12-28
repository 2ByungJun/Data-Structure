#include <stdio.h>
#include <stdlib.h>

#define SWAP(a,b) { element t; t=a; a=b; b=t; } // 버블정렬을 위한 SWAP함수 ( 자리를 바꿔준다 )

typedef struct {
	int studentNumber;
	int kor;
	int eng;
	int math;
} element;

typedef struct ListNode {
	element data;
	struct ListNode *link;
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

// 버블정렬
void sort(ListNode *head)
{
	ListNode *p = NULL; // p리스트를 생성 후 NULL로 초기화
	ListNode *q = NULL; // q리스트를 생성 후 NULL로 초기화
	element tmp;
	int sum_p;
	int sum_q;

	for(p=head; p!=NULL; p=p->link) // p를 head로 초기화 후 노드 끝까지 반복
	{
		sum_p = p->data.eng + p->data.kor + p->data.math;
		for(q=head; q!=NULL; q=q->link) // q를 head로 초기화 후 노드 끝까지 반복
		{
			sum_q = q->data.eng + q->data.kor + q->data.math;
			if( sum_p > sum_q )       // p의 data값이 q의 data값 보다 작을 경우
			{
				tmp = p->data;
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
	ListNode *p=head;
	int i;
	int sum;
	double average;
	while( p != NULL) {
		printf("학번        국어   영어   수학   총점   평균\n");
		for (p = head; p !=NULL; p=p->link)
		{
			sum = p->data.eng + p->data.kor + p->data.math;
			average = (double)sum/3;
			printf("%d%7d%7d%7d", p->data,p->data,p->data,p->data);
			for( i=0; i<1; i++)
				printf("%7d%8.2lf\n",sum ,average );
		}
		printf("\n");
	}
}


int main()
{
	ListNode *plist=NULL;   // 동적할당 받을 메인 구조체 배열 선언
	element tmp;
	int i=0,j=0;       // 반복증가값 변수
	
	FILE *fp = fopen("data4.txt","r");  // data4.txt파일을 읽기형식으로 오픈
	if( fp == NULL)                     // 파일에러시 출력문구
	{
		printf("파일이 열리지 않았습니다\n");
		return 1;
	}

	while(!feof(fp))  // 파일카운팅을 위해 파일을 끝까지 읽어줄 반복문
	{
		fscanf(fp,"%d %d %d %d", &tmp.studentNumber,&tmp.kor, &tmp.eng, &tmp.math );
	    insert_node(&plist,NULL,create(tmp,NULL));
	}
	printf("Before Sorting!!\n");
	plist = reverse(plist); // 역순
	display(plist);         // plist출력

	printf("After Sorting!!\n");
	sort(plist);
	display(plist);

	fclose(fp); // 파일을 닫아준다
	return 0;
}