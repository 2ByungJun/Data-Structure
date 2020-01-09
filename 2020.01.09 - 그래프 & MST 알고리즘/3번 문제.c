///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 11일
// 프로그램명   : Prim의 MST 알고리즘
//   설  명     : 책 p436에 코드를 참조하여 Prim의 최소 비용 신장 트리
//                프로그램을 작성하여 테스트하기
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1    // 갔던 곳 TRUE표시 정의
#define FALSE 0   // FALSE로 초기화
#define INF 1000L // INF는 정점끼리의 간선이 없음을 표시

int **weight;  // 이차원 행렬
int *selected; // 임시 저장 배열
int *dist;     // 정점의 개수 크기의 배열, 현재의 가중치 크기를 나타냄

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v,i;
	for ( i=0; i<n; i++)
		// 들리지 않았다면
		if ( !selected[i]) {
			v = i;
			break;
		}
	for( i = 0; i<n; i++)
		// 들리지 않았거나 가중치가 더 작을 경우를 비교
		if( !selected[i] && (dist[i] < dist[v])) 
			v = i;
	// 정점 반환
	return (v);
}
// s : 시작 정점
// n : 정점 개수
void prim(int s,int n)
{
	int i,j,v,u; // i,j,v : 반복변수, u : 정점
	int *Array;  // u정점의 순서를 기억할 배열
	int sum = 0;   // 가중치 누적 합 변수

	// 동적 할당
	Array = (int *)malloc(sizeof(int)*n);

	printf(">> 과정\n");
	// dist와 selected 배열 초기화
	for(u=0; u<n; u++)
	{
		dist[u] = INF; selected[u] = FALSE; 
	}
	// 정점의 시작부분의 가중치를 0으로 초기화
	dist[s]=0;

	for(i=0; i<n; i++){
		u=get_min_vertex(n);
		// 같던 곳 TRUE 표시
		selected[u] = TRUE;
		// 가중치가 INF면 리턴
		if( dist[u] == INF ) return;

		// 과정 출력
		printf("%d >> ",i+1); 
		Array[i] = u;
		// 실행 순서 출력
		for( j=0; j<i+1; j++)
			printf("%d ",Array[j]); 
		// 가중치 누적 합 출력
		sum += dist[u];
		printf(": %d\n",sum);

		for( v=0; v<n; v++)
			if(weight[u][v] != INF)
				if( !selected[v] && weight[u][v] < dist[v] )
					dist[v] = weight[u][v];
	}
	// 동적 할당 반납
	free(Array);
	// 최소 비용 출력
	printf("\n< 필요한 최소 비용 %d >\n",sum);
	exit(1);
}
//
int main()
{
	int num_x;   // 정점 x 
	int num_y;   // 정점 y
	int num_add; // 가중치
	int max_num=0; // 최대 정점
	int count=0;   // 파일 데이터 값
	int i,j;       // 반복 변수

	// data3.txt 파일 오픈
	FILE *fp = fopen("data3.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 최대정점 구하기
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d",&num_x,&num_y,&num_add);
		if( max_num < num_y ) // 최대정점 구하기
			max_num = num_y;
	}
	// 동적 할당
	weight = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<=max_num; i++ ){
		weight[i] = (int *)malloc(sizeof(int)*max_num);
	}
	selected = (int *)malloc(sizeof(int)*max_num);
	dist = (int *)malloc(sizeof(int)*max_num);

	// weight 초기화
	for(i=0; i<=max_num; i++){
		for(j=0; j<=max_num; j++)
			weight[i][j] = INF;
	}

	// weight 형성
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d",&num_x,&num_y,&num_add);
		weight[num_x][num_y] = num_add;
		weight[num_y][num_x] = num_add;
	}
	for( i=0; i<=max_num; i++){
		weight[i][i] = 0;
	}

	// Prim 프로그램 실행
	printf("- Prim의 최소 비용 신장 트리 프로그램 -\n\n");
	prim(0,max_num+1);

	// 파일 닫기
	fclose(fp);
	// 동적 할당 반납
	for(i=0; i<=max_num; i++) free(weight);
	free(weight);
	free(dist);
	free(selected);
	return 0;
}
