#include <stdio.h>

// �迭�� �ִ� ũ��
#define MAX_LIST_SIZE 100

typedef struct {
	int studentNumber;
	int kor;
	int eng;
	int math;
} element;

typedef struct {
	// �迭 ����
	element list[MAX_LIST_SIZE];
	// ���� �迭�� ����� �ڷ���� ����
	int length;
} ArrayListType;

// ����Ʈ �ʱ�ȭ
void init(ArrayListType *L)
{
	L->length = 0;
}

/**
 * �迭 ����Ʈ�� item�� �����ϴ� �Լ�
 * @param L �迭 ����Ʈ
 * @param position �����ϰ��� �ϴ� ��ġ
 * @param item �����ϰ��� �ϴ� �ڷ�
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
	printf("%20s%7s%7s%7s%7s%7s\n", "�й�", "����", "����", "����", "����", "���");
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
		puts("������ �� �� �����ϴ�!");
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