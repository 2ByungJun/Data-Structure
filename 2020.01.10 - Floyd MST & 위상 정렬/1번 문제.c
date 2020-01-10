///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 20일
// 프로그램명   : Floyd의 최단 경로 알고리즘
//   설  명     : p451를 참조하여 Floyd의 최단 경로 프로그램을 참고하여
//                모든 결과를 순서에 맞게 출력하는 프로그램
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define INF 1000

int **A;         // Floyd를 사용할 임시배열
int **weight;    // 메인 배열(행렬)
int max_num = 0; // 정점 개수

// Floyd
void floyd(int n)
{
	int i,j,k; // 반복 변수
	int row=0; // 0~6 출력

	// A에 weight 복사
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			A[i][j] = weight[i][j];

	// 작을경우 재대입하는 과정
	for(k=0; k<n; k++)
	{
		// 양식
		printf("< %d번 정점 열림 >\n  ",k);
		// 행 숫자 표시
		while(row < max_num){
			printf(" %2d ",row);
			row++;
		}
		row=0;
		printf("\n");
		printf(" |---------------------------|\n");
		// 행 부분 반복
		for(i=0; i<n; i++)
		{
			// 열 숫자 표시
			printf("%d|",i);
			// 열 부분 반복
			for(j=0; j<n; j++)
			{
				if(A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					printf("*%2d|",A[i][j]);     // 변경된 값 *출력 
				}
				else
				{
					if( A[i][j] == INF ) // INF일 경우는 x출력
						printf(" %2 x|");
					else
						printf(" %2d|",A[i][j]); // 아닐 경우 가중치 출력
				}
			}
		printf("\n");
		}
		printf(" |---------------------------|\n\n");
	}
}

int main()
{
	char ch;     // v ,e 판단
	int num;     // 정점
	int num_x;   // 정점 x 
	int num_y;   // 정점 y
	int num_add; // 가중치
	int i,j;     // 반복 변수
	int row=0;   // 행 숫자 표시

	// 파일 변수 fp
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}

	// max_num 값 (파일개수 값) 구하기
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v'){
			fscanf(fp, "%d", &num);
			max_num++;  // 0 ~ 6
		}
	}

	// 동적 할당
	weight = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<max_num; i++){
		weight[i] = (int *)malloc(sizeof(int)*max_num);
	}
	A = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<max_num; i++){
		A[i] = (int *)malloc(sizeof(int)*max_num);
	}

	// 배열 초기화
	for( i=0; i<max_num; i++){
		for( j=0; j<max_num; j++){
			if( i == j ) // i = j는 0으로 초기화
				weight[i][j] = 0;
			else         // 나머진 INF로 초기화
			    weight[i][j] = INF;
		}
	}

	// weight 배열(행렬) 형성
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v' )             // 의미없는 수식
			fscanf(fp, "%d", &num);
		if( ch == 'e' ){
			fscanf(fp,"%d %d %d",&num_x, &num_y, &num_add);
			weight[num_x][num_y] = num_add; 
			weight[num_y][num_x] = num_add;
		}
	}

	// 초기 상태 
	printf("< 초기 상태 >\n  ");
	// 행 숫자 표시
	while(row < max_num){
		printf(" %2d ",row);
		row++;
	}
	printf("\n");
	printf(" |---------------------------|\n");
	// 행 반복
	for( i=0; i<max_num; i++){
		// 열 숫자 표시
		printf("%d|",i);
		// 열 반복
		for( j=0; j<max_num; j++){
			if( weight[i][j] == INF ) // INF일 경우 x로 출력
				printf(" %2 x|");
			else                      // 나머진 숫자 출력
				printf("*%2d|",weight[i][j]);
		}
		printf("\n");
	}
	printf(" |---------------------------|\n");

	// Floyd 실행
	floyd(max_num);

	// 동적 할당 반납
	for(i=0; i<max_num; i++) free(weight[i]);
	free(weight);
	for(i=0; i<max_num; i++) free(A[i]);
	free(A);

	// 파일을 닫아준 후 종료
	fclose(fp);
	return 0;
}