///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 16일
// 프로그램명   : 셸 정렬 프로그램
//   설  명     : data4.txt에 학생의 정보가 이름, 학번, 전화번호로 저장
//                되어 있다. 이를읽어와 학번 순으로 내림차순 정렬하여
//                출력하시오.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// element 구조체 정의
typedef struct element{
	char name[20]; // 이름
	int schoolnum; // 학번
	char phone[20];// 핸드폰 번호
}element;

// 셸 정렬 삽입과정
// *list : 구조체 배열
// first : 배열 첫 인덱스
// last : 배열 끝 인덱스
// gap : 셸 정렬에서 나눠주기위한 인덱스끼리의 차이
void inc_insertion_sort(element *list,int first,int last,int gap)
{
	int i,j;
	element	key; // 데이터를 잠깐 저장할 key구조체
	for(i=first+gap; i<=last; i=i+gap){
		key = list[i]; // 데이터를 gap차이만큼 뽑아 key에 보관
		for(j=i-gap; j>=first && key.schoolnum>list[j].schoolnum; j=j-gap)
			list[j+gap]=list[j]; // key끼리 학번을 기준으로 정렬
		list[j+gap] = key; // 정렬 후 삽입
	}
}
// 셸 정렬
// *list : 구조체 배열
// n : 파일 데이터 개수
void shell_sort(element *list,int n)
{
	int i,gap;
	for(gap=n/2; gap>0; gap=gap/2) { 
		if( (gap%2) == 0 ) // 갭이 짝수 일경우 증가
			gap++;
		for(i=0; i<gap; i++) // 갭까지 반복
			inc_insertion_sort(list,i,n-1,gap); // 삽입 정렬
	}
}

int main(){
	element *temp; // 구조체배열 temp
	element e;     // 구조체 e
	int count=0;   // 파일 개수
	int i=0;       // 반복 변수
	// 파일 오픈
	FILE *fp= fopen("data4.txt","r");
	if(fp == NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 파일 데이터 개수체크
	while(!feof(fp)){
		fscanf(fp,"%s %d %s",e.name,&e.schoolnum,e.phone);
		count++;
	}
	// 동적 할당
	temp = (element *)malloc(sizeof(element)*count);

	// 파일포인터 리셋
	rewind(fp);

	// 정렬 전 출력
	// temp[i]에 파일 데이터값 대입
	printf("<정렬 전>\n");
	for( i=0; i<count; i++)
	{
		fscanf(fp,"%s %d %s",temp[i].name,&temp[i].schoolnum,temp[i].phone);
		printf("%s %d %s\n",temp[i].name,temp[i].schoolnum,temp[i].phone);
	}

	// 정렬 후 출력
	// 셸 정렬 사용
	printf("\n<정렬 후>\n");
	shell_sort(temp,count);
	for( i=0; i<count; i++)
	{
		printf("%s %d %s\n",temp[i].name,temp[i].schoolnum,temp[i].phone);
	}

	free(temp); // temp 동적반납
	fclose(fp); // fp 파일을 닫습니다.
	return 0;
}