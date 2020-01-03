///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 6일
// 프로그램명   : 재귀함수를 이용한 데이터 처리
//   설  명     : data.txt파일에 있는 x와 n을 이용하여 숫자 x의
//                n거듭제곱 값인 x^n을 반복문과 순환으로 작성하고 시간을
//                구하는 프로그램을 작성하시오
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>    // 시간을 재기위한 라이브러리 함수

int data_file(double x ,int n) // x * x * x...(n의개수만큼) 값을 계산하는 재귀함수
{
	if ( n > 0)
	{
		return (int)x * data_file ( x , n-1 ); // n > 0 경우 x값을 곱하며 data_file함수를 n-1 상태로 리턴
	}

	if ( n == 0 )
		return 1;    // n == 0 일 경우 1을 리턴
}                                                    

int main()
{
	clock_t start,finish;  // 시간을 재는 시작과 마침의 변수 선언
	double duration;       // 시간차이를 저장하는 변수
	double x;
	int n;                // 파일에서 입력받을 x와 n 변수 선언
	int i;                 // 반복 증가값 변수
	int mul;               // 곱을 누적시킬 변수

	FILE *fp = fopen("data4.txt","r"); // data4.txt 파일을 읽기형식으로 오픈
	if(fp == NULL)                     // 파일이 열리지 않았을 시 에러문구 출력
	{
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}

	while(!feof(fp))   // 파일을 끝까지 읽어주는 반복문
	{
		fscanf(fp,"%lf %d",&x,&n);  // 파일 데이터 값을 x,n값에 대입한다 
		mul = 1;       // mul값을 1로 초기화

		// 순환식
		printf("순환식\n\n");
		start = clock();       // 시간재기를 시작한다

		printf("결과 값 = %d\n",data_file(x,n)); // 함수 결과값 출력

		finish = clock();    // 시간재기를 마친다
		duration = (double)(finish - start) / CLOCKS_PER_SEC;  // 시간 차이 값을 초단위로 출력
		printf("%lf 초입니다.\n\n", duration); // 시간을 출력

		//반복식
		printf("반복식\n\n");
		start = clock();       // 시간재기를 시작한다

		for( i=0; i<n; i++)  // n값만큼 반복하는 반복문
		{
			mul = mul * (int)x;   // mul값에 x값을 곱으로 누적시킨다
		}
		printf("결과 값 = %d\n",mul); // mul값을 출력

		finish = clock();    // 시간재기를 마친다
		duration = (double)(finish - start) / CLOCKS_PER_SEC;  // 시간 차이 값을 초단위로 출력
		printf("%lf 초입니다.\n\n", duration); // 시간을 출력
		printf("-----------------------------------\n");
	}

	fclose(fp); // 파일 닫기
	return 0;
}