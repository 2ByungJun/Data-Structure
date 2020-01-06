///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 16일
// 프로그램명   : 퀵 정렬 프로그램
//   설  명     : data3.txt에 저장되어 있는 데이터를 불러와
//                오름차순으로 정렬하여 출력하시오.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// 스왑 정의
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

int count=0; // 파일 데이터 개수(전역변수 선언)

// 분할 함수
// *list : 정렬할 배열
// left : 배열 처음을 나타내는 인덱스
// right : ( 배열 끝-1 )을 나타내는 인덱스
int partition(int *list,int left,int right)
{
	int pivot,temp;
	int low,high;
	int i;
	low = left;     // low를 처음위치로 설정
	high = right+1; // high는 배열의 끝을 설정
	pivot = list[left]; // pivot은 list 맨 앞으로 설정
	printf("-Pivot : %d-\n",pivot);
	do{
		do{ // low가 right보다 작고 list[low]값이 pivot보다 작을 시
			low++; // low 증가
		}while(low <= right && list[low]<pivot);

		do{ // high가 left보다 크고 list[high]값이 pivot보다 클 시
			high--; // high 감소
		}while(high >= left && list[high]>pivot);

		// list[low]가 기존에 가르쳤던 pivot을 가르킬 시 over
		if( list[low] != 15 )
			printf("low:%d  ",list[low]);
		else
			printf("low:over  ");
		printf("high:%d  ",list[high]);

		// 정렬 실시간 출력문
		printf("[");
		for(i=left; i<=right; i++)
			printf("%d > ",list[i]);
		printf("]\n\n");

		// low가 high보다 작을경우 데이터값 스왑
		if(low<high){
			SWAP(list[low],list[high],temp);

		}
	}while(low<high);

	// pivot 재설정을 위한 스왑
	SWAP(list[left],list[high],temp);
	return high;
}

// 퀵 정렬
void quick_sort(int *list,int left,int right)
{
	if(left<right){
		int q=partition(list,left,right); // 분할
		quick_sort(list,left,q-1);  // 왼쪽 정렬
		quick_sort(list,q+1,right); // 오른쪽 정렬
	}
}

int main()
{
	int *temp;    // 정수형 temp 동적배열 생성
	int num;      // 파일 데이터값 정수를 받아 올 변수
	int i=0;      // 반복변수
	// 파일 오픈
	FILE *fp= fopen("data3.txt","r");
	if(fp == NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 파일 데이터 개수체크
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	// 동적 할당
	temp = (int *)malloc(sizeof(int)*count);

	// 파일포인터 리셋
	rewind(fp);
	// temp[i]에 파일 데이터값 대입
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		temp[i] = num;
		i++;
	}

	// 정렬되지 않은 리스트 출력
	printf("< 정렬되지 않은 리스트 >\n");
	for(i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n\n");

	// 퀵정렬 사용
	printf("< 정렬 과정>\n");
	quick_sort(temp,0,count-1);
	
	// 정렬된 리스트 출력
	printf("< 정렬된 리스트 >\n");
	for(i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n");

	free(temp); // temp 동적반납
	fclose(fp); // fp 파일을 닫습니다.
	return 0;
}