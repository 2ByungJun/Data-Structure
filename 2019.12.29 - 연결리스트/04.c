#include <stdio.h>

// 배열의 최대 크기
#define MAX_LIST_SIZE 100

typedef struct {
	int studentNumber;
	int kor;
	int eng;
	int math;
} element;

typedef struct {
	// 배열 정의
	element list[MAX_LIST_SIZE];
	// 현재 배열에 저장된 자료들의 개수
	int length;
} ArrayListType;

// 리스트 초기화
void init(ArrayListType *L)
{
	L->length = 0;
}

/**
 * 배열 리스트에 item을 삽입하는 함수
 * @param L 배열 리스트
 * @param position 삽입하고자 하는 위치
 * @param item 삽입하고자 하는 자료
 */
void add(ArrayListType *L, int position, element item)
{
	int i;
	if (position >= 0 && position <= L->length)
	{
		for (i = L->length; i > position; i--)
		{
			L->list[i] = L->list[i - 1];
		}
		L->list[position] = item;
		L->length++;
	}
}

int getTotal(element *e)
{
	return e->kor + e->eng + e->math;
}

void display(ArrayListType *L)
{
	int i;
	printf("%20s%7s%7s%7s%7s%7s\n", "학번", "국어", "영어", "수학", "총점", "평균");
	for (i = 0; i < L->length; i++)
	{
		printf("%20d%7d%7d%7d%7d%7.2f\n",
			L->list[i].studentNumber,
			L->list[i].kor,
			L->list[i].eng,
			L->list[i].math,
			getTotal(L->list + i),
			getTotal(L->list + i) / 3.0);
	}
	puts("");
}

void sort(ArrayListType *L)
{
	int i, j;
	element tmp;
	for (i = 0; i < L->length; i++)
	{
		for (j = i + 1; j < L->length; j++)
		{
			if (getTotal(L->list + i) < getTotal(L->list + j))
			{
				tmp = L->list[i];
				L->list[i] = L->list[j];
				L->list[j] = tmp;
			}
		}
	}
}

int main()
{
	FILE *fp;
	element tmp;
	int i;
	ArrayListType l;

	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		puts("파일을 열 수 없습니다!");
		return 1;
	}

	init(&l);
	for (i = 0; !feof(fp); i++) 
	{
		fscanf(fp, "%d%d%d%d", &tmp.studentNumber, &tmp.kor, &tmp.eng, &tmp.math);
		add(&l, l.length, tmp);
	}
	puts("Before Sorting!!");
	display(&l);

	puts("\n\n\n\n");
	puts("After Sorting!!");
	sort(&l);
	display(&l);

	return 0;
}