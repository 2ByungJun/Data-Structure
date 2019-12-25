///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 3일
// 프로그램명   : 성적관리 프로그램
//   설  명     : 학생 별 학번,국어,영어,수학의 점수가 data.txt 파일에
//                저장되어 있다. 이 파일의 데이터를 읽어 들여 배열에
//                저장하고, 학생 별 총점과 평균, 각 과목별 평균 등을
//                평균으로 출력하는 프로그램을 작성하시오.
//                2중 배열을 동적으로 생성하여 저장하고 계산하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h> // malloc을 쓰기위한 라이브러리 함수

int main()
{
	int **temp;       // 이차동적배열 배열선언
	int i,j;          // 반복 증가값 변수
	int num;          // 파일 읽어주기 위한 변수
	int count=0;      // 열을 표현해주기 위한 카운트변수
	int sum=0;        // 총합을 저장할 변수
	double average=0; // 평균을 저장할 변수

	int korean_sum=0;     // 국어 총합
	int math_sum=0;       // 수학 총합
	int english_sum=0;    // 영어 총합
	int sum_sum=0;        // 함계 총합
	double average_sum=0; // 평균 총합

	FILE *fp = fopen("data1.txt","r");  // data1 파일 오픈 후 읽기
	if( fp == NULL)                     // 파일 에러시 출력
	{
		printf("파일이 열리지 않았습니다.\n");
		return 0;
	}

	while(!feof(fp)) // 파일을 끝까지 읽어주는 반복문
	{
		fscanf (fp,"%d",&num); // 파일을 num값으로 읽어준다.
		count++; // 카운트
	}

	temp = (int**) malloc(sizeof(int *) * 4); // temp 이차원 배열 동적 할당
	for(i = 0; i < 4; i++)  // 4는 행에 해당된다.
	{
		temp[i] = (int*) malloc(sizeof(int ) * count/4); // count/4값은 열에 해당된다.
	}


	rewind(fp); // 파일포인터 초기화
	while(!feof(fp)) // 파일을 끝까지 읽어주는 반복문
	{
		for(j=0; j<count/4; j++) // temp[][] 배열에 파일data1.txt에 있는 수 대입
		{
			for(i=0; i<4; i++)
			{
				fscanf(fp,"%d",&temp[j][i]); // 파일에 있는 정수를 하나씩 temp 이차원배열에 대입
			}
		}
	}

	printf("|=============================================|\n");
	printf("| 학  번 | 국어 | 영어 | 수학 | 총 점 | 평 균 |\n");
	for(i=0; i<count/4; i++) // 열의 반복문
	{
		for(j=0; j<6; j++) // 0~5까지 다섯번 반복하는 것으로 행을 표현한 반복문이다.
		{
			if( j == 0 ) // 0학번을 출력할 조건문
			{
				printf("|%d",temp[i][j]); // 학번 출력
			}
			else if( 1 <= j && j < 4 ) // 1국어,2수학,3영어 를 출력할 조건문
			{
				printf("|  %d  ",temp[i][j]); // 국어,수학,영어 출력

			}
			else if( j == 4 ) // 4총점을 출력할 조건문
			{
				sum = temp[i][1] + temp[i][2] + temp[i][3]; // sum의 값에 국어,수학,영어 값을 더해준다.
				printf("|  %d  ",sum); // sum출력
			}
			else if( j == 5 ) // 5평균을 출력할 조건문
			{
				average = (double)sum /3; // sum의 값을 3으로 나눠서 double형으로 형변환시켜 대입한다.
				printf("| %.2f |",average); // %.2f는 반올림하여 소수점 둘째자리까지 출력시켜주는 형식지정자이다.
			}
		}
		// 열 count/4 반복문에만 포함되있는 수식
		korean_sum = korean_sum + temp[i][1];   // 국어 누적 총합
		math_sum = math_sum + temp[i][2];       // 수학 누적 총합
		english_sum = english_sum + temp[i][3]; // 영어 누적 총합
		sum_sum = sum_sum + sum;                // 총점 누적 총합
		average_sum = average_sum + average;    // 평균 누적 총합
		sum = 0;  // 다른 학번에 해당하는 sum값을 위해 sum값을 초기화 해준다
		printf("\n");
	}
	printf("|========|======|======|======|=======|=======|\n");
	printf("| 평  균 |  %d |  %d |  %d |  %d  | %.2f|\n",korean_sum, math_sum,english_sum,sum_sum,average_sum); // 누적 총합 출력
	printf("|========|======|======|======|=======|=======|\n");
	

	//for(i = 0; i < 4; i++)   // 이차원 동적메모리할당을 반납해준다.
	//    free(temp[i]);
	free(temp);

	fclose(fp); // 파일 닫기


	return 0;
}