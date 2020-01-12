///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 12월 1일
// 프로그램명   : 이차조사법을 이용한 HashTable 사전
//   설  명     : data.txt에 저장된 단어와 의미들을 경계 폴딩을 이용하여
//                변환 후 이차조사법을 이용한 HashTable에 저장하고 저장
//                과정에서 충돌이 일어난다면 아래와 같은 충돌 감지 문구를
//                출력하는 프로그램.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // 테이블 사이즈
#define SIZE 20
#define empty(e) (e.value == 0)
#define equal(e1,e2) (e1 == e2)

typedef struct element{
	char key[TABLE_SIZE]; // 단어
	char name[TABLE_SIZE];// 뜻
	int value;            // 경계폴딩 후 값
}element;

element hash_table[TABLE_SIZE];	// 해쉬 테이블

// 테이블 초기화 함수
void init_table(element ht[])
{
	int i;
	for(i=0; i<TABLE_SIZE; i++){
		ht[i].key[0] = NULL; // 단어 초기화
	}
}
// 해시 함수
int hash_function(int key)
{
	int hash_index = key % 7; // 위치
	if(hash_index < 0) // 0보다 작을경우 +하여 위치지정
		hash_index += 7;
	return hash_index; // 위치 반환
}

// 해시 삽입
void hash_lp_add(element item, element *ht)
{
	int i, hash_value;
	int inc=1;

	hash_value = i = hash_function(item.value);

	while(!empty(ht[i])){
		if(equal(item.value, ht[i].value)){
			fprintf(stderr,"탐색키가 중복되었습니다.\n");
			return;
		}
		printf("data = %s 저장 도중 HashTable : %d 에서 충돌감지 ",item.key,i);
		
		i = (i +inc*inc) % 7;
		inc = inc+1;

		printf("- index = %d 로 증가하였습니다.\n",i);

	
	}
	ht[i] = item;
}

// 경계폴딩 함수
int boundary_function(char *key)
{
	char s[SIZE];   // 단어값 하나를 저장하는 공간
	int sum=0, i;    

	for(i=0; i<SIZE; i++)
	{
		if(key[i] ==NULL) // NULL일 경우 break
			break;

		if(i%2 == 0){ // 홀수 번째일 경우
			sprintf(s,"%d",key[i]);
			sum += atoi(s);
		}
		else { // 짝수 번째일 경우
			sprintf(s,"%d",key[i]); // key단어를 분할하여 s[]에 저장 
			strrev(s);      // 문자열 반전
			sum += atoi(s); // 아스키 코드 값 누적 합
		}	
	}
	return sum;
}

// 해시 테이블 출력
void hash_Ip_print(element *ht)
{
	int i;
	for(i=0; i<TABLE_SIZE; i++){
		if(ht[i].key[0] != NULL) // 값이 NULL이 아닌경우
			printf("hashtable[%d] - %s > %s\n",i ,ht[i].key ,ht[i].name);
		else // NULL 경우 출력
			printf("hashtable[%d] - %s\n",i ,ht[i].key);
	}
}

int main()
{
	element tmp;     // 구조체 tmp
	char name[SIZE]; // 경계폴딩 대상 단어
	int list[SIZE];  // 경계폴딩함수 값들을 저장하는 배열
	int count=0;   // 반복변수

	// data1.txt를 읽기형식으로 오픈
	FILE *fp = fopen("data2.txt","r");
	if(fp == NULL){
		printf("파일 에러\n");
		exit(1);
	}

	// 테이블 초기화
	init_table(hash_table);

	// 테이블 크기
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);

	// list에 단어 복사
	printf("< Data Insert Finish >\n");	
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&tmp.key, &tmp.name);	
		strcpy(name,tmp.key);                 // name배열에 데이터 파일 '단어' 복사
		list[count]= boundary_function(name); // 경계폴딩을 사용하여 값을 배열에 저장
		count++;
	}

	// 해시 테이블에 데이터 삽입
	rewind(fp); // 파일 초기화
	count =0;   // count 초기화
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&tmp.key, &tmp.name);		
		tmp.value = list[count];     // list값들을 tmp.value에 저장
		hash_lp_add(tmp,hash_table); // tmp를 해시테이블에 삽입
		count++;
	}

	// 해시 테이블 출력
	printf("\n\n< table >\n");
	hash_Ip_print(hash_table);

	printf("< Finish >\n\n");
	fclose(fp); // 파일을 닫습니다
	return 0;   // 종료
}