///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 22일
// 프로그램명   : 스택 2
//   설  명     : Data.txt에서 데이터를 가져와 이름,전화번호, 성멸을 가진
//                구조체에 저장하라. 이후 두 개의 스택에 각각 남자와 여자
//                를 넣고 각 스택에서 하나씩 뽑아 짝을 지어 아래와 같이
//                출력하라.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 사이즈
#define MAX_STACK_SIZE 100
// 구조체 element 정의
typedef struct element{
	char name[20];  // 이름
	char phone[20]; // 폰번호
	char sex[20];   // 성별
}element;
// 스택 정의
typedef struct {
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

// 공백 상태 검출 함수
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType *s)
{
	return (s->top == (MAX_STACK_SIZE-1));
}
// 삽입 함수
void push(StackType *s,element item)
{
	if( is_full(s)  ) { // 포화일 경우
		fprintf(stderr,"스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제 함수
element pop(StackType *s)
{
	if( is_empty(s) ) { // 공백일 경우
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top--]; // top--감소
}

int main()
{
	StackType man,girl; // 스택 man,girl 생성
	element A,man_str,girl_str; // 구조체 생성
	int i=1; // <%d호> 표현변수
	int count_man=0,count_girl=0; // 남,여 파일데이터 개수

	// data3.txt 파일을 읽기형식으로 오픈
	FILE *fp = fopen("data3.txt","r");
	if(fp==NULL){ // 파일 에러시
		printf("파일 에러\n");
		return 1;
	}

	// 푸시
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s", A.name , A.phone , A.sex );
		if ( strcmp( A.sex , "남") == 0 ){ // 남자일 경우
			push(&man,A); // man에 푸시
			printf("<Push> 남자 - %s\n", A.name );
			count_man++;  // man카운팅 
		}
		else if ( strcmp( A.sex , "여" ) == 0 ){ // 여자일 경우
			push(&girl,A); // girl에 푸시
			printf("<Push> 여자 - %s\n", A.name );
			count_girl++;  // girl카운팅
		}
	}
	printf("\n");

	// 팝
	while(1)
	{
		man_str = pop(&man);   // man_str구조체에 pop(&man)값 대입
		girl_str = pop(&girl); // girl_str구조체에 pop(&girl)값 대입

		if( count_man != 0 && count_girl != 0 ) // 남,여 데이터 수가 둘 다 0이 아닐경우
		{
			printf("<%d호> ",i);
			printf(" %s(%s) -", man_str.name , man_str.phone );
			printf(" %s(%s)\n", girl_str.name , girl_str.phone );
		}
		else if ( count_girl == 0 && count_man>0 ) // 더이상 여자 데이터 수가 없을 경우
		{
			printf("%s씨는 짝이 없습니다...\n",man_str.name); // 남은 남자이름 출력
			break;
		}
		else if ( count_man == 0 && count_girl>0 ) // 더이상 남자 데이터 수가 없을 경우
		{
			printf("%s씨는 짝이 없습니다...\n",girl_str.name); // 남은 여자이름 출력
			break;
		}
		else if ( count_man <= 0 && count_girl <= 0 ) // 두 데이터 수가 없을 경우
			break;
		count_man--;  // count_man감소
		count_girl--; // count_girl감소
		i++;          // i증가
	}

	fclose(fp); // 파일을 닫아준다
	return 0;
}