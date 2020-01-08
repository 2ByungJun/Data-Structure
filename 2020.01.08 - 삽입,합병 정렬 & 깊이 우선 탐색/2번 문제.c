///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 11월 2일
// 프로그램명   : 합병 정렬 프로그램
//   설  명     : data2.txt에 저장되어 있는 데이터를 불러와 오름차순 정렬
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

int *sorted; // 합병정렬 임시공간 배열

// 합병 정렬
// list   : 정렬시킬 배열
// left   : 부분 배열의 첫 레코드
// mid    : 분할 기점
// right  : 부분 배열의 마지막 레코드
void merge(int *list,int left,int mid,int right)
{
	int i,j,k,l;
	i=left; j=mid+1; k=left;

	/*분할 정렬된 list의 합병*/
	while(i<=mid && j<=right){
		if(list[i]<=list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if(i>mid) // 남아 있는 레코드의 일괄 복사
		for(l=j; l<=right; l++)
			sorted[k++] = list[l];
	else
		for(l=i; l<=mid; l++)
			sorted[k++] = list[l];
	// 배열 sorted[]의 리스트를 배열 list[]로 재복사
	for(l=left; l<=right; l++)
		list[l] = sorted[l];
}
// list : 정렬시킬 배열
// left : 부분 배열의 첫 레코드
// right : 부분 배열의 마지막 레코드 (함수 사용하기 위해 right값은 배열 MAX_SIZE-1로 받는다.)
void merge_sort(int *list,int left,int right)
{
	int mid;
	int i;
	if(left<right){
		mid = (left+right)/2;         // 리스트 균등 분할
		merge_sort(list,left,mid);    // 부분 리스트 정렬
		merge_sort(list,mid+1,right); // 부분 리스트 정렬
		// 왼쪽 부분 리스트 출력
		printf("\nLeft list : ");     
		for( i = left; i<=mid; i++)
			printf("%d ",list[i]);
		// 오른쪽 부분 리스트 출력
		printf("\nRight list : ");    
		for( i = mid+1; i<=right; i++)
			printf("%d ",list[i]);

		merge(list,left,mid,right);   // 합병
		// 합병결과 출력
		printf("\nSorted list : ");   
		for( i = left; i<=right; i++)
			printf("%d ",list[i]);

		printf("\n");
	}
}

// 출력
// list : 출력시킬 배열
// count: 파일데이터 개수
void dispaly(int *list,int count)
{
	int i;
	for( i=0; i<count; i++)
		printf("<%d> ",list[i]);
	printf("\n");
}

int main()
{
	int *list;   // 리스트 생성
	int num;     // 파일 데이터 값 변수
	int count=0; // 파일 데이터 개수
	int j=0;     // 반복 변수

	// data2.txt 읽기
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("파일 에러\n");
		exit(1);
	}

	// 파일데이터 개수 파악
	while(!feof(fp)){
		fscanf(fp,"%d ",&num);
		count++;
	}

	// 동적 할당
	list = (int *)malloc(sizeof(int)*count);
	sorted = (int *)malloc(sizeof(int)*count);

	// 파일 데이터 list에 대입
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d ",&num);
		list[j] = num;
		j++;
	}

	// 정렬 전 리스트 출력
	printf("<< 정렬되지 않은 리스트 >>\n");
	dispaly(list,count);

	// 합병 정렬 및 과정 출력
	printf("<< 정렬 과정 >>\n");
	printf("-----------------------------------------------\n");
	merge_sort(list,0,count-1);
	printf("-----------------------------------------------\n");
	
	// 정렬된 리스트 출력
	printf("<< 정렬된 리스트 >>\n");
	dispaly(list,count);

	fclose(fp);  // 파일을 닫아준다
	free(sorted);// sorted 동적할당 반납
	free(list);  // list 동적할당 반납
	return 0;
}
