///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 3월 15일
// 프로그램명   : 숫자 계단 프로그램
//   설  명     : 줄의 개수를 입력받고 그에 맞게 출력하시오.(0~9까지숫자)
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	int len;      // 줄의 개수를 입력받을 변수
	int i,j,z;    // 반복문의 증가값을 나타낼 변수들

	printf("줄을 입력 : ");   // 줄을 입력하라는 문구 출력
	scanf("%d",&len);         // 줄의 개수를 입력

	for ( i = 1; i < len+1; i++)      // i=1부터 len+1만큼 반복해주는 for문
	{
		// 홀수 출력
		if( i % 2 == 1)               // i는 홀수번째의 위치조건
		{
			for( j = 1; j < i+1; j++) // j값을 호출해주는 반복문
			{ 
				if ( j % 2 == 1)      // j는 값이 홀수일 경우
				{
					printf("%d ",j%10);  // 일의자리 홀수 출력
				}
			}
		}
		// 짝수 출력
		if( i % 2 == 0)               // i는 짝수번째의 위치조건
		{
			for( z =1; z< i+1; z++)   // z값을 호출해주는 반복문
			{
				if ( z % 2 == 0)      // z는 값이 짝수일 경우
				{
					printf(" %d",z%10); // 일의자리 짝수 출력
				}
			}
		}
		printf("\n");
	}
	return 0;
}