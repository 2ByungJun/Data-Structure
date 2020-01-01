///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 31일
// 프로그램명   : 미로 탐색
//   설  명     : 책에 있는 미로 탐색 프로그램을 작성하고 이해하라.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAZE_SIZE 6

// 구조체
typedef struct{
	short r; // row
	short c; // cow
}element;
// 스택구조
typedef struct {
	element stack[MAX];
	int top;
}StackType;
element here={1,0}, entry={1,0};
// 미로 모양
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};
// 스택 초기화
void init(StackType *s)
{
	s->top = -1;
}
// 스택 비어있는지 확인
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// 스택 가득찼는지 확인
int is_full(StackType *s)
{
	return (s->top == (MAX-1));
}
// 스택 push
void push(StackType *s,element item)
{
	if(is_full(s))
	{
		fprintf(stderr,"스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 스택 pop
element pop(StackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else 
		return s->stack[(s->top)--];
}
// 스택 peek
element peek(StackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else 
		return s->stack[(s->top)];
}
// 위치를 스택에 삽입
void push_loc(StackType *s, int r, int c)
{
	if(r<0 || c<0) return;
	if(maze[r][c] != '1' && maze[r][c] != '.') /// 벽이아니고 방문되지 않았으면
	{
		element tmp; // tmp 구조체 선언
		tmp.r=r;     // tmp 행 대입
		tmp.c=c;     // tmp 열 대입
		push(s,tmp); // s스택에 tmp를 푸시
	}
}
// 미로 출력
void printMaze(char m[MAZE_SIZE][MAZE_SIZE])
{
	int r,c;
	printf("\n\n");
	for(r=0; r<MAZE_SIZE; r++)
	{
		for(c=0; c<MAZE_SIZE; c++)
		{
			if(c==here.c && r == here.r)
				printf("m ");
			else
			{
				if(m[r][c] == 0) printf("0 ");
				else printf("%c ",m[r][c]);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
// 스택 출력
void printStack(StackType *s)
{
   int i;
   for(i=5; i>s->top; i--)  // 스택모양 출력
      printf("|      |\n");
   for(i=s->top; i>=0; i--) // 스택에 값이 있을 시 출력
      printf("|<%01d,%01d> |\n",s->stack[i].r,s->stack[i].c);
   printf("--------\n");
}

int main()
{
	int r,c;     // 행,열
	StackType s; // s스택 선언

	init(&s); // 스택 초기화

	here = entry; 
	// 미로 'x'가 아닐경우 ( 도착점 x )
	while (maze[here.r][here.c] !='x')
	{
		r=here.r; 
		c=here.c;
		maze[r][c] = '.'; // 지나온 곳은 .대입
		push_loc(&s,r-1,c); // 왼쪽 푸시
		push_loc(&s,r+1,c); // 오른쪽 푸시
		push_loc(&s,r,c-1); // 위쪽 푸시
		push_loc(&s,r,c+1); // 아래쪽 푸시
		printMaze(maze);
		printStack(&s);

		if(is_empty(&s)) // 비어있는 경우
		{
			printf("실패\n\n");
			return;
		}
		else 
			here = pop(&s);
	}
	printMaze(maze);
	printStack(&s);
	printf("성공\n\n");

	return 0;
}