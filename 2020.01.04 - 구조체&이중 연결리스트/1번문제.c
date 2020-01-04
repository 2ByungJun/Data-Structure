#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;
typedef struct DlistNode {
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

void init(DlistNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 노드 생성
DlistNode *create( element data )
{
	DlistNode *new_node; // Dnode타입 new_node 생성
	new_node = (DlistNode *)malloc( sizeof(DlistNode) ); // new_node 동적할당
	new_node->data = data;  // data초기화
	new_node->llink = NULL; // L링크 NULL 가리킴
	new_node->rlink = NULL; // R링크 NULL 가리킴
	return new_node; // new_node리턴
}

// 삽입
void dremove_node(DlistNode *before, DlistNode *new_node)
{
	new_node->rlink = before;
	new_node->llink = before->llink;
	before->llink->rlink = new_node;
	before->llink = new_node;
}

// 출력
void display(DlistNode *phead)
{
	DlistNode *p;
	int i=1;
	printf("< ");
	for( p=phead->rlink; p != phead; p = p->rlink)
	{
		printf("%c ",p->data);
	}
	printf(">\n");
}

// 선택정렬
void select_sort(DlistNode *head_node)
{
	DlistNode *p, *min_node, *A , *B , *temp1, *temp2;
	//      헤더 , 최소값노드, 비교A,B ,  (헤드,테일)위치노드

	int count = 1;
	for( p=head_node; p->rlink!=head_node; p=p->rlink)
	{
		A=p->rlink;
		B=A->rlink;
		min_node = A;
		for(; B!=head_node; B=B->rlink )
		{
			
			if( min_node->data > B->data )
			{
				min_node = B;
			}
		}
		B = min_node;
		if(A != B)
		{
			if( A->rlink == B )
			{
				A->llink->rlink = A->rlink;
				A->rlink = B->rlink;
				B->rlink->llink = A;
				B->llink = A->llink;
				B->rlink = A;
				A->llink = B;
			}
			else
			{
				A->rlink->llink = B;
				B->llink->rlink = A;
				A->llink->rlink = B;
				B->rlink->llink = A;
				temp1 = A->llink;
				temp2 = B->rlink;
				A->llink = B->llink;
				B->rlink = A->rlink;
				A->rlink = temp2;
				B->llink = temp1;
			}
		}
		printf("%d ",count++);
		display(head_node);
	}
}

int main()
{
	DlistNode head_node;
	char alpa;
	int count=0;

	FILE *fp = fopen("data1.txt","r");
	if( fp==NULL )
	{
		printf("파일이 열리지 않았습니다.\n");
		return 1;
	}
	init(&head_node);

	while(!feof(fp))
	{
		fscanf(fp," %c ",&alpa);
		dremove_node(&head_node,create(alpa));
		count++;
	}
	display(&head_node);
	select_sort(&head_node);

	fclose(fp);
	return 0;
}