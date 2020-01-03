///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 10일
// 프로그램명   : 구조체 활용
//   설  명     : 정적으로 할당된 구조체를 작성하여 각 변수 파일에 저장된
//                임의의 값을 저장하는 프로그램을 작성하시오
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>      // 문자열을 다루는 라이브러리 함수

struct People   // People 구조체 생성
{
	char name[20];       // 이름
	char N_number[20];   // 주민번호
	char birth[20];      // 생년월일
	char P_number[20];   // 전화번호
	char area[20];       // 주소
};

int main()
{
	struct People people[5];  // 구조체 People를 가지는 people[5] 구조체 정적배열 생성
	int i = 0 , j;        // 반복문 증가값 변수

	FILE *fp = fopen("data1.txt","r"); // data1.txt파일을 읽기형식으로 오픈
	if(fp == NULL)                     // 파일 에러시 출력문구
	{
		printf("파일을 열지 못했습니다.\n");
		return 0;
	}

	while(!feof(fp))  // 파일 포인터가 끝까지 도달할때까지 반복하는 반복문
	{
		// 구조체 배열의 변수값에 파일데이터값 대입
		fscanf(fp,"%s %s %s %s %s", people[i].name, people[i].N_number, people[i].birth, people[i].P_number, people[i].area);
		i++; // i값 증가 ( 구조체 배열값 카운팅 )
	}

	for ( j=0; j<i; j++)  // 구조체 배열값의 크기만큼 반복해주는 반복문
	{
	printf("=================================\n");
	printf("이름 : %s \n",people[j].name);         // 이름 출력
	printf("주민번호 : %s \n",people[j].N_number); // 주민번호 출력
	printf("생년월일 : %s \n",people[j].birth);    // 생년월일 출력
	printf("전화번호 : %s \n",people[j].P_number); // 전화번호 출력
	printf("주소 : %s \n\n",people[j].area);       // 주소 출력
	}
	fclose(fp);  // 파일을 닫아준다


	return 0;
}