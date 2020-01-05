///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 10일
// 프로그램명   : 우선 순위 큐
//   설  명     : data.txt에 손님의 입장과 퇴장이 이름과 함께 입력되어있다.
//                각 입장과 퇴장을 히프에 적용하고 이를 중위 순회를 이용하여
//                출력하시오.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 100

// element 정의
typedef struct {
	char name[MAX_ELEMENT]; // 이름
	int key; // 인덱스
} element;

// HeapType 정의
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// 초기화함수
void init(HeapType *h){
	h->heap_size = 0;
}

// Min순위 삽입
void insert_min_heap(HeapType *h,element item)
{
	int i;
	i = ++(h->heap_size);

	// 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while((i != 1) && (item.key < h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item; // 새로운 노드를 삽입
}

// Min순위 삭제
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while( child <= h->heap_size ){
		// 현재 노드의 자식 노드 중 더 작은 자식 노드를 찾는다.
		if( ( child < h->heap_size ) && 
			( h->heap[child].key) > h->heap[child+1].key)
			child++;
		if( temp.key <= h->heap[child].key) break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 출력
void display(HeapType *h)
{
	int i;
	printf("< 히프 중위 순회 출력 >\n");
	// heap_size만큼 출력
	for(i = 1; i<=h->heap_size; i++){ 
		printf("%d - %s\n", i , h->heap[i].name );
	}
	printf("\n");
}

int main()
{
	HeapType heap;   // heap생성
	element e;       // 구조체e
	element delete_e;// 삭제한 구조체 대입변수
	char s[20];      // 선수 이름을 읽어올 문자열
	char c;          // i / o 입출력
	int i=0;         // 인덱스
	// data2.txt파일을 읽기형식으로 오픈
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){ // 파일 에러시
		printf("파일 에러\n");
		exit(1);
	}
	init(&heap); // heap 초기화

	while(!feof(fp)){
		fscanf(fp,"%c",&c); // i / o 문자를 c로 받아온다.
		if( c == 'i'){      // i일 경우 입장
			fscanf(fp,"%s",s);  // 파일에서 이름을 받아 s에 저장.
			i++;
			printf(">> 손님(%s) 입장\n",s);
			// 삽입
			e.key = i;        // 인덱스 값
			strcpy(e.name,s); // 이름 복사
			insert_min_heap(&heap,e); // e삽입
			display(&heap);   // 출력
		}

		else if( c == 'o'){ // o일 경우 퇴장
			delete_e = delete_min_heap(&heap); // 삭제하여 delete_e에 대입
			printf(">> 손님(%s) 퇴장\n",delete_e.name);
			display(&heap); // 출력
		}

	}

	fclose(fp); // 파일을 닫아준다.
	return 0;
}