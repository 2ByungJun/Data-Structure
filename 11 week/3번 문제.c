///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 31��
// ���α׷���   : �̷� Ž��
//   ��  ��     : å�� �ִ� �̷� Ž�� ���α׷��� �ۼ��ϰ� �����϶�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAZE_SIZE 6

// ����ü
typedef struct{
	short r; // row
	short c; // cow
}element;
// ���ñ���
typedef struct {
	element stack[MAX];
	int top;
}StackType;
element here={1,0}, entry={1,0};
// �̷� ���
char maze[MAZE_SIZE][MAZE_SIZE] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'}
};
// ���� �ʱ�ȭ
void init(StackType *s)
{
	s->top = -1;
}
// ���� ����ִ��� Ȯ��
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// ���� ����á���� Ȯ��
int is_full(StackType *s)
{
	return (s->top == (MAX-1));
}
// ���� push
void push(StackType *s,element item)
{
	if(is_full(s))
	{
		fprintf(stderr,"���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// ���� pop
element pop(StackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else 
		return s->stack[(s->top)--];
}
// ���� peek
element peek(StackType *s)
{
	if(is_empty(s))
	{
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else 
		return s->stack[(s->top)];
}
// ��ġ�� ���ÿ� ����
void push_loc(StackType *s, int r, int c)
{
	if(r<0 || c<0) return;
	if(maze[r][c] != '1' && maze[r][c] != '.') /// ���̾ƴϰ� �湮���� �ʾ�����
	{
		element tmp; // tmp ����ü ����
		tmp.r=r;     // tmp �� ����
		tmp.c=c;     // tmp �� ����
		push(s,tmp); // s���ÿ� tmp�� Ǫ��
	}
}
// �̷� ���
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
// ���� ���
void printStack(StackType *s)
{
   int i;
   for(i=5; i>s->top; i--)  // ���ø�� ���
      printf("|      |\n");
   for(i=s->top; i>=0; i--) // ���ÿ� ���� ���� �� ���
      printf("|<%01d,%01d> |\n",s->stack[i].r,s->stack[i].c);
   printf("--------\n");
}

int main()
{
	int r,c;     // ��,��
	StackType s; // s���� ����

	init(&s); // ���� �ʱ�ȭ

	here = entry; 
	// �̷� 'x'�� �ƴҰ�� ( ������ x )
	while (maze[here.r][here.c] !='x')
	{
		r=here.r; 
		c=here.c;
		maze[r][c] = '.'; // ������ ���� .����
		push_loc(&s,r-1,c); // ���� Ǫ��
		push_loc(&s,r+1,c); // ������ Ǫ��
		push_loc(&s,r,c-1); // ���� Ǫ��
		push_loc(&s,r,c+1); // �Ʒ��� Ǫ��
		printMaze(maze);
		printStack(&s);

		if(is_empty(&s)) // ����ִ� ���
		{
			printf("����\n\n");
			return;
		}
		else 
			here = pop(&s);
	}
	printMaze(maze);
	printStack(&s);
	printf("����\n\n");

	return 0;
}