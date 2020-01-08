///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 2일
// 프로그램명   : 그래프 깊이 우선 탐색 프로그램
//   설  명     : data3.txt파일에 입력되어 있는 정점과 간선의 정보를 이용
//                하여 그래프를 구성하고 깊이 우선 탐색을 통해 출력하라
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

int visited[MAX_VERTICES]; // 전역변수 선언

typedef struct GraphType{
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

// 그래프 초기화
void graph_init(GraphType *g)
{
	int r,c;
	g->n = 0;
	for(r=0; r<MAX_VERTICES; r++)
		for(c=0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c]=0;
}

// 정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1 ) > MAX_VERTICES ) {
		fprintf(stderr,"그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}

// 간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
	if( start > g->n || end > g->n ) {
		fprintf(stderr,"그래프: 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// 인접 리스트로 표현된 그래프에 대한 깊이 우선 탐색
void dfs_mat(GraphType *g,int v)
{
	int w;
	visited[v] = TRUE;                  // 정점 v의 방문 표시
	printf("%d ",v);                    // 방문한 정점 출력
	for(w=0; w<=g->n; w++) // 인접 정점 탐색
		if( g->adj_mat[v][w] && !visited[w] )
			dfs_mat(g,w);      // 정점 w에서 DFS 새로시작 
}

int main()
{
	GraphType g;       // 그래프 선언
	char c;            // v와 e 구분
	int num_v;         // v데이터 값
	int num_e1,num_e2; // e데이터 값들

	// data3.txt 읽기
	FILE *fp = fopen("data3.txt","r");
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
		}
	}

	// 깊이 우선 탐색
	printf("- 그래프 깊이 우선 탐색 결과 -\n< ");
	dfs_mat(&g,0);
	printf(">\n");

	fclose(fp); // 파일을 닫아준다
	return 0;   // 종료
}