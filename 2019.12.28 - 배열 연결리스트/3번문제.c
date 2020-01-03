///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 4월 10일
// 프로그램명   : 성적 관리 프로그램
//   설  명     : 학생 별 학번,국어,영어,수학의 점수가 data.txt 파일에
//                저장되어 있다. 이 파일의 데이터를 읽어 들여 동적으로
//                만든 구조체 배열에 저장하고, 학생의 학번 또는 이름을
//                입력 받아 그 학생의 성적 및 총점, 평균, 등수를 출력하라
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>  // malloc,free를 써주기 위한 라이브러리 함수 
#include <string.h>  // 문자열을 다루는 라이브러리 함수

typedef struct Student // Student 구조체 생성
{
   char number[20];   // 학번
   char name[20];     // 이름
   int korean;        // 국어
   int english;       // 영어
   int math;          // 수학
}Student; // Animal로 정의

int main()
{
   Student *temp;      // tmep 동적할당 구조체배열 선언
   int F_line;         // 파일을 읽어줄 라인변수선언
   int count=0;        // 데이터 값을 카운팅해줄 변수
   int i=0;            // 반복문 증가값 변수
    char name_num[20];  // 학번과 이름을 비교할 배열
   int index;          // 학번과 이름이 동일시 위치를 저장해줄 값
   int sum;            // 총점
   double average;     // 평균
   char rank[20];      // 석차를 구하기위해 총점을 저장할 배열 
   int rank1=1;        // 석차
   
   FILE *fp = fopen("data3.txt","r");  // data3.txt파일을 읽기형식으로 오픈
   if(fp == NULL)                      // 파일 에러시 출력문구
   {
      printf("파일을 열지 못했습니다.\n");
      return 0;
   }

   while(!feof(fp))   // 파일 포인터가 끝까지 도달할때까지 반복하는 반복문
   {
      F_line = fgetc(fp);
      if(F_line == '\n')
         count++; // 데이터값 카운팅 증가값
   }
   count++; // 마지막 라인 카운트 증가

   temp = (Student *)malloc(sizeof(Student)*count); // temp 구조체 배열 동적할당
   if ( temp == NULL)      // 동적할당 오류시 조건
   {
      printf("동적 메모리 할당 오류\n"); // 동적할당 오류시 출력문구
      return 0;
   }

   rewind(fp); // 파일 포인터 초기화
   while(!feof(fp))   // 파일 포인터가 끝까지 도달할때까지 반복하는 반복문
   {
      // 구조체 배열의 변수값에 파일데이터값 대입
      fscanf(fp,"%s %s %d %d %d", temp[i].number, temp[i].name, &temp[i].korean, &temp[i].english,&temp[i].math);
	  rank[i] =  temp[i].korean + temp[i].english + temp[i].math; // rank[i]배열에 총점을 저장
	  i++; // i값의 증가
   }

   // 학생의 이름과 학번으로 정보 찾기
   printf("학생의 이름 또는 학번을 입력하세요 : ");
   scanf("%s",&name_num);   // 학생이름 또는 학번을 입력
   for ( i=0; i<count; i++) // count크기의 반복문
   {
      if( strcmp ( name_num , temp[i].name ) == 0 ){ // 입력한 이름과 temp[i]이름을 비교에서 같은 경우
         index = i; // index에 i값 저장
         break;     // 반복문 탈출
      }
      if( strcmp ( name_num , temp[i].number ) == 0 ){ // 입력한 학번과 temp[i]학번을 비교해서 같은 경우
         index = i; // index에 i값 저장
         break;     // 반복문 탈출
      }
   }

   sum = temp[index].korean + temp[index].english + temp[index].math;  // 입력한 학생의 총점
   average = (double)sum/count; // 입력한 학생의 평균
    for ( i=0; i<count; i++) // count크기의 반복문
   {
      if(rank[index] < rank[i]) // 입력한 학생의 총점 < 나머지 인원의 총점의 조건식
         rank1++; // rank1값이 올라간다
   }

   // 입력한 학생 정보 출력
   printf("입력하신 학생 \"%s\"학생의 정보는 아래와 같습니다.\n" , temp[index].name ); // 입력된 학생이름 출력
   printf("| 학     번 | 국어 | 영어 | 수학 | 총 점 | 평 균 | 석 차 |\n");
   printf("| %s  |  %d  |  %d  |  %d  |  %d  | %.2lf |  %d/%d  |\n",temp[index].number,temp[index].korean,temp[index].english,temp[index].math,sum,(double)average,rank1,count);

   free(temp); // temp 동적메모리 반납
   fclose(fp); // 파일을 닫아준다
   return 0;
}
