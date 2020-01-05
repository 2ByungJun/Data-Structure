///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 9일
// 프로그램명   : 동물 히프
//   설  명     : 배열을 이용한 히프를 사용해서 data.txt에 있는 우선
//                순위대로 동물들의 이름을 저장하고 사용자가 원하는
//                동물의 이름과 우선순위를 받아 히프에 추가하는 프로그램을
//                작성하시오.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// 배열크기 정의
#define MAX_ELEMENT 200
// 스왑 정의
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

// element 정의
typedef struct {
	int key;
	char animal[20];
} element;

// HeapType 정의
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 초기화
void init(HeapType *h)
{
	h->heap_size = 0;
}

// 삽입
void insert_max_heap(HeapType *h,element item)
{
	int i;
	i = ++(h->heap_size);

	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while((i != 1) && (item.key > h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}

// 힙 정렬
void heap_sort(HeapType *h,int n)
{
	int i,j,least; // 반복변수 및 최소값위치 저장값
	element temp;  // temp구조체
	for(i=1; i<=n-1; i++){
		least = i;
		for(j=i+1; j<=n; j++)
			if(h->heap[j].key > h->heap[least].key) least = j;
		SWAP(h->heap[i],h->heap[least],temp);
	}
}

// 출력
element display(HeapType *h,int n)
{
	int i;
	for(i = 1; i<=n; i++){
		printf("%d:%s > ", h->heap[i].key , h->heap[i].animal );
	}
	printf("\n");
}

int main()
{
	element e;
	HeapType heap; // 히프생성
	int count=0;
	FILE *fp = fopen("data1.txt","r");
	if( fp == NULL ){
		printf("파일 에러\n");
		exit(1);
	}
	init(&heap);

	// 파일 값 우선순위 큐
	while(!feof(fp)){
		// 파일 데이터 받아오기
		fscanf(fp,"%d %s",&e.key , e.animal);
		printf(">>%d %s\n",e.key , e.animal);
		// 삽입
		insert_max_heap(&heap,e);
		count++;
		// 힙 정렬
		heap_sort(&heap,count);
		// 힙 출력
		display(&heap,count);
	}
	printf("\n");

	// 사용자가 추가할 값 
	while(1){
	printf("히프에 데이터를 넣을 동물의 우선순위와 이름을 입력하시오(완료시 우선순위 0)\n");
	    // 추가 데이터 받아오기
		printf(">>");
		scanf("%d ", &e.key);
		if( e.key == 0 )
			break;
		scanf("%s", e.animal);
		// 삽입
		insert_max_heap(&heap,e);
		count++;
		// 힙 정렬
		heap_sort(&heap,count);
		// 힙 출력
		display(&heap,count);
		printf("\n");
	}

	fclose(fp); // 파일을 닫습니다.
	return 0;
}