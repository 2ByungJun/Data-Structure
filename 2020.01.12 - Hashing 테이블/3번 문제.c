///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 27일
// 프로그램명   : 체이닝을 이용한 HashTable
//   설  명     : data.txt에 저장된 정수들을 체이닝을 이용한 HashTable
//                에 저장하라. 후에 조건에 맞게 출력하는 프로그램
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // 테이블 사이즈

// 정의부
#define empty(e) (e.key == 0)
#define equal(e1,e2) (e1 == e2)

// element 정의
typedef struct element{
	int key;
}element;

// ListNode 정의
typedef struct ListNode{
	element item;
	struct ListNode *link;
}ListNode;

// ListNode형 해시 테이블 선언
ListNode *hash_table[TABLE_SIZE]={NULL};

// 해시 함수
int hash_function(int key)
{
	int hash_index = key % 7;
	if(hash_index < 0)
		hash_index += 7;
	return hash_index;
}
// 해시 체이닝 삽입
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *ptr;                   // 리스트 노드
	ListNode *node_before=NULL;      // 전 노드
	ListNode *node = ht[hash_value]; // 새로운 노드

	node_before = node;

	for(; node; node_before=node, node = node->link){
		if(equal(node->item.key,item.key)){
			fprintf(stderr,"이미 탐색 키가 저장되어 있음\n");
			return;
		}
	}
	// 새로운 노드 생성
	ptr = (ListNode *)malloc(sizeof(ListNode));
	ptr->item = item;
	ptr->link = NULL;
	// 전 노드와 연결
	if(node_before)
		node_before->link = ptr;
	else{
		ht[hash_value] = ptr;
	}
}
// 해시 체이닝 탐색
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;
	int i=0;
	int hash_value = i = hash_function(item.key);

	// 노드 탐색
	for(node = ht[hash_value]; node; node = node->link){
		// 현재노드값과 가리키는 노드값이 같을 경우
		if(equal(node->item.key,item.key)){
			printf("%3d의 검색 결과 - HashTable[%d] : ",item.key,i);
			node = ht[hash_value];
			// 노드 출력문
			while(node != NULL){
				printf("(%d) - > ",node->item.key);	
				// 현재노드값과 가리키는 노드값이 같을 경우 줄바꿈
				if(equal(node->item.key ,item.key)){
					printf("\n");
					return;
				}
				node = node->link; // 다음 노드로		
			}			
		}		
	}
	// 없을 경우
	printf(" 입력하신 값 %d 는 HashTable에서 검색되지 않았습니다. \n",item.key);
}

int main()
{
	element tmp; // 구조체 tmp
	char ch;     // i와 s판단

	// data3.txt를 읽기 형식으로 오픈
	FILE *fp = fopen("data3.txt","r");
	if(fp == NULL){
		printf("파일 열기 실패");
		exit(1);
	}
    // 테이블 크기
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);

	// 테이블 삽입
	printf("< Data Insert Finish >\n");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(ch=='i'){
			fscanf(fp,"%d",&tmp.key);
			hash_chain_add(tmp,hash_table); // 삽입
		}
		else if(ch =='s'){
			fscanf(fp,"%d",&tmp.key);
		}
	}
	printf("\n\n");

	// 테이블 탐색
	rewind(fp);
	printf("< Find Data Location >\n");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(ch=='i'){
			fscanf(fp,"%d",&tmp.key);

		}
		else if(ch =='s'){
			fscanf(fp,"%d",&tmp.key);
			hash_chain_find(tmp,hash_table); // 탐색
		}
	}

	printf("< Finish >\n\n");
	fclose(fp); // 파일을 닫습니다
	return 0;   // 종료
}