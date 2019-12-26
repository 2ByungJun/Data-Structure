///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 6일
// 프로그램명   : 데이터 처리
//   설  명     : data.txt파일의 숫자 데이터를입력 받아 산술 평균,
//                조화 평균, 기하 평균을 구하는 프로그램을 함수로
//                작성하라.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>        // malloc를 사용하기 위한 라이브러리 함수 선언
#include <math.h>          // pow연산과 sqrt연산을 사용하기 위한 라이브러리 함수 선언

double Sansul( int count , int *temp )  // 산술기하 함수
{
	int i;           // 반복 증가값 변수
	double sansul=0; // 산술 실수형 변수 선언

	for( i=0; i<count; i++ ) // count까지 반복
	{
		sansul += temp[i];   // sansul변수에 temp[i]값을 순서대로 누적(합)시킨다
	}
	return sansul / count;   // 덧셈값을 count값으로 나눠 산술기하 값을 리턴
}

double Giha ( int count , int *temp )   // 기하평균 함수
{
	int i;          // 반복 증가값 변수
	double giha=0;  // 기하값을 실수형으로 변수 선언

	for( i=0; i<count; i++ )  // count까지 반복
	{
		giha += pow(temp[i],2); // pow연산을 사용해 temp[i]의 2승(temp[i]^2)을 누적(합)시킨다
	}
	return sqrt(giha); // sqrt값으로 giha값에 루트를 씌어 리턴
}

double Johaw ( int count , int *temp )   // 조화평균 함수
{
	int i;          // 반복 증가값 변수
	double johaw=0; // 조화값을 실수형으로 변수 선언

	for( i=0; i<count; i++ ) // count까지 반복
	{
		johaw += (double)1/temp[i]; // 조화값에 분모부분을 실수형으로 누적(합)시킨다
	}
	return count/johaw; // 조화평균값을 리턴
}

int main() 
{
	int *temp;    // 파일값을 대입시킬 동적메모리 배열 선언
	int i;        // 반복 증가값 변수
	int file_num; // count값을 구하기위해 파일을 읽어올 변수
	int count=0;  // 파일 데이터 수를 세기 위한 변수

	FILE *fp = fopen("data1.txt","r");  // data1.txt 파일 읽기형식으로 오픈
	if(fp == NULL)                      // 파일이 열리지 않을 시 에러문구 출력
	{
		printf("파일을 열지 못했습니다.\n");
		return 0;
	}

	while(!feof(fp))   // 파일 포인터가 끝까지 위치할 때까지의 반복문
	{
		fscanf(fp ,"%d", &file_num); // file_num변수로 정수 데이터들을 읽어준다
		count++; // count값 증가
	}

    temp = (int *)malloc(sizeof(int)*count); // temp배열 동적 메모리 할당
	if(temp == NULL) // 동적메모리 할당 에러시 문구 출력 후 종료
	{
		printf("동적 메모리 할당 오류\n");
		return 0;
	}

	rewind(fp);      // 파일 포인터위치를 초기화
	while(!feof(fp)) // 파일 끝까지 반복해주는 반복문
	{
		for ( i = 0; i<count; i++)    // count까지 반복하는 반복문
		fscanf(fp ,"%d", &temp[i] );  // 파일 데이터 값을 temp[i]배열에 순서대로 대입
	}

		printf("산술평균=======================\n\n");
		printf("산술평균 값 : %lf\n\n", Sansul(count, temp));  // 산술기하 함수에서 연산 후 리턴 값을 출력

		printf("기하평균=======================\n\n");
		printf("기하평균 값 : %lf\n\n", Giha(count, temp));    // 기하평균 함수에서 연산 후 리턴 값을 출력
		
		printf("조화평균=======================\n\n");
    	printf("조화평균 값 : %lf\n\n", Johaw(count , temp));  // 조화평균 함수에서 연산 후 리턴 값을 출력

	fclose(fp); // 파일을 닫아준다
	free(temp); // temp의 동적메모리를 반납
	
	return 0;
}