///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 3일
// 프로그램명   : 행렬의 계산
//   설  명     : Data.txt 파일에 있는 3개의 행렬을 각각 동적으로 만든
//                2중 배열에 저장하고 저장된 식을 가져와 계산하고 출력.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h> // malloc을 쓰기위한 라이브러리 함수

int main()
{
	int row1,col1; // 1행렬의 행과 열
	int row2,col2; // 2행렬의 행과 열
	int row3,col3; // 3행렬의 행과 열
	char name1,name2,name3; // 행렬의 이름을 파일에서 읽어 저장할 변수
	char cal[10]; // 행렬의 연산을 읽어서 저장시킬 배열

	int **tempA; // A행렬의 이차원동적할당배열
	int **tempB; // B행렬의 이차원동적할당배열
	int **tempC; // C행렬의 이차원동적할당배열
	int **sum_temp; // 행렬의 연산을 저장할 이차원동적할당 배열선언
	int i,j,z;  // 반복문 증가값 변수
	char fpline[5]; // 파일 포인터의 줄 위치를 변경해줄 배열선언

	FILE *fp = fopen("data3.txt","r"); // data3 파일을 오픈 후 읽음
	if(fp==NULL)                       // 파일 에러시 출력 문구
	{
		printf("파일을 열지 못했습니다.\n");
		return 0;
	}

	// A 행렬 ( 행렬의 이름을 간편하게 A로 설정하여 주석을 달았습니다. )
	fscanf( fp , "%c%d%d",  &name1 , &row1, &col1 ); // 파일 첫째 줄을 읽어 행렬의 이름과 크기를 각 변수에 저장
	if ( row1 != col1 ){                             // 행과 열이 다를 시 출력 문구
		printf("행렬의 크기가 맞지 않습니다!\n");
		return 0;
	}
	printf("%c행렬 ======================================\n",name1); // name1(=A) 행렬 출력
	tempA = (int**) malloc(sizeof(int *) * row1);  // tempA 이차원 동적 메모리 할당
	for(i = 0; i < row1; i++)   // 행크기만큼 반복문
	{
		tempA[i] = (int*) malloc(sizeof(int ) * col1); // 열만큼 동적 메모리 할당
	}
	// tmepA 행렬의 표현
	for(i=0; i<row1; i++)       // tempA 행렬을 파일에서 받아오는 반복문
	{
		for(j=0; j<col1; j++)
		{
			fscanf(fp,"%d",&tempA[i][j]);
		}
	}
	for(i=0; i<row1; i++)       // tempA 행렬을 출력해주는 반복문
	{
		for(j=0; j<col1; j++)
		{
			printf("%3d      ",tempA[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // 현재 파일커서의 위치가 A행렬의 마지막위치니 B행렬의 시작지점으으로 줄바꾸기 위함

	// B 행렬 ( 행렬의 이름을 간편하게 B로 설정하여 주석을 달았습니다. )
	fscanf( fp , "%c%d%d",  &name2 , &row2, &col2 ); // 파일 첫째 줄을 읽어 행렬의 이름과 크기를 각 변수에 저장
	if ( row2 != col2 ){                             // 행과 열이 다를 시 출력 문구
		printf("행렬의 크기가 맞지 않습니다!\n");
		return 0;
	}
	printf("%c행렬 ======================================\n",name2 ); // name2(=B) 행렬 출력
	tempB = (int**) malloc(sizeof(int *) * row2);  // tempB 이차원 동적 메모리 할당
	for(i = 0; i < row2; i++)   // 행크기만큼 반복문
	{
		tempB[i] = (int*) malloc(sizeof(int ) * col2); // 열만큼 동적 메모리 할당
	}
	// tmepB 행렬의 표현
	for(i=0; i<row2; i++)       // tempB 행렬을 파일에서 받아오는 반복문
	{
		for(j=0; j<col2; j++)
		{
			fscanf(fp,"%d",&tempB[i][j]);
		}
	}
	for(i=0; i<row2; i++)       // tempB 행렬을 출력해주는 반복문
	{
		for(j=0; j<col2; j++)
		{
			printf("%3d      ",tempB[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // 현재 파일커서의 위치가 B행렬의 마지막위치니 C행렬의 시작지점으으로 줄바꾸기 위함

	// C 행렬 ( 행렬의 이름을 간편하게 C로 설정하여 주석을 달았습니다. )
	fscanf( fp , "%c%d%d",  &name3 , &row3, &col3 ); // 파일 첫째 줄을 읽어 행렬의 이름과 크기를 각 변수에 저장
	if ( row3 != col3 ){                             // 행과 열이 다를 시 출력 문구
		printf("행렬의 크기가 맞지 않습니다!\n");
		return 0;
	}
	printf("%c행렬 ======================================\n",name3); // name3(=C) 행렬 출력
	tempC = (int**) malloc(sizeof(int *) * row3);  // tempC 이차원 동적 메모리 할당
	for(i = 0; i < row3; i++)    // 행크기만큼 반복문
	{
		tempC[i] = (int*) malloc(sizeof(int ) * col3); // 열만큼 동적 메모리 할당
	}
	// tmepC 행렬의 표현
	for(i=0; i<row3; i++)       // tempC 행렬을 파일에서 받아오는 반복문
	{
		for(j=0; j<col3; j++)
		{
			fscanf(fp,"%d",&tempC[i][j]);
		}
	}
	for(i=0; i<row3; i++)       // tempC 행렬을 출력해주는 반복문
	{
		for(j=0; j<col3; j++)
		{
			printf("%3d      ",tempC[i][j]);
		}
		printf("\n");
	}
	fgets( fpline, sizeof(fpline), fp); // 현재 파일커서의 위치가 C행렬의 마지막위치니 행렬 연산의 시작지점으으로 줄바꾸기 위함

	// 행렬 연산
	while(!feof(fp)) // C행렬을 읽은 시점부터 끝까지 파일을 읽어준다
	{
		fscanf(fp , "%s", &cal); // fscanf로 수식을 읽어준다.
		printf("%s행렬 ======================================\n",cal); // 읽은 수식cal을 출력
		sum_temp = (int**) malloc(sizeof(int *) * row1); // 행렬의 합과차를 계산하여 저장할 sum_temp 이차원배열 동적할당선언
		for(i = 0; i < row1; i++)  // 행크기만큼의 반복문
		{
			sum_temp[i] = (int*) malloc(sizeof(int ) * col1); // 열만큼 동적 메모리 할당
		}
		for(i=0; i<row1; i++) // 행 크기만큼의 반복문
		{
			for(j=0; j<col1; j++) // 열 크기만큼의 반복문
			{
				// 수식의 첫번째 행렬로 set_temp행렬을 초기화
				if( cal[0] == 'A' ){ 
					sum_temp[i][j] = tempA[i][j];}
				if( cal[0] == 'B' ){
					sum_temp[i][j] = tempB[i][j];}
				if( cal[0] == 'C' ){
					sum_temp[i][j] = tempC[i][j];}
				
				for( z=1; z<10; z++) // cal[] 배열을 읽기 위한 반복문
				{
					if( cal[z] == '+' ) // cal 배열이 +가 나올 조건
					{
						// z+1로 선언하여 다음 행렬과 연산하여 sum_temp에 합을 누적시키는 조건문
						if( cal[z+1] == 'A' ){
							sum_temp[i][j] = sum_temp[i][j] + tempA[i][j];}
						else if( cal[z+1] == 'B' ){
							sum_temp[i][j] = sum_temp[i][j] + tempB[i][j];}
						else if( cal[z+1] == 'C' ){
							sum_temp[i][j] = sum_temp[i][j] + tempC[i][j];}
					}
					if( cal[z] == '-') // cal 배열이 -가 나올 조건
					{	
						// z+1로 선언하여 다음 행렬과 연산하여 sum_temp에 차를 누적시키는 조건문
						if( cal[z+1] == 'A' ){
							sum_temp[i][j] = sum_temp[i][j] - tempA[i][j];}
						else if( cal[z+1] == 'B' ){
							sum_temp[i][j] = sum_temp[i][j] - tempB[i][j];}
						else if( cal[z+1] == 'C' ){
							sum_temp[i][j] = sum_temp[i][j] - tempC[i][j];}
					}			
				}	
			}
		}
		for (i=0; i< row1; i++) // 행크기만큼의 반복문
		{
			for(j=0; j<col1; j++) // 열크기만큼의 반복문
			{
				printf("%3d      ",sum_temp[i][j]); // sum_temp 행렬을 출력
			}
			printf("\n");
		}
	}
	for(i = 0; i < row1; i++)  free(temp[i]); // tempA 이차원 동적메모리할당을 반납
	free(tempA);
	for(i = 0; i < row2; i++)  free(temp[i]); // tempB 이차원 동적메모리할당을 반납
	free(tempB);
	for(i = 0; i < row3; i++)  free(temp[i]); // tempC 이차원 동적메모리할당을 반납
	free(tempC);
	for(i = 0; i < row1; i++)  free(temp[i]); // sum_temp 이차원 동적메모리할당을 반납
	free(sum_temp);

	fclose(fp); // 파일 닫기
	return 0;
}