///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 18일
// 프로그램명   : 배열로 구현된 연결리스트 3
//   설  명     : 학생 별 학번,국어,영어,수학의 점수가 data.txt 파일에
//                저장되어 있다. 이 파일의 데이터를 읽어 들여 동적으로
//                만든 구조체 배열에 저장하고, 학생의 학번 또는 이름을
//                입력 받아 그 학생의 성적 및 총점, 평균, 등수를 출력하라
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // 배열의 최대 크기

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE]; // 배열의 정의
	int length; // 현재 배열에 저장된 자료들의 개수
}ArrayListType;
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
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
// position : 삭제하고자 하는 위치
// 반환 값 : 삭제되는 자료
element delete(ArrayListType *L, int position )
{
	int i;
	element item;

	if(  position < 0 || position >= L->length)
		error("위치 오류");
	for(i=position; i<(L->length-1); i++)
	item = L->list[i] = L->list[i+1];
	L->length--;
	return item;
}

int main()
{
	ArrayListType *plist; // plist 구조체 배열 선언
	int count=0;          // 파일 데이터 개수를 구할 변수
	int num;              // count를 구하기 위한 파일을 읽어줄 변수
	int i;                // 반복 증가값 변수
	int delete1=1;        // 홀수 위치를 나타낼 변수
	FILE *fp = fopen("data3.txt","r"); // data3.txt를 읽기상태로 오픈
	if( fp == NULL)                    // 파일오류시 에러문구 출력
	{
		printf("파일이 열리지 않았습니다\n");
		return 0;
	}
	
	while(!feof(fp)) // count값을 구하기 위해 파일을 읽어주는 반복문
	{
		fscanf(fp,"%d",&num);
		count++;
	}

	// count값의 크기만큼 plist배열 동적할당
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count);
	init(plist); // plist 배열 초기화

	rewind(fp); // 파일 포인터위치 초기화
	for(i=0; i<count; i++) // count크기의 반복문
	{
		fscanf(fp,"%d",&num);  // 파일 데이터값을 num값에 대입
		add(plist , i , num ); // num값을 plist리스트의 i위치에 삽입
	}

	display(plist); // plist 리스트를 출력
	
	for ( i=0; i<count-1; i++) // count-1 크기만큼 반복
	{
		if( i%2 == 1 ){        // i값이 홀수일 경우
		delete( plist, delete1); // plist리스트의 delete1번째 변수를 삭제
		delete1++; // delete1값을 증가
		}
	}
	display(plist); // plist출력

	fclose(fp);  // 파일을 닫아준다
	free(plist); // plist리스트 동적 메모리 반납
}