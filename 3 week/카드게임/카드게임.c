///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 3월 26일
// 프로그램명   : 카드게임
//   설  명     : A와 B가 카드게임을 한다. A와 B가 가진 카드의 개수와
//                숫자의 정보는 data.txt파일에 저장되어있다.
//                각자 하나의 카드를 내고 A가 승리하는 모든 경우의 수를
//                출력하여라. (단,동적 할당을 이용하여 배열에 저장할 것)
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int *temp1;  // A카드 배열
	int *temp2;  // B카드 배열
	char people; // A,B 문자를 읽어주기 위한 변수
	char fpline[5];   // 파일 문장 라인을 조절해주는 함수
	int num;     // 카드 개수를 count하기위한 변수
	int count1=0,count2=1; // A카드 개수 , B카드 개수
	int i,j;     // 반복문 증가값 변수

	FILE *fp = fopen("data.txt","r"); // 파일 변수를 선언하며 data.txt파일을 읽기형식으로 연다.

	while(!feof(fp)) // count1의 값을 구하는 위해 파일을 끝까지 읽어준다.
	{	
		fscanf(fp,"%c %d",&people,&num);  // 파일의 문자와 정수들을 읽어준다
		if ( people  == 'A')              // A문자가 나올 시 이하내용을 취소하고 재반복하는 조건
			continue;                    
		if ( people  == 'B')              // B문자가 나올 시 반복을 멈춘다 
			break;
		count1++;	                      // A카드의 개수인 count1의 증가
	}
	while(!feof(fp)) // count2의 값을 구하는 위해 파일을 끝까지 읽어준다.
	{
		fscanf(fp,"%d",&num);             // 파일의 숫자를 읽어준다
		count2++;                         // B카드의 개수인 count2의 증가
	}
	
	// A카드를 저장할 배열의 동적 메모리 할당
	temp1 = (int *)malloc(count1*sizeof(int));
	if ( temp1 == NULL )          // temp1 배열 동적메모리 에러시 출력하는 조건
	{
		printf("temp1 동적 메모리 할당 오류\n");
		exit(1);
	}
	// B카드를 저장할 배열의 동적 메모리 할당
	temp2 = (int *)malloc(count2*sizeof(int));
	if ( temp2 == NULL )          // temp2 배열 동적메모리 에러시 출력하는 조건
	{
		printf("temp2 동적 메모리 할당 오류\n");
		exit(1);
	}

	rewind(fp);  // 파일을 초기화해준다.
	printf("A의 카드 {");
	fgets( fpline, sizeof(fpline), fp);  // 파일의 첫 줄을 읽어준 후 둘째 줄로 이동한다
	for ( i=0; i<count1; i++)            // count1까지 반복하는 A카드 출력반복문
	{
		fscanf(fp,"%d",&temp1[i]);       // temp1배열에 A카드 파일에 있는 정수들을 입력받는다
		printf(" %d ",temp1[i]);         // A카드 출력
	}
	printf("}\n");

	printf("B의 카드 {");
	fgets( fpline, sizeof(fpline), fp);  // 파일의 둘째 줄에서 셋째 줄로 이동한다
	fgets( fpline, sizeof(fpline), fp);  // 파일의 셋째 줄에서 넷째 줄로 이동한다
	for ( i=0; i<count2; i++)            // count2까지 반복하는 B카드 출력반복문 
	{
		fscanf(fp,"%d",&temp2[i]);       // temp2배열에 B카드 파일에 있는 정수들을 입력받는다
		printf(" %d ",temp2[i]);         // B카드 출력
	}
	printf("}\n\n");

	printf("< A가 이기는 경우의 수 >\n"); // A가 이기는 경우의 수를 출력한다
	for(i=0; i<count1; i++)        // A카드를 count1까지 반복하는 반복문
	{
		for( j=0; j<count2; j++)    // B카드를 count2까지 반복하는 반복문
		{
			if(temp1[i] > temp2[j]) // A카드를 기준으로 B카드가 변경되면서 A>B 경우의 조건식
			{
				printf("= A-%d  ,  B-%d =\n",temp1[i],temp2[j]); // A가 B보다 클 시 값들을 출력해준다
			}
		}
	}
  fclose(fp);   // fp파일을 닫아준다
  free(temp1);  // temp1 배열의 메모리를 반납한다
  free(temp2);  // temp2 배열의 메모리를 반납한다.
  return 0;
}