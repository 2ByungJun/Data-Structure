///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 18일
// 프로그램명   : 배열로 구현된 연결리스트 1
//   설  명     : 사용자가 입력한 숫자만큼 랜덤 숫자들을 생성하여 배열로
//                구성한 연결리스트에 추가하고 최대값과 최소값을 아래
//                결과와 같이 출력 하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>  // malloc,srand,rand를 쓰기 위함 라이브러리 함수
#include <time.h>    // time을 쓰기위한 라이브러리 함수

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

// 리스트 출력
void display(ArrayListType *L)
{
	int cmp[MAX_LIST_SIZE]={0};
	int i,j;
	int count=0;
	int max=0;
	int min=999;

	// 최대값 최소값 해당 수 찾는 반복문
    for(i=0; i<(L->length); i++)
	{
		if ( max < L->list[i] )
			max = L->list[i];    // 최대값 대입
		else if ( min > L->list[i] )
			min = L->list[i];    // 최소값 대입
	}

	// 최대값 최소값 위치를 cmp[]에 저장
	for(i=0; i<(L->length); i++)
	{
		if ( max == L->list[i] )
			cmp[i] = 1; // 최대값일 경우 1 대입
		else if ( min == L->list[i] )
			cmp[i] = 2; // 최소값일 경우 2 대입
	}
	printf("최대:%d 최소:%d\n",max,min);

	// 최댓값 최소값 
	for( i = 0; i < L->length; i+=15)        // i+=15을 주어 15의 자리수인 큰 반복틀을 형성한다.             
   {
	    for(j = 0; j < 15; j++)      // z값을 이용해 1의 자리수를 반복하여 출력하는 반복문
		{
			if( i + j >= L->length)  // C[데이터값]의 쓰레기값이 나오지 않게 해주는 조건문
				break;               // '제거시'에는 뒤에 값에서 쓰레기주소값이 나온다.

			printf("%d  \t", L->list[i+j]);  // C[0]~C[i]까지 출력시켜준다.
		}
		printf("\n");

		for(j = 0; j < 15; j++)       // 최대값 최소값 위치 탐색 반복문
		{
			if(cmp[i+j] == 1) {         // 최대값 위치를 1로 지정하였고 cmp[j] 1일경우 그 위치에 "최대값"을 출력해준다.
				printf("Max   ");
			}
			if(cmp[i+j] == 2)  {        // 최소값 위치를 2로 지정하였고 cmp[j] 2일경우 그 위치에 "최소값"을 출력해준다.
				printf("Min   ");
			}
			if(cmp[i+j] == 0)  {        // 최대값도 최소값 아닌 곳에 공백을 출력해주는 조건식
				printf("\t");
			};
		}
		printf("\n");		
   }
}

int main()
{
	ArrayListType *plist;  // plist 동적배열 생성
	int n; // 숫자 개수를 받을 변수
	int i; // 반복문 증가값 변수

	// 생성할 숫자 입력
	printf("생성할 랜덤 숫자 개수를 입력하세요 : ");
	scanf("%d",&n);
	printf("[ 배열로 구현된 연결리스트에 추가된 데이터 ]");
	
	// plist를 동적 구조체 할당
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*n);
	init(plist); // 리스트 초기화

	srand(time(NULL)); // 시간을 초기화 시켜 때마다 난수를 랜덤하게 출력
	for(i=0; i<n; i++) // 랜덤함수 출력
	{
		add(plist,i,rand()%1000); // plist에 난수들을 삽입
	}

	printf("\n");
	display(plist); // plist 출력
	free(plist);    // plist 동적 메모리 반납
}

