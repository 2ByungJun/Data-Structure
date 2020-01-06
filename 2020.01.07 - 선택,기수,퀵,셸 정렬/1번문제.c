///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 10월 16일
// 프로그램명   : 선택 정렬 프로그램
//   설  명     : data1.txt에 학생의 정보가 이름, 학번, 등수로 저장되어
//                있다. 이를 읽어와 학번 순, 등수 순으로 정렬하여 출력
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// 스왑정의
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

// element구조체 정의
typedef struct element{
	char name[20]; // 이름
	int schoolnum; // 학번
	int num;       // 등수
}element;

// 학번정렬
void schoolnum_sort(element *list,int n)
{
	int i,j,least; // i.j:반복변수 , least:최소값 자리 인덱스
	element temp;  // SWAP을 위한 element선언
	for(i=0; i<n-1; i++) {
		least = i; 
		for(j=i+1; j<n; j++)
			if(list[j].schoolnum < list[least].schoolnum) least=j; // 학번대수 비교
		SWAP(list[i],list[least],temp); 
	}
}
// 등수정렬
void num_sort(element *list,int n)
{
	int i,j,least; // i.j:반복변수 , least:최소값 자리 인덱스
	element temp;  // SWAP을 위한 element선언
	for(i=0; i<n-1; i++) {
		least = i;
		for(j=i+1; j<n; j++)
			if(list[j].num<list[least].num) least=j; // 등수대수 비교
		SWAP(list[i],list[least],temp);
	}
}

int main()
{
	element *temp; // 구조체배열 temp
	element e;     // 구조체 e
	int count=0;   // 파일 개수
	int i=0;       // 반복변수
	// 파일 오픈
	FILE *fp= fopen("data1.txt","r");
	if(fp == NULL){
		printf("파일 에러\n");
		exit(1);
	}
	// 파일 데이터 개수체크
	while(!feof(fp)){
		fscanf(fp,"%s %d %d",e.name,&e.schoolnum,&e.num);
		count++; // 파일개수 카운팅
	}
	// 동적 할당
	temp = (element *)malloc(sizeof(element)*count);

	// 파일포인터 리셋
	rewind(fp);
	// temp[i]에 파일 데이터값 대입
	for( i=0; i<count; i++)
	{
		fscanf(fp,"%s %d %d",temp[i].name,&temp[i].schoolnum,&temp[i].num);
	}
	
	// 정렬전 데이터
	printf("< 정렬전 데이터 >\n");
	printf(" ---------------------\n");
	printf("| 이름 |  학 번  |등수|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");


	// 학번정렬
	schoolnum_sort(temp,count);
	printf("< 학번 정렬후 데이터 >\n");
	printf(" ---------------------\n");
	printf("| 이름 |  학 번  |등수|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");

	// 등수 정렬
	num_sort(temp,count);
	printf("< 등수 정렬후 데이터 >\n");
	printf(" ---------------------\n");
	printf("| 이름 |  학 번  |등수|\n");
	printf(" ---------------------\n");
	for( i=0; i<count; i++)
		printf("|%s| %d| %d |\n",temp[i].name,temp[i].schoolnum,temp[i].num);
	printf(" ---------------------\n");


	free(temp); // temp 동적반납
	fclose(fp); // fp 파일을 닫습니다.
	return 0;
}