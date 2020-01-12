///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 27일
// 프로그램명   : 선형조사법을 이용한 HashTable
//   설  명     : data.txt에 저장된 정수들을 선형 조사법을 이용한 HashTable
//                에 저장하라. 후에 조건에 맞게 출력하는 프로그램
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// 정의
#define TABLE_SIZE 10  
#define empty(e) (e.key == 0)

// element 구조체
typedef struct {
	int key; // 정수형 key
}element;

// key값을 가진 Hash_table배열
element hash_table[TABLE_SIZE];

// Hash_table 초기화
void init_table(element *ht)
{
	int i;
	for(i=0; i<TABLE_SIZE; i++) {
		ht[i].key=NULL;
	}
}

// hash 함수
int hash_function(int key)
{
	return key%7;
}

// hash 삽입
void hash_lp_add(element item,element *ht)
{
	int i,hash_value;

	hash_value = i = hash_function(item.key); // hash_function() 값으로 초기화

	while(!empty(ht[i])){
		if(item.key != ht[i].key){ // 충동 시
			printf("data = %d 저장 도중 Hashtaable : %d 에서 충돌 감지 ", item.key, i);
		}
		i = (i+1) % TABLE_SIZE; // i 증가
		printf("- index = %d로 증가하였습니다.\n",i);
		if(i == hash_value) { // 테이블이 초과할 시
			fprintf(stderr,"테이블이 가득찼습니다\n");
			return;
		}
	}
	ht[i] = item; // item 대입
}

// Hash 탐색
void hash_lp_search(element item, element *ht)
{
	int i,hash_value;

	hash_value = i = hash_function(item.key);

	while(!empty(ht[i])) 
	{
		if(item.key == ht[i].key ){ // 검색될 경우
			printf("%2d 는 HashTable : %d 에서 검색되었습니다..\n",item.key,i);
			return;
		}
		i = (i+1) % TABLE_SIZE; // i+1로 재 계산
	}
	if(item.key != ht[i].key) // 검색되지 않을 경우
	{
		printf("입력하신 값 %d 은 HashTable에서 검색되지않았습니다.\n",item.key);
	}
}

int main()
{
	element tmp; // 구조체 tmp
	char ch;     // i와 s 판단
	int z = 0;   // 출력문 조건변수

	// data1.txt를 읽기형식으로 오픈
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}
	
	// HashTable Size 출력
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);
    
	// Date Insert Finish 
	printf("< Date Insert Finish >\n");
	while(!feof(fp))
	{
		fscanf(fp," %c",&ch);
		if( ch == 'i')
		{
			fscanf(fp,"%d",&tmp.key);
			hash_lp_add(tmp,hash_table); // hash 삽입
		}
		else if( ch == 's') 
		{
			// Find Data Location
			if( z == 0 )
			{
				printf("\n< Find Data Location >\n");
				z++;
			}
			fscanf(fp,"%d",&tmp.key);
			hash_lp_search(tmp,hash_table); // hash 탐색
		}
	}

	printf("< Finish >\n\n");

	fclose(fp); // 파일을 닫습니다
	return 0;   // 종료
}