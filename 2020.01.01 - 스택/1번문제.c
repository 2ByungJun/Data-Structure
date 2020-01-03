///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 22일
// 프로그램명   : 연결리스트
//   설  명     : Data.txt에서 학번,이름,국어,영어,수학 정보를 가져와
//                링크드 리스트에 저장하고 총점,국어,영어,수학 최고점수를
//                받은 학생을 아래와 같이 출력하라.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// People구조체 정의
typedef struct {
	char name[10];	//이름
	int number;		//학번
	int korean;		//국어
	int eng;		//영어
	int math;		//수학
}People;

// 연결리스트 정의
typedef struct ListNode{
	People data;
	struct ListNode *link;
}ListNode;

// 에러함수
void error (char *message)
{
	fprintf(stderr,"&s\n",message);
	exit(1);
}
// 삽입함수
// phead: 리스트의 헤드 포인트의 포인터
// p : 선행노드
// new_node : 삽입될 노드
void insert_node(ListNode **phead, ListNode *p,ListNode *new_node)
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
// 역순함수
ListNode *reverse(ListNode *head)
{
	ListNode *p, *q, *r; // 순회 포인터
	p = head;
	q = NULL;
	while(p!=NULL)
	{
		r=q;
		q=p;
		p=p->link;
		q->link=r;
	}
	return q;
}
// 동적으로 노드를 생성
ListNode *create_node(People data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node==NULL) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// 학생정보 출력
void display(ListNode *head)
{
	int total=0;   // 총점
	double ever=0; // 평균
	ListNode *p=head; // p 생성 및 head로 초기화
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  학번  |  이름  |국어|영어|수학|총점| 평균 |\n");
	printf("|========|========|====|====|====|====|======|\n");
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math; // 총점값 대입
		ever=total/3.0; // 평균값 대입
		printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;    // 다음 노드로 이동
	}
	printf("|========|========|====|====|====|====|======|\n\n");

}
// 최고점수 출력
void display_MAX(ListNode *head)
{
	int total=0;   // 총점
	double ever=0; // 평균
	int max=0;     // 최고값을 찾아 저장할 변수
	ListNode *p=head;// p 생성 및 head로 초기화

	// 총점 최고점수   ( 밑의 함수들 중 중복된 경우는 주석처리를 생략하도록 하겠습니다.[가독성위함] )
	// total,ever,max 구하기
	while(p!=NULL)
	{	
		total=p->data.korean+p->data.eng+p->data.math; // 총점값 대입
		if(max<=total)  // total이 max보다 크거나 같을 시
			max= total; // max에 대입
		p = p->link;
	}
	p=head; // head초기화
	printf("< 총점 최고점수 >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  학번  |  이름  |국어|영어|수학|총점| 평균 |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// 출력
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==total)  // max와 최고점수가 같을 시 출력
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// 국어 최고점수
	p=head;// head초기화
	max=0; // max초기화
	while(p!=NULL)
	{	
		if(max<=p->data.korean) // 국어점수 최대값을 max에 대입
			max= p->data.korean;
		p = p->link;
	}
	p=head; // head초기화
	printf(" < 국어 최고점수 >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  학번  |  이름  |국어|영어|수학|총점| 평균 |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// 출력
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==p->data.korean)  // max와 국어점수가 같을 시 출력
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// 수학 최고점수
	p=head;
	max=0;
	while(p!=NULL)
	{	
		if(max<=p->data.math) // 수학점수 최대값을 max에 대입
			max= p->data.math;
		p = p->link;
	}
	p=head;
	printf(" < 수학 최고점수 >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  학번  |  이름  |국어|영어|수학|총점| 평균 |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// 출력
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==p->data.math)  // max와 수학점수가 같을 시 출력
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// 영어 최고점수
	p=head;
	max=0;
	while(p!=NULL)
	{	
		if(max<=p->data.eng) // 영어점수 최대값을 max에 대입
			max= p->data.eng;
		p = p->link;
	}
	p=head;
	printf(" < 영어 최고점수 >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  학번  |  이름  |국어|영어|수학|총점| 평균 |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// 출력
	while(p!=NULL)
	{
		if(max==p->data.eng)// max와 영어점수가 같을 시 출력
		{	
			total=p->data.korean+p->data.eng+p->data.math;
			ever=total/3.0;
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		}
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");
}

int main()
{
	ListNode *list1=NULL; // 리스트 생성
	People temp;    // temp 구조체 생성
	FILE *fp = fopen("data1.txt","r"); // 파일data1.txt 읽기형식으로 오픈
	if(fp==NULL) // 파일에러시 출력
	{
		printf("파일 열기 실패\n");
		exit(1);
	}

	// list1에 data삽입
	while(!feof(fp))
	{
		fscanf(fp,"%d %s %d %d %d",&temp.number,temp.name,&temp.korean,&temp.eng,&temp.math); // data구조체에 저장
		insert_node(&list1,NULL,create_node(temp,NULL)); // data구조체 list1에 삽입
	}
	list1=reverse(list1); // list1 역순

	display(list1);     // 학생 정보 출력
	display_MAX(list1); // 최고점수 출력

	fclose(fp); // 파일을 닫아준다.
	return 0;
}