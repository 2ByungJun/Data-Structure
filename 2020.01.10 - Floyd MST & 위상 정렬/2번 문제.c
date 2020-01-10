///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 20일
// 프로그램명   : 위상 정렬
//   설  명     : p457의 프로그램을 참고하여 data.txt에 저장된 정점과
//                인접 리스트의 데이터에 위상 정렬 알고리즘을 사용하여
//                데이터에 대한 위상 순서를 출력하라.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50

// element 정의
typedef struct {
	int num;
	char name[20];
}element;

// 전역 변수
element *temp; // 정점과 이름을 가진 temp 배열
int count=0;   // 파일 데이터 개수

// GraphNode 정의
typedef struct GraphNode{
	int vertex;
	struct GraphNode *link;
} GraphNode;

// GraphType 정의
typedef struct GraphType{
	int n;
	char name[20];
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

// 스택 정의
typedef struct {
	element stack[MAX_VERTICES];
	int top;
}StackType;

// 그래프 초기화
void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for( v=0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// 정점 삽입연산
int insert_vertex(GraphType *g,int v)
{
	if( ((g->n)+1) > MAX_VERTICES ) {
		fprintf(stderr,"그래프:정점의 개수 초과");
		return 0;
	}
	g->n++;
}

// 간선 삽입연산
void insert_edge(GraphType *g,int u,int v)
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ) {
		fprintf(stderr,"그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

/* 스택 함수 */
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
	return (s->top == (MAX_VERTICES-1));
}
// 삽입 함수
void push(StackType *s,element item)
{
	if( is_full(s) ) {
		fprintf(stderr,"스택 포화 에러\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// 삭제 함수
element pop(StackType *s)
{
	if( is_empty(s) ) {
		fprintf(stderr,"스택 공백 에러\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

// 위상 정렬
void topo_sort(GraphType *g)
{
	int i,j;        // 반복 변수
	StackType s;    // 스택 선언
	GraphNode *node;// GraphNode 생성
	int *in_degree; // push에 이용할 정점 임시 배열

	// in_degree 동적할당
	in_degree = (int *)malloc(g->n* sizeof(int));

	// 초기화
	for( i=0; i<g->n; i++)
		in_degree[i]=0;
	// 모든 정점의 진입 차수를 계산
	for( i=0; i<g->n; i++) {
		GraphNode *node = g->adj_list[i];
		while( node != NULL ) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	// 진입 차수가 0인 정점을 스택에 삽입
	init(&s); // 스택 초기화
	for( i=0; i<g->n; i++)
	{
		if( in_degree[i] == 0 ) 
		{
			for( j=0; j<count; j++){ // 데이터에 없는 정점 제외
				if( temp[j].num == i )
					push(&s,temp[j]);// temp구조체배열을 push
			}
		}
	}

	// 위상 순서를 생성
	i=1; // j 초기화
	while(!is_empty(&s)){
		element w;   // 구조체 w 선언
		w = pop(&s); // pop
		printf("%d. %d-%s\n",i++,w.num,w.name); // 출력문
		node = g->adj_list[w.num];
		// in_degree에서 --하여 또 0일경우 temp구조체 배열 push
		while(node != NULL) {
			int u = node->vertex;
			in_degree[u]--;
			if(in_degree[u] == 0){
				for( j=0; j<count; j++){ // 데이터에 없는 정점 제외
					if( temp[j].num == u )
						push(&s,temp[j]);
				}
			}
			node = node->link; // 다음 노드로
		}
	}
	free(in_degree); // in_degree 삭제
	return; // 종료
}


int main()
{
	GraphType g;     // GraphType g 선언
	char ch;         // v,e 판별
	int num_x,num_y; // 정점x,y
	int i=0;

	// 파일 변수 fp
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}

	// 정점 개수 파악
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v'){
			count++;
		}
	}

	// 정점 값을 저장할 배열 동적 할당
	temp = (element *)malloc(sizeof(element)*count);

	// 그래프 초기화
	graph_init(&g);

	// 데이터
	printf("< 데이터 >\n");
	printf("------------------\n");
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch); // v, e 판별
		// v일 경우
		if( ch == 'v')
		{
			fscanf(fp,"%d %s",&g.n,&g.name);
			printf("%d-%s\n",g.n,g.name);
			// temp배열에 파일 데이터값 저장
			temp[i].num = g.n;
			strcpy(temp[i].name,g.name);
			i++;
			// 정점 삽입
			insert_vertex(&g,g.n);
		}
		// e일 경우
		else if( ch == 'e')
		{
			fscanf(fp,"%d %d",&num_x,&num_y);
			// 간선 삽입
			insert_edge(&g,num_x,num_y);
		}
	}
	printf("------------------\n\n");

	// 위상 순서 출력
	printf("< 위상 순서 출력 >\n");
	printf("------------------\n");
	topo_sort(&g); // 위상 정렬 함수
	printf("------------------\n");

	free(temp); // temp동적할당 반납
	fclose(fp); // 파일을 닫습니다
	return 0;   // 종료
}