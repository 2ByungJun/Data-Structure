///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 10일
// 프로그램명   : 구조체 배열
//   설  명     : 동물원에서 동물을 관리하는 프로그램을 사용하려 한다.
//                동물의 종, 고유번호, 위치, 수를 파일에 저장하고
//                사용하려 한다. 이를 동적 할당으로 구조체 배열에
//                저장하고 검색하는 프로그램을 작성하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  // malloc,free를 써주기 위한 라이브러리 함수 
#include <string.h>  // 문자열을 다루는 라이브러리 함수

typedef struct Animal // Animal구조체 생성
{
	char animal[20];  // 종
	char num[20];     // 고유번호
	char area[20];    // 위치
	char total[20];   // 개체 수
}Animal; // Animal로 정의

int main()
{
    Animal *tmep;     // tmep 동적할당 구조체배열 선언
	int F_line; // 파일을 읽어줄 라인변수선언
	int count = 0;    // 데이터 값을 카운팅해줄 변수
	int i=0 , j=0;    // 반복문 증가값 변수
	int select;       // 검색할 조건을 입력할 변수
	char type[20];    // 검색값을 저장할 배열

	FILE *fp = fopen("data2.txt","r");  // data2.txt파일을 읽기형식으로 오픈
	if(fp == NULL)                      // 파일 에러시 출력문구
	{
		printf("파일을 열지 못했습니다.\n");
		return 0;
	}
	
	while(!feof(fp))   // 파일 포인터가 끝까지 도달할때까지 반복하는 반복문
	{
		F_line = fgetc(fp);
		if(F_line == '\n')
			count++; // 데이터값 카운팅 증가값
	}
	count++; // 마지막 라인 카운트 증가

	tmep = (Animal *)malloc(sizeof(Animal)*count); // temp 구조체 배열 동적할당
	if ( tmep == NULL)      // 동적할당 오류시 조건
	{
		printf("동적 메모리 할당 오류\n"); // 동적할당 오류시 출력문구
		return 0;
	}
	
	rewind(fp); // 파일 포인터 초기화
	while(!feof(fp))   // 파일 포인터가 끝까지 도달할때까지 반복하는 반복문
	{
		// 구조체 배열의 변수값에 파일데이터값 대입
		fscanf(fp,"%s %s %s %s", tmep[i].animal, tmep[i].num, tmep[i].area, tmep[i].total);
		i++; // i값의 증가
	}

	printf("검색하실 조건을 선택하여 주십시오.\n");
	printf("< 1.종  2.고유번호  3.위치  4.개체 수 >\n");
	scanf("%d",&select);  // 검색할 조건을 입력후 select에 저장 

	printf("검색하실 정보를 입력하여 주십시오 : ");
	scanf("%s",&type);  // 검색할 정보를 입력후 type 배열에 저장 

	while( j < count)
	{
		if( ( strcmp(type , tmep[j].animal ) == 0 ) ) { // 종이 검색한 정보(type)와 같다면
			select = j; // j값을 select에 대입
			break;      // 반복문 탈출
		}
		if( ( strcmp(type , tmep[j].num ) == 0 ) )  { // 고유번호가 검색한 정보(type)와 같다면
			select = j; // j값을 select에 대입
			break;      // 반복문 탈출
		}
		if( ( strcmp(type , tmep[j].area ) == 0 ) ) { // 위치가 검색한 정보(type)와 같다면
			select = j;	// j값을 select에 대입
			break;     // 반복문 탈출
		}
		if( ( strcmp(type , tmep[j].total ) == 0 ) ) { // 개체 수가 검색한 정보(type)와 같다면
			select = j; // j값을 select에 대입
			break;      // 반복문 탈출
		}
		j++; // j값 증가
	}

	printf("종 : %s \n",tmep[select].animal);    // 해당 종 출력
	printf("고유번호 : %s \n",tmep[select].num); // 해당 고유번호 출력
	printf("위치 : %s \n",tmep[select].area);    // 해당 위치 출력
	printf("개체 수 : %s \n",tmep[select].total);// 해당 개체 수 출력
	
	free(tmep); // 동적 메모리 반납
	fclose(fp); // 파일을 닫아준다
	return 0;
}