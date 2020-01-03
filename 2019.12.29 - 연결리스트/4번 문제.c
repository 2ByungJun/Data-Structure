///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 19일
// 프로그램명   : 배열로 구현된 연결리스트 4
//   설  명     : 보기와 같이 data.txt파일에 학번,국어,영어,수학 점수가
//                입력되어 있다. 이 파일을 이용하여 구조체 안의 구조체
//                배열에 초기화 하고 이를 이용하여 평균점수 순으로
//                Sorting하여 아래와 같이 출력하는 프로그램을 작성하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100 // 배열의 최대 크기

typedef struct {  // student 구조체
	int number;   // 학번
	int korean;   // 국어
	int english;  // 영어
	int math;     // 수학
}student;

typedef int element;
typedef struct {
	int list[MAX_LIST_SIZE];
	int length; // 현재 배열에 저장된 자료들의 개수
}ArrayListType;

// 리스트 초기화
void init(ArrayListType *L)
{
	L->length = 0;
}
// 리스트가 가득 차 있으면 1을 반환
// 그렇지 않으면 0을 반환
int is_full(ArrayListType *L)
{
	return L->length == MAX_LIST_SIZE;
}
// position : 삽입하고자 하는 위치
// item : 삽입하고자 하는 자료
void add(ArrayListType *L , int position,element item)
{
	if( !is_full(L) && (position >= 0) && (position <= L->length) ) 
	{
			int i;
			for( i=(L->length-1); i>=position; i--) 
				L->list[i+1] = L->list[i];
			L->list[position] = item;
			L->length++;
	}
}
// 리스트 출력
void display(ArrayListType *L,int count)
{
	int i,j=0,z=0;     // 반복문 증가값
	int sum[20];       // 총점 배열
	double average[20];// 평균 배열
	int tmp;           // 버블정렬 대입변수
	int index_num;     // After Sorting!! sum위치 컨트롤 변수
	int x;             // After Sorting!! 출력 컨트롤 변수

	// 총점과 평균 배열 구하기
	for( i=0; i<count; i++)
	{
		sum[i] = L->list[1+j]+ L->list[2+j] + L->list[3+j]; // 총점을 구하는 연산
		average[i] = (double)sum[i]/3;                      // 평균을 구하는 연산
		j+=4; // j가 +4씩증가
	}

	// Before Sorintg!!
	printf("Before Sorting!!\n");
	printf("학번           국어    영어    수학     총점     평균\n");
	// 초기화된 변수값
	j=0;
	// 출력문
	for( i=0; i<=L->length; i++){ // 리스트 크기만큼 반복 
		if( i != 0 && i%4 == 0 )  // i값이 0이 아니며 i의 4배수일경우
		{
			printf("%d \t%.2lf \t",sum[j] , average[j]); // 총점과 평균 출력
			j++;
			printf("\n");
		}
		if( L->length != i )        // 리스트의 크기가 i값과 다를경우
		printf("%d \t",L->list[i]); // 리스트 출력
	}
	printf("\n\n\n");

	// sum , average 버블정렬 - 큰수를 먼저 출력하기 위함
	for( i=0; i<count; i++)
	{ 
		for(j=0; j<count-1; j++)
		{
			if(sum[j]<sum[j+1])    // sum값을 다음 항과 비교하여 다음 항이 더 클 경우
			{
				tmp = sum[j];      // 기존 sum값을 tmp에 대입
				sum[j] = sum[j+1]; // 기존 sum값에 다음 항을 대입
				sum[j+1] = tmp;    // 다음 항에 기존 sum값을 대입
			}
			if(average[j]<average[j+1])    // average값을 다음 항과 비교하여 다음 항이 더 클 경우
			{
				tmp = average[j];          // 기존 average값을 tmp에 대입
				average[j] = average[j+1]; // 기존 average값에 다음 항을 대입
				average[j+1] = tmp;        // 다음 항에 기존 average값을 대입
			}
		}
	}

	// After Sorting!!
	printf("After Sorting!!\n");
	printf("학번           국어    영어    수학     총점     평균\n");
	// 초기화된 변수값
	index_num=0;
	j=0;
	x=0;
	// 출력문
	for( i=0; i<=L->length; i++)
	{
		if( i != 0 && i%4 == 0 )  // i값이 0이 아니며 i값이 4배수일경우
		{
			printf("%d \t%.2lf \t",sum[j] , average[j]); 
			j++;
			x--; // 총점과 평균이 출력될때까지 출력이 안되게 하는 컨트롤 변수 해제
			printf("\n");
		}
		for ( z=0; z<L->length; z+=4) // 리스트 크기만큼의 반복문이며 증가값이 z가 +4씩 증가한다
		{
			 // 총점과 비교하여 해당위치의 리스트들을 출력
			if(  sum[index_num] ==  L->list[z+1]+ L->list[z+2]+L->list[z+3] && x == 0 )
			{
				printf("%d \t%d \t%d \t%d \t",L->list[z],L->list[z+1],L->list[z+2],L->list[z+3]);
				index_num++;
				x++; // 총점과 평균이 출력될때까지 출력이 안되게 하는 컨트롤 변수 적용
				break;
			}
		}
	}
}

int main()
{
	ArrayListType *plist; // 동적할당 받을 메인 구조체 배열 선언
	student *list;        // 구조체를 초기화할 배열 선언
	int count=0;          // 파일 라인 카운팅
	int F_line;           // 카운팅을 위해 파일을 읽어줄 변수
	int i=0,j=0;          // 반복증가값 변수
	
	FILE *fp = fopen("data4.txt","r");  // data4.txt파일을 읽기형식으로 오픈
	if( fp == NULL)                     // 파일에러시 출력문구
	{
		printf("파일이 열리지 않았습니다\n");
		return 0;
	}

	while(!feof(fp))  // 파일카운팅을 위해 파일을 끝까지 읽어줄 반복문
	{
		F_line = fgetc(fp); // 파일 라인을 읽어준다
		if(F_line == '\n')  // 줄바꿈시 카운팅
			count++; // 데이터값 카운팅 증가값
	}
	count++; // 마지막 라인을 읽어야함으로 증가

	list = (student *)malloc(sizeof(student)*count); // count만큼의 list동적할당
	plist = (ArrayListType *)malloc(sizeof(ArrayListType)*count); // count만큼의 plist동적할당
	init(plist); // plist 리스트 초기화

	rewind(fp);
	while(!feof(fp))   // 파일포인터가 끝까지 도달할때까지 반복하는 반복문
	{ 
		// 구조체 배열의 변수값에 파일데이터값 대입
		fscanf(fp,"%d %d %d %d", &list[i].number,  &list[i].korean, &list[i].english,&list[i].math);
		add( plist , j , list[i].number );  // list -> plist로 학번대입
		j++;
		add( plist , j , list[i].korean );  // list -> plist로 국어점수대입
		j++;
		add( plist , j , list[i].english ); // list -> plist로 영어점수대입
		j++;
		add( plist , j , list[i].math );    // list -> plist로 수학점수대입
		j++;
		i++; // i값의 증가
	}

	display(plist,count); // plist 출력

	fclose(fp);  // 파일을 닫아준다
	free(plist); // plist의 동적할당을 반납해준다.
	free(list);  // list의 동적할당을 반납해준다.

	return 0;
}