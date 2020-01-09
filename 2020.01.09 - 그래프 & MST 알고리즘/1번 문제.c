///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 11일
// 프로그램명   : 그래프 너비 우선 탐색 프로그램
//   설  명     : 책 p418에 있는 프로그램 10.5의 너비 우선 탐색 프로그램을
//                참고하여 파일에 입력되어있는 정점과 간선의 정보를 이용하여
//                그래프를 구성하고 깊이 너비 탐색을 하는 프로그램
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1    // 갔던 곳 TRUE표시 정의
#define FALSE 0   // FALSE로 초기화
#define MAX_VERTICES 50 

// GraphNode 구조체 정의
typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
} GraphNode;

// GraphType 구조체 정의
typedef struct GraphType{
	int n;
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

/* 큐 타입 정의 */
typedef int element;
typedef struct {    
	element queue[MAX_VERTICES]; 
	int front, rear;
} QueueType;

// 그래프 초기화
void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for(v=0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType *g,int v)
{
	if( ((g->n)+1) > MAX_VERTICES )
	{
		fprintf(stderr,"그래프 : 정점의 개수 초과" );
		return;
	}
	g->n++;
}

// 간선 삽입 연산, v를 u의 인접 리스트에 삽입한다.
void insert_edge(GraphType *g,int u,int v)
{
	GraphNode *node;
	if( u > g->n || v > g->n ) {
		fprintf(stderr,"그래프: 정점 번호 오류\n");
		return;
	}
	node = ( GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int visited[MAX_VERTICES]; 

/* 큐 */
// 큐 에러 함수
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 큐 초기화 함수
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// 큐가 비어있는지 확인하는 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// 큐가 차있는지 확인하는 함수
int is_full(QueueType *q)
{
	return (q->rear+1)%MAX_VERTICES == q->front;
}
// 큐 삽입 함수
void enqueue(QueueType *q,element item)
{
	if( is_full(q) )
		error("큐가 포화상태입니다\n");
	q->rear = (q->rear+1)%MAX_VERTICES;
	q->queue[q->rear] = item;
}
// 큐 삭제 함수
element dequeue(QueueType *q)
{
	if( is_empty(q) )
		error("큐가 공백상태입니다.");
	q->front = (q->front +1)%MAX_VERTICES;
	return q->queue[q->front];
}

// 너비 우선 탐색
void bfs_list(GraphType *g,int v)
{
	GraphNode *w;
	QueueType q;
	init(&q);          // 큐 초기화
	visited[v] = TRUE; // 정점 v 방문
	printf("%d ",v);
	enqueue(&q, v);
	while(!is_empty(&q))
	{
		v = dequeue(&q);
		for(w=g->adj_list[v]; w; w = w->link)
		{
			if(!visited[w->vertex])
			{
				visited[w->vertex] = TRUE;
				printf("%d ",w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}

int main()
{
	GraphType g;       // 그래프 선언
	char c;            // v와 e 구분
	int num_v;         // v데이터 값
	int num_e1,num_e2; // e데이터 값들

	// data1.txt 읽기
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 그래프 초기화
	graph_init(&g);

	// 파일 읽어와 그래프 형성
	while(!feof(fp))
	{
		fscanf(fp,"%c",&c); // v,e 구분
		if( c == 'v')
		{
			fscanf(fp,"%d",&num_v);
			insert_vertex(&g,num_v); // num_v값 정점 생성
		}
		else if( c == 'e') 
		{
			fscanf(fp,"%d %d",&num_e1,&num_e2);
			insert_edge(&g,num_e1,num_e2); // e1과 e2 간선 형성
			insert_edge(&g,num_e2,num_e1); // e2과 e1 간선 형성
		}
	}

	// 너비 우선 탐색
	printf("- 그래프 너비 우선 탐색 결과 -\n< ");
	bfs_list(&g,0);
	printf(">\n");

	fclose(fp); // 파일을 닫아준다
	return 0;   // 종료
}