///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 12월 4일
// 프로그램명   : 반복을 이용한 이진 탐색
//   설  명     : data.txt에 저장된 정수들을 P.509의 이진 탐색을 동적 할당을
//                이용한 배열로 구현하고 탐색하여 걸린 시간을 출력하라.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 전역변수 선언
int *list;

// 이진 탐색
int search_binary2(int key,int low, int high)
{
	int middle;

	while( low <= high ){
		middle = (low+high)/2;
		if(key == list[middle] ){
			return middle;
		}
		else if( key > list[middle] ){
			low = middle + 1;
		}
		else{
			high = middle-1;
		}
	}
	return -1;
}

int main()
{
	int num,s_num=0;   // 정수형 파일변수, 입력변수
	int count=0,i=0;   // 파일 데이터 갯수, 반복 변수
	clock_t start=0,finish=0; // 시간 시작지점, 마침지점
	double savetime=0;        // 시간 저장 변수
	// data2.txt 파일 읽기
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL)
	{
		printf("파일 에러\n");
		exit(1);
	}

	// list 동적할당
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	list = (int *)malloc(sizeof(int)*count);

	// list에 데이터값 대입
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		list[i] = num;
		i++;
	}

	// 입력
	printf("찾고자 하는 정수를 입력하세요 : ");
	scanf("%d",&s_num);

	// 탐색
	printf("\n<탐색 성공>\n");
	start = clock();       // 시작 시간
	search_binary2(s_num, 0, count-1);
	finish = clock();      // 종료 시간
	savetime = (double)(finish-start)/CLOCKS_PER_SEC; // 시간 계산

	for( i=0; i<count; i++){
		if(list[i] == s_num) break;
	}
	printf("%d 번째에 저장되어 있음\n",i);
	printf("이진탐색 실행 속도 : %lf\n",savetime);

	fclose(fp); // 파일을 닫습니다
	free(list); // 할당 반납
	return 0;
}