///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 11일
// 프로그램명   : Kruskal의 MST 알고리즘
//   설  명     : 책 p431에 코드를 참조하여 Kruskal의 최소 비용 신장 트리
//                프로그램을 작성하고 비용을 결과를 출력하는 프로그램
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000 // INF는 정점끼리의 간선이 없음을 표시

int parent[MAX_VERTICES]; // 부모 배열
int num[MAX_VERTICES];

// 초기화
void set_init(int n)
{
	int i;
	for( i=0; i<n; i++){
		parent[i] = -1;
		num[i] = 1;
	}
}
// vertex가 속하는 집합을 반환한다
int set_find(int vertex)
{
	int p,s,i=-1;
	for(i=vertex; (p=parent[i])>=0; i=p) // 루트 노드까지 반복
		;
	s = i; // 집합의 대표 원소
	for(i=vertex; (p=parent[i])>=0; i=p )
		parent[i] = s; // 집합의 모든 원소들의 부모를 s로 설정
	return s;
}
// 두 개의 원소가 속한 집합을 합친다.
void set_union(int s1,int s2)
{
	if( num[s1] < num[s2] ){
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

// element 구조체 정의
typedef struct {
	int key; // 간선의 가중치
	int u;   // 정점 x
	int v;   // 정점 y
} element;

// 히프 구조체 정의
typedef struct{
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

// 히프 초기화
void init(HeapType *h)
{
	h->heap_size = 0;
}
// 히프 삽입
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);
	//
	while( (i != 1) && (item.key < h->heap[i/2].key )){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}
// 히프 삭제
element delete_min_heap(HeapType *h)
{
	int parent,child;
	element item,temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while( child <= h->heap_size ){
		//
		if( ( child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child+1].key)
			child++;
		if( temp.key <= h->heap[child].key) break;
		//
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// 정점 u와 정점 v를 연결하는 가중치가 weight인 간선을 히프에 삽입
void insert_heap_edge(HeapType *h,int u,int v,int weight,int n)
{
	element e;
	int i;
	e.u = u;
	e.v = v;
	e.key = weight;

	for(i = 1; i<n; i++)
	{
		if(((h->heap[i].u == e.u) && (h->heap[i].v == e.v)) ||
			((h->heap[i].v == e.u) && (h->heap[i].u == e.v)))
		{
				printf("간선 %d - %d은 이미 추가된 간선입니다. -- 제외\n",e.u,e.v);
				return;
		}
	}
	insert_min_heap(h,e);
	printf("간선 %d - %d 추가 완료\n",u,v);
}
// 인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입
void insert_all_edges(HeapType *h,int n)
{
	int edg1,edg2,length; // 정점1,정점2,간선 가중치

	// data2.txt 파일을 읽기
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 간선 삽입
	while(!feof(fp)){
		fscanf(fp,"%d %d %d",&edg1,&edg2,&length);
		insert_heap_edge(h,edg1,edg2,length,n);
	}
	fclose(fp); // 파일을 닫아준다.
}
// kruskal의 최소 비용 신장 트리 프로그램
void kruskal(int n)
{
	int edge_accepted=0; // 현재까지 선택된 간선의 수
	HeapType h;          // 최소 히프
	int uset, vset;      // 정점 u와 정점 v의 집합 번호
	int mul_sum=0;       // 최소 누적값
	element e;           // 히프 요소
	int i=0;             // 반복 변수

	init(&h); // 히프 초기화
	printf(">> 데이터 입력\n");
	
	insert_all_edges(&h,n); // 히프에 간선들을 삽입
	set_init(n);            // 집합 초기화

	// 과정
	printf("\n>> 과정\n");
	while( edge_accepted < (n-1) ) // 간선의 수 < n-1
	{
		e = delete_min_heap(&h); // 최소 히프에서 삭제
		uset = set_find(e.u);    // 정점 u의 집합 번호
		vset = set_find(e.v);    // 정점 v의 집합 번호
		if( uset != vset) {      // 서로 속한 집합이 다르면
			printf("간선 %d-%d : %d \n",e.u ,e.v ,e.key);
			mul_sum += e.key;    // 최소 비용 누적 합
			edge_accepted++;
			set_union(uset, vset);
		}
		else{                    // 서로 속한 집합이 같을 경우
			printf("간선 %d-%d : %d - 사이클 생성으로 제외 \n",e.u, e.v, e.key);
			// 히프의 남은 쓰레기 값 출력을 방지하기 위해 간선의 수를 강제로 증가
			if( edge_accepted == n-2 ) // 기존 while범위보다 -1
				edge_accepted++;
		}
	}
	// 최소 비용 출력
	printf("\n< 필요한 최소 비용 %d >\n",mul_sum);
}
int main()
{
	int edg1,edg2,length; // 정점1, 정점2, 가중치
	int high=0;           // 최대 정점

	// data2.txt 파일을 읽기
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}

	// high으로 정점 최대 값을 대입
	while(!feof(fp)){
		fscanf(fp,"%d %d %d",&edg1,&edg2,&length);
		if( high < edg2)
			high = edg2;
	}

	// kruskal 프로그램 실행
	rewind(fp);
	kruskal(high+1);

	// 파일을 닫은 후 종료
	fclose(fp);
	return 0;
}