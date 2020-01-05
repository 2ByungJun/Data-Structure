///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 10��
// ���α׷���   : �켱 ���� ť
//   ��  ��     : data.txt�� �մ��� ����� ������ �̸��� �Բ� �ԷµǾ��ִ�.
//                �� ����� ������ ������ �����ϰ� �̸� ���� ��ȸ�� �̿��Ͽ�
//                ����Ͻÿ�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 100

// element ����
typedef struct {
	char name[MAX_ELEMENT]; // �̸�
	int key; // �ε���
} element;

// HeapType ����
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// �ʱ�ȭ�Լ�
void init(HeapType *h){
	h->heap_size = 0;
}

// Min���� ����
void insert_min_heap(HeapType *h,element item)
{
	int i;
	i = ++(h->heap_size);

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while((i != 1) && (item.key < h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}

// Min���� ����
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while( child <= h->heap_size ){
		// ���� ����� �ڽ� ��� �� �� ���� �ڽ� ��带 ã�´�.
		if( ( child < h->heap_size ) && 
			( h->heap[child].key) > h->heap[child+1].key)
			child++;
		if( temp.key <= h->heap[child].key) break;
		// �� �ܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// ���
void display(HeapType *h)
{
	int i;
	printf("< ���� ���� ��ȸ ��� >\n");
	// heap_size��ŭ ���
	for(i = 1; i<=h->heap_size; i++){ 
		printf("%d - %s\n", i , h->heap[i].name );
	}
	printf("\n");
}

int main()
{
	HeapType heap;   // heap����
	element e;       // ����üe
	element delete_e;// ������ ����ü ���Ժ���
	char s[20];      // ���� �̸��� �о�� ���ڿ�
	char c;          // i / o �����
	int i=0;         // �ε���
	// data2.txt������ �б��������� ����
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){ // ���� ������
		printf("���� ����\n");
		exit(1);
	}
	init(&heap); // heap �ʱ�ȭ

	while(!feof(fp)){
		fscanf(fp,"%c",&c); // i / o ���ڸ� c�� �޾ƿ´�.
		if( c == 'i'){      // i�� ��� ����
			fscanf(fp,"%s",s);  // ���Ͽ��� �̸��� �޾� s�� ����.
			i++;
			printf(">> �մ�(%s) ����\n",s);
			// ����
			e.key = i;        // �ε��� ��
			strcpy(e.name,s); // �̸� ����
			insert_min_heap(&heap,e); // e����
			display(&heap);   // ���
		}

		else if( c == 'o'){ // o�� ��� ����
			delete_e = delete_min_heap(&heap); // �����Ͽ� delete_e�� ����
			printf(">> �մ�(%s) ����\n",delete_e.name);
			display(&heap); // ���
		}

	}

	fclose(fp); // ������ �ݾ��ش�.
	return 0;
}