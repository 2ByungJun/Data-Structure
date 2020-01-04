///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 9월 13일
// 프로그램명   : 파일에서 자료 읽어오기
//   설  명     : 파일에서 이름,과목명,과목 점수가 제대로 정리되어있지
//                않은 상태로 저장되어 있다. 이 정보를 이용하여 조건에
//                맞게 프로그램을 작성하라.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student 구조체
typedef struct Student{
	char name[10]; // 이름
	int math;      // 수학
	int eng;       // 영어
	int kor;	   // 국어
}Student;

// 리스트 생성
typedef struct ListNode{
	Student data;
	struct ListNode *link;
} ListNode;

// 오류 출력
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}

// 삽입 함수
// phead: 리스트의 헤드 포인트의 포인터
// p : 선행노드
// new_node : 삽입될 노드
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if(*phead == NULL){
		new_node->link =NULL;
		*phead = new_node;
	}
	else if(p == NULL){
		new_node->link = *phead;
		*phead = new_node;
	}
	else{
		new_node->link = p->link;
		p->link = new_node;
	}
}

// 동적 노드 생성
ListNode *create_node(Student data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL)
		error("메모리 할당 오류");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// 탐색 함수
// head : 리스트
// file_name : 파일에서의 이름값
ListNode *search(ListNode *head,char file_name[] )
{
	ListNode *p=head;
	while(p !=NULL)
	{
		if(strcmp(p->data.name,file_name) == 0) // 데이터이름과 파일데이터 이름이 같을 경우
			return p;
		p= p->link; // 다음노드를 가리킴
	}
	return p;
}

// 출력 함수
// head : 받아 올 리스트
void display(ListNode *head)
{
	ListNode *p=head;
	while(p != NULL)
	{
		printf("< %s 학생의 점수 >\n",p->data.name); // 학생 이름 출력
		printf("- 국어 : %5d점\n- 수학 : %5d점\n- 영어 : %5d점\n- 평균 : %.2f점\n\n", 
			                              p->data.kor,p->data.math,p->data.eng,(double)(p->data.kor+p->data.math+p->data.eng)/3);
		                                  // 국어,수학,영어,평균 출력
		p=p->link; // 다음 노드를 가리킴
	}
	printf("\n");
}

int main()
{

	ListNode *list=NULL;  // 리스트 생성
	ListNode *p;          // 이름값을 탐색시켜 저장할 
	Student tmp;          // 구조체 tmp생성 ( 이름,과목,점수 )
	char file_subject[10];
	FILE *fp =NULL;

	fp = fopen("data2.txt","r"); // data2.txt파일을 읽기형식으로 오픈
	if(fp==NULL) // 파일 읽기 에러시
	{
		error("파일 읽기 실패\n");
		exit(1);
	}
	// 점수 초기화( 빈 점수칸에 0점을 넣어주기 위함 )
	tmp.eng = 0;
	tmp.kor = 0;
	tmp.math = 0;

	while(!feof(fp))
	{
		fscanf(fp,"%s",&tmp.name); // 파일 이름값을 가져옴
		if(search(list,tmp.name) != NULL) // 리스트에서 이름이 있는지 전체 탐색하여 없을 경우
		{
			p = search(list,tmp.name);  // p에 tmp.name이름값을 가진 노드를 탐색하여 저장
			fscanf(fp,"%s",&file_subject); // 파일 과목이름을 가져옴

			if(strcmp(file_subject,"수학") == 0) // 수학일경우 수학에 점수 업데이트
				fscanf(fp,"%d",&p->data.math);
			if(strcmp(file_subject,"국어") == 0) // 국어일경우 국어에 점수 업데이트
				fscanf(fp,"%d",&p->data.kor);
			if(strcmp(file_subject,"영어") == 0) // 영어일경우 영어에 점수 업데이트
				fscanf(fp,"%d",&p->data.eng);
		}			
		else // 이름이 있을 경우
		{
			fscanf(fp,"%s",&file_subject); // 파일에서 과목을 읽음

			if(strcmp(file_subject,"수학") == 0) // 수학일경우 수학에 점수 업데이트
				fscanf(fp,"%d",&tmp.math);
			if(strcmp(file_subject,"국어") == 0) // 국어일경우 국어에 점수 업데이트
				fscanf(fp,"%d",&tmp.kor);
			if(strcmp(file_subject,"영어") == 0) // 영어일경우 영어에 점수 업데이트
				fscanf(fp,"%d",&tmp.eng);

			insert_node(&list,NULL,create_node(tmp,NULL)); // tmp삽입
		}
	}
	display(list); // list출력

	fclose(fp); // 파일을 닫아준다
	return 0;	
}
