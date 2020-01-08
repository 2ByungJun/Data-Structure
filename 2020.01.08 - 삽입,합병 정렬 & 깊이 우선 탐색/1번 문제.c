///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 2일
// 프로그램명   : 삽입 정렬 프로그램(단순 연결리스트)
//   설  명     : data1.txt에 학생의 정보가 저장되어 있다. 이를 읽어와
//                평균을 구하고 총점순으로 내림차순으로 정렬하여 출력
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// element 구조체 정의
typedef struct {
	int num;   // 학번
	int kor;   // 국어
	int eng;   // 영어
	int math;  // 수학
	int total; // 총점
}element;

// 리스트 정의
typedef struct ListNode{
	element data;
	struct ListNode *link;
}ListNode;

// 오류 출력
void error(char *message)
{
	fprintf(stderr,"s\n",message);
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
// data : data값 설정
// link : link값 설정
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
// head : 정렬할 리스트
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

// 삽입 정렬
// head : 정렬할 리스트
ListNode *insertion_sort(ListNode *head)
{
	ListNode *p = head; // p가 헤드를 가리킴
	ListNode *temp;     // temp는 임시공간
	while(p->link != NULL ) { // p의 다음링크가 NULL경우
		if(p->data.total < p->link->data.total){ // total비교 (현재노드가 다음노드보다 작을경우 발생)
			temp = p->link; // temp가 p의 다음노드를 가리킴 | ㅁ(p) ㅁ(<-temp) ㅁ ㅁ |
			p->link = p->link->link; // p의 다음노드는 그 다음 노드를 가리킴 | ㅁ(p) ㅁ(temp)->ㅁ(p) ㅁ |
			temp->link = head; // temp에는 헤드값이 적용
			head = p = temp; // head를 다음노드로 가리킴
			continue;
		}
		p = p->link; // 다음링크로
	}
	return head;
}

// 출력
// head : 출력할 리스트
void display(ListNode *head)
{
	ListNode *p = head;
	printf("|========================================|\n");
	printf("|  학번  | 국어| 영어| 수학| 총 점| 평 균|\n");
	while( p != NULL ){
		printf("|%d| %3d | %3d | %3d | %3d  | %3.2lf|\n",p->data.num,p->data.kor,p->data.eng,p->data.math
			                                            ,p->data.total , (float)p->data.total/3);
		p = p->link;
	}
	printf("|========================================|\n");
}

int main()
{
	ListNode *list=NULL; // 리스트 생성
	element e;           // 구조체 생성

	// data1.txt 읽기
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}
	
	// 리스트에 e구조체 삽입(e:파일데이터 값을 적용)
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d %d",&e.num,&e.kor,&e.eng,&e.math); // 학번,국어,영어,수학
		e.total = e.kor+e.math+e.eng; // 총합
		insert_node(&list,NULL,create(e,NULL)); // 삽입함수
	}

	// 정렬 전
	printf("<정렬 전>\n");
	list = reverse(list); // 역순 정렬
	display(list); // 출력

	// 정렬 후
	printf("\n<정렬 후>\n");
	list = insertion_sort(list); // 삽입 정렬
	display(list); // 출력

	fclose(fp); // 파일을 닫아줍니다
	return 0;   // 종료
}