///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 31일
// 프로그램명   : 스택 push pop 형식출력 프로그램
//   설  명     : 연결리스트를 이용한 스택 프로그램을 이용하여 data.txt
//                파일에 저장된 데이터를 입력 받아 2개의 스택에 저장되
//                는 기준을 아래에 조건에 맞게 프로그래밍 하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

// int형으로 element 정의
typedef int element; 
// 스택 연결리스트 구조체
typedef struct StackNode{ 
	element item;
	struct StackNode *link;
}StackNode;
// 스택 상단 top
typedef struct{
	StackNode *top;
} LinkedStackType;
// 스택 데이터 개수카운팅 변수
static int stack1_count=0,stack2_count=0;
// 스택 초기화 
void init(LinkedStackType *s)		
{
	s->top = NULL;
}
// 스택이 비어있을시
int is_empty(LinkedStackType *s)	
{
	return (s->top == NULL);
}
// Push함수
// *s : 연결리스트 스택
// item : 데이터 값
void push(LinkedStackType *s,element item)	
{
	StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp ==NULL)
	{
		fprintf(stderr,"메모리 할당에러\n");
		return;
	}
	else
	{
		temp->item =item;
		temp->link = s->top;
		s->top = temp;
	}
}
// Pop함수
// s : 연결리스트 스택
element pop(LinkedStackType *s)				
{
	if(is_empty(s))
	{
		fprintf(stderr,"스택이 비어있음\n");
		return;
	}
	else
	{
		StackNode *temp=s->top;
		element item = temp->item;
		s->top = s->top->link;
		free(temp);
		return item;
	}
}
// Peek함수
// s : 연결리스트 스택
element peek(LinkedStackType *s)			
{
	if(is_empty(s))
	{
		fprintf(stderr,"스택이 비어있음\n");
		exit(1);
	}
	else
	{
		return s->top->item;
	}
}
// 스택 출력 함수
// head1 : 스택1
// head2 : 스택2
// count1 : 스택1의 데이터 수
// count2 : 스택2의 데이터 수
void display(LinkedStackType *head1,LinkedStackType *head2,int stack1_count, int stack2_count)
{
	int i=0;
	StackNode *temp1 = head1->top;
	StackNode *temp2 =	head2->top;

	// 스택1의 데이터 개수가 더많을경우
	if(stack1_count > stack2_count)				
	{
		for(i=0; i<stack1_count-stack2_count; i++)
		{
			printf("│ <%2d>│  │     │  \n",temp1->item);
			temp1=temp1->link; // 스택1의 다음노드로
		}
	}
	// 스택2의 데이터 개수가 더많을경우
	if(stack1_count < stack2_count)				
	{
		for(i=0; i<stack2_count-stack1_count; i++)
		{
			printf("│     │  │ <%2d>│  \n",temp2->item);
			temp2=temp2->link; // 스택2의 다음노드로
		}
	}
	// 나머지 부분 출력
	while ( temp1 != NULL && temp2 !=NULL)
	{
		printf("│ <%2d>│  ",temp1->item); printf("│ <%2d>│\n",temp2->item);
		temp1=temp1->link; // 스택1의 다음노드로
		temp2=temp2->link; // 스택2의 다음노드로
	}
	printf("└─────┘  └─────┘\n");
}


void main()
{
	LinkedStackType s1,s2;		// 스택 생성
	char stack_pp[10]={0};      // 스택push,pop 판별
	int stack_number=0,data=0;  // 스택번호,데이터값
	int i=0;                    // 스탭Step

	// data2.txt파일을 읽기형식으로 오픈
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL) // 파일 에러
	{
		fprintf(stderr,"파일 에러\n");
		exit(1);
	}
	// 스택 초기화
	init(&s1);						
	init(&s2);						
	// 파일 포인터가 끝까지 도달할때까지 반복
	while(!feof(fp))
	{
		fscanf(fp,"%s",&stack_pp); // stack_pp로 push,pop를 읽어온다.

		// push일 경우
		if(strcmp(stack_pp,"push") == 0)
		{
			fscanf(fp,"%d %d",&stack_number,&data);
			// 1스택일 경우
			if(stack_number == 1)
			{
				push(&s1,data); // data를 스택1에 푸시
				printf("---Step %d : 스택 1 %d 입력---\n",i+1,data);

				stack1_count++; // 스택1에 카운트+1
				display(&s1,&s2,stack1_count,stack2_count);
				printf("\n");	
			}
			// 2스택일 경우
			else if(stack_number==2)
			{
				push(&s2,data); // data를 스택2에 푸시
				printf("---Step %d : 스택 2 %d 입력---\n",i+1,data);

				stack2_count++; // 스택2에 카운트+1
				display(&s1,&s2,stack1_count,stack2_count);
				printf("\n");				
			}
		}
		// pop일 경우
		else if(strcmp(stack_pp,"pop") == 0)
		{
			fscanf(fp,"%d",&stack_number);
			// 1스택일 경우
			if(stack_number==1)
			{
				printf("---Step %d : 스택 1 %d 삭제---\n",i+1,peek(&s1));
				pop(&s1); // 스택1 pop

				stack1_count--; // 스택1에 카운트-1
				display(&s1,&s2,stack1_count,stack2_count);			
				printf("\n");	
			}
			// 2스택일 경우
			else if(stack_number==2)
			{
				printf("---Step %d : 스택 2 %d 삭제---\n",i+1,peek(&s2));
				pop(&s2); // 스택2 pop

				stack2_count--; // 스택2에 카운트-1
				display(&s1,&s2,stack1_count,stack2_count);		
				printf("\n");	
			}	
		}
		i++;
	}
	
	fclose(fp); // 파일을 닫아준다
	return;
}