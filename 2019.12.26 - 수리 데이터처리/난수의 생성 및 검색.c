///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 3일
// 프로그램명   : 난수의 생성 및 검색
//   설  명     : 사용자로부터 2중 배열의 크기를 입력 받고 동적으로
//                생성하여 배열에 1~100까지의 난수를 저장한다. 이후
//                사용자가 1~100까지 중 임의의 숫자를 입력하면
//                배열에서 해당 숫자가 있는지 검색하고 있다면 그 숫자가
//                몇행 몇열에 있는지 출력하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h> // malloc을 쓰기위한 라이브러리 함수

int main()
{
	int row,col;  // 행,열 변수
	int **temp;   // 이차원 동적할당 배열 선언
	int i,j;      // 반복문 증가값 변수
	int find_num; // 찾는 수를 입력받을 변수
	int not_num=0;// 입력받은 숫자가 없을시 증가값 변수

	printf("행과 열의 크기를 입력하시오 : "); // 행과 열 크기를 입력받을 변수
	scanf("%d %d",&col,&row); // 행과 열을 입력
	printf("\n");

	temp = (int**) malloc(sizeof(int *) * row); // temp 이차원 배열 동적할당
	for(i = 0; i < row; i++)  // 행을 범위값 가지는 반복문
	{
		temp[i] = (int*) malloc(sizeof(int ) * col); // 행만큼 열을 할당
	}

	for( i = 0; i< row; i++) // 행 반복문
	{
		for( j= 0; j< col; j++) // 열 반복문
		{
			temp[i][j] = rand()%100; // 난수생성하여 temp[][] 이차원배열에 대입
		}
	}
	printf("난수 생성 완료 !\n"); // 난수 생성문구 출력
	printf("\n");

	printf("검색할 숫자를 입력하시오(1~100) : "); // 검색할 숫자 입력 문구 출력
	scanf("%d",&find_num); // 숫자 입력
	printf("\n");

	for( i = 0; i< row; i++) // 행 반복문
	{
		not_num++; // not_num의 증가
		for( j= 0; j< col; j++) // 열 반복문
		{
			if( temp[i][j] == find_num )	// 찾는 숫자와 동일할 경우
			{
				printf("검색하신 숫자 %d는 %d행 %d열에 있습니다.\n",find_num,i+1,j+1); // 찾는숫자, 행과 열 출력
				not_num=0; // not_num을 0으로 초기화
				goto exit; // goto문으로 exit로 이동
			}
		}
	}exit: // exit로 반복문 탈출

 	if( not_num != 0 ){ printf("검색하신 숫자 존재하지 않습니다.\n"); } // not_num이 0이 아니면 숫자가 없다는 문구 출력

	printf("\n");

	printf("저장된 행렬-----------\n");
	for( i = 0; i< row; i++) // 행 반복문
	{
		for( j= 0; j< col; j++) // 열 반복문
		{
			printf("%3d ",temp[i][j]);		// 난수가 저장된 행렬 출력
		}
		printf("\n");
	}

	for(i = 0; i < row; i++)  free(temp[i]); // temp 동적 이차원배열 할당한 값 반납 
	free(temp);
	return 0;
}