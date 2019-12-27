///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 18일
// 프로그램명   : 배열로 구현된 연결리스트 2
//   설  명     : 배열로 구성한 연결리스트 내에서 사용자가 입력한
//                숫자가 몇 번째에 있는지 검색하는 함수를 구현하고 출력
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> // malloc를 사용하기 위한 라이브러리 함수

#define MAX_LIST_SIZE 10000 // 배열의 최대 크기

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE]; // 배열의 정의
	int length; // 현재 배열에 저장된 자료들의 개수
}ArrayListType;

// 리스트 초기화
void init(ArrayListType *L)
{
	L->length = 0;
}
// 리스트가 비어 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_empty(ArrayListType *L)
{
	return L->length == 0;
}
// 리스트가 가득 차 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_full(ArrayListType *L)
{
	return L->length == MAX_LIST_SIZE;
}
// 리스트 출력
void display(ArrayListType *L)
{
	int i;
	for( i=0; i<L->length; i++){
		printf("%d ",L->list[i]);
		if ( i != L->length-1)
		printf("-> ");
	}
	printf("\n");
}
// position : 삽입하고자 하는 위치
// item : 삽입하고자 하는 자료
void add(ArrayListType *L , int position,element item)
{
	if( !is_full(L) && (position >= 0) && (position <= L->length) ) 
	{
			int i;
			for( i=(L->length-1); i>=position; i--) 
				L->list[i+1] = L->list[i];
			L->list[position] = item;
			L->length++;
	}
}

// 숫자가 몇 번째에 있는지 검색하는 함수
int find( ArrayListType *L, int count )
{
	int i=0, j;  // 반복 증가값 변수
	int zero=0;  // 리스트에 없을 경우를 위한 카운팅 변수
	int value;   // 입력받을 값을 저장하는 변수

	while ( 1 )  // 무한루프 반복문
	{
		if ( i == 0 ) // i == 0 일경우 값을 입력받는 조건
		{
			printf("값을 입력하세요<0:종료> : ");
			scanf("%d",&value);
			if ( value == 0 )
				return 0;
		}
		// 값이 존재할 경우
		if ( value == L->list[i] ){
			printf("%d은(는) 리스트 ", value );
			for( j = 0; j< count; j++ )     // 값의 위치를 알려줄 반복문
			{
				if ( value == L->list[j] )  // 값이 list의 값과 동일할 경우
					printf("%d ",j+1);      // 위치를 출력
			}
			printf("번째에 있습니다.\n\n");
			i = 0;    // 재시도를 위한 i를 0으로 초기화
			continue; // 재반복
		}
		else if ( value != L->list[i] ) // 리스트를 탐색하면서 없을 경우 zero를 카운팅
			zero++;

		// 값이 리스트에 없을 경우
		if( zero == count )  // zero가 count와 같을 경우는 탐색을 끝까지 마친 후 값이 없을 경우이다
		{
			printf("%d은(는) 리스트에 없습니다.\n\n",value);
			i = 0;    // 재시도를 위한 i를 0으로 초기화
			zero = 0; // 재시도를 위한 zero를 0으로 초기화
			continue; // 재반복
		}
		i++;
	}
}

int main()
{
	ArrayListType *plist; // 구조체 동적할당받을 배열
	int count=0;          // 파일 데이터 개수
	int num;              // count를 위해 파일을 읽어줄 변수
	int i;                // 반복 증가값 변수
	FILE *fp = fopen("data2.txt","r"); // data2.txt파일을 읽기 형식으로 오픈
	if( fp == NULL)                    // 파일이 열리지 않았을 경우 에러문구 출력
	{
		printf("파일이 열리지 않았습니다\n");
		return 0;
	}
	
	while(!feof(fp)) // count값을 얻기 위한 파일을 끝까지 읽는 반복문
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	// count 크기만큼 plist 구조체배열에 동적메모리 할당
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count);
	init(plist); // plist 리스트 초기화

	rewind(fp);
	for(i=0; i<count; i++)  // count 크기만큼 반복문
	{
		fscanf(fp,"%d",&num);  // 파일에서 데이터를 num값에 입력받는다
		add(plist , i , num ); // num값을 plist리스트에 순차적으로 삽입
	}
	fclose(fp); // 파일을 닫아준다
	display(plist); // plist 리스트 출력

	find(plist,count); // find함수로 plist의 숫자가 몇번째있는지 검색해준다

	free(plist); // plist리스트 동적메모리 반납
	return 0;
}