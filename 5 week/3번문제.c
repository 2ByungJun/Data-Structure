///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 6일
// 프로그램명   : 재귀함수를 이용한 데이터 처리
//   설  명     : data.txt파일에 p64의 15번 문제와 같이 n이 입력되어
//                있을때 다음을 계산하는 프로그램을 순환과 반복문으로
//                작성하고 시간을 측정하시오.
//                1 + 1/2 + 1/3 + 1/4 +... + 1/n
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <time.h>    // 시간을 재기위한 라이브러리 함수


double data_file(double n) // 1 + 1/2 + 1/3 + ... + 1/n 값을 계산하는 재귀함수
{
	if ( n > 0 )
	{
		return (double)1/n + data_file(n-1); // n > 0 경우 1/n값과 data_file함수를 n-1 상태로 리턴
	}
	if ( n == 0 )
		return 0;   // n == 0 일 경우 0을 리턴
}

int main()
{
	clock_t start,finish;  // 시간을 재는 시작과 마침의 변수 선언
	double duration;       // 시간차이를 저장하는 변수
	double n;           // 파일 데이터 값을 저장할 변수
	int i;           // 반복 증가값 변수
	double sum;      // 합을 누적시키는 실수형 변수

	FILE *fp = fopen("data3.txt","r"); // data3.txt 파일을 읽기형식으로 오픈
	if(fp == NULL)                     // 파일이 열리지 않았을 시 에러문구 출력
	{
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}

	while(!feof(fp))   // 파일을 끝까지 읽어주는 반복문
	{
		fscanf(fp,"%lf",&n);  // 파일 데이터 값을 n값에 대입한다 
		sum = 0;             // sum 값을 0으로 초기화

		// 순환식
		printf("순환식\n\n");
		start = clock();      // 시간재기를 시작한다

		printf("결과 값 = %lf\n",data_file(n)); // 함수 결과값 출력

		finish = clock();    // 시간재기를 마친다
		duration = (double)(finish - start) / CLOCKS_PER_SEC;  // 시간 차이 값을 초단위로 출력
		printf("%lf 초입니다.\n\n", duration); // 시간을 출력

		// 반복식
		printf("반복식\n\n");
		start = clock();      // 시간재기를 시작한다

		for( i=1; i<=n; i++)  // n값만큼 반복하는 반복문
		{
			sum += (double)1/i;    // 1/i값을 double로 형변환 시켜 sum값에 누적 대입
		}
		printf("결과 값 = %lf\n",sum);

		finish = clock();    // 시간재기를 마친다
		duration = (double)(finish - start) / CLOCKS_PER_SEC;  // 시간 차이 값을 초단위로 출력
		printf("%lf 초입니다.\n\n", duration); // 시간을 출력
		printf("-----------------------------------\n");
	}

	fclose(fp); // 파일 닫기
	return 0;
}