///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 3월 15일
// 프로그램명   : 별 출력 프로그램
//   설  명     : 첫 줄의 별의 개수를 입력 받고 입력된 값에 다라 출력하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>

int main(void)
{
	int i,k,z;         // 반복 변수
	int star;          // 별의 개수

	printf("첫 줄의 별의 개수를 입력하시오 : ");
	scanf("%d",&star);

	for ( i = 0; i < star-1; i++)   // 마지막 줄을 출력하지 않게 하기 위해서 조건식을 star-1로 표현하였다.
	{
		for( z=0; z < i; z++)       // 별을 호출하는 반복분
		{	
			printf(" ");
		}
		for( k=0; k < star-i; k++)  // 공백을 호출하는 반복문
		{	
			printf(" *");
		}
		printf("\n");
	}

     // 역순 호출
	for ( i = 1; i < star+1; i++)  // 마지막 한줄을 위해 조건식에 star+1로 표현하였다.
	{
		for( k=i; k < star; k++)   // 공백을 호출하는 반복문
		{
			printf(" ");
		}
		for( z=0; z < i; z++)      // 별을 호출하는 반복분
		{	
			printf(" *");
		}		
		printf("\n");
	}
	return 0;
}