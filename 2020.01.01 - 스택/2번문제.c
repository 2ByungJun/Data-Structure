///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 15일
// 프로그램명   : 스택 1
//   설  명     : 스택에 1~20 까지의 숫자를 랜덤으로 저장하고 두 명이 한
//                장씩 뽑아 숫자게임을 5회 진행하여 승패를 출력하시오.
//                (한 장씩 봅아 숫자가 높은 사람이 승리한다.)
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STACK_SIZE 100 // 스택 사이즈 100 
typedef int element; // 자료형 element 정의
typedef struct { // 스택정의
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;
// 스택 초기화 함수
void init(StackType *s)
{
	s->top = -1;
}
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
	if( is_full(s)  ) { // 가득 차 있을 시 에러출력
		fprintf(stderr,"스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item; // 현재의 top부분보다 다음에 삽입( top은 삽입된 값이 된다 )
}
// 삭제 함수
element pop(StackType *s)
{
	if( is_empty(s) ) { // 스택이 비어있을 시 에러출력
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[s->top]; // top부분을 리턴
}

int main()
{
	StackType temp;  // 스택타입 temp선언
	int i=0,j=0,a=0; // 증가값 컨트롤 변수
	int num[20];     // 랜덤함수를 저장할 배열
	int win=0 , lose=0;  // 승,패 횟수
	int copy1=0,copy2=0; // 승,패 비교변수

	init(&temp); // temp 초기화

	// 중복안되는 랜덤함수
	srand((unsigned)time(NULL)); // 매 시간을 NULL로 초기화
	while(i<20)
	{
		num[i]=rand()%20+1; // num값에 1~20범위의 난수를 저장
		while(1) // 무한루프
		{
			for(j=0; j<i; j++) // num[i] 모든항을 비교
			{
				while(num[i]==num[j])  // 같을 경우 다른 난수 대입
					num[i]=rand()%20+1;
			}
			for(j=0; j<i; j++) // num[i] 모든항을 비교
			{
				if( num[i] != num[j]) // 다를 시 a값만 증가
					a++;
			}
			if( a==(i)) // a와 i가 같을 경우 꽉 찬경우이며 break;
				break;

			a=0; // a를 0으로 초기화
		}
		i++; // i값 증가
	}
	
	// temp.stack에 푸쉬
	for(i=0;i<20;i++){
		push(&temp,num[i]);
	}

	// 결과 출력
	j=0; // 0으로 초기화
	for(i=0; i<5; i++)   // 5번 실행
	{
		printf("< %d회차 >\n",i+1); // 회차 출력
		printf("A : %d - ", temp.stack[j] ); // A값 출력
		copy1 = temp.stack[j]; // 값을 copy1에 저장
		j++; 
		printf("B : %d\n", temp.stack[j] ); // B값 출력
		copy2 = temp.stack[j]; // 값을 copy2에 저장
		j++;
		// 승 패 정하기
		if( copy1 > copy2 )
			win++; 
		else
			lose++;
	}
	// 승 패 출력
	printf("\n< 승 패 >\n");
	printf("A - 승 : %d     패 : %d\n",win,lose); 
	printf("B - 승 : %d     패 : %d\n",5-win,5-lose); 

	return 0;
}