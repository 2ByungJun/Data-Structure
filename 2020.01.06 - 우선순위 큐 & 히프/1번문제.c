///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 9��
// ���α׷���   : ���� ����
//   ��  ��     : �迭�� �̿��� ������ ����ؼ� data.txt�� �ִ� �켱
//                ������� �������� �̸��� �����ϰ� ����ڰ� ���ϴ�
//                ������ �̸��� �켱������ �޾� ������ �߰��ϴ� ���α׷���
//                �ۼ��Ͻÿ�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// �迭ũ�� ����
#define MAX_ELEMENT 200
// ���� ����
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

// element ����
typedef struct {
	int key;
	char animal[20];
} element;

// HeapType ����
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
} HeapType;

// �ʱ�ȭ
void init(HeapType *h)
{
	h->heap_size = 0;
}

// ����
void insert_max_heap(HeapType *h,element item)
{
	int i;
	i = ++(h->heap_size);

	// Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while((i != 1) && (item.key > h->heap[i/2].key)){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item; // ���ο� ��带 ����
}

// �� ����
void heap_sort(HeapType *h,int n)
{
	int i,j,least; // �ݺ����� �� �ּҰ���ġ ���尪
	element temp;  // temp����ü
	for(i=1; i<=n-1; i++){
		least = i;
		for(j=i+1; j<=n; j++)
			if(h->heap[j].key > h->heap[least].key) least = j;
		SWAP(h->heap[i],h->heap[least],temp);
	}
}

// ���
element display(HeapType *h,int n)
{
	int i;
	for(i = 1; i<=n; i++){
		printf("%d:%s > ", h->heap[i].key , h->heap[i].animal );
	}
	printf("\n");
}

int main()
{
	element e;
	HeapType heap; // ��������
	int count=0;
	FILE *fp = fopen("data1.txt","r");
	if( fp == NULL ){
		printf("���� ����\n");
		exit(1);
	}
	init(&heap);

	// ���� �� �켱���� ť
	while(!feof(fp)){
		// ���� ������ �޾ƿ���
		fscanf(fp,"%d %s",&e.key , e.animal);
		printf(">>%d %s\n",e.key , e.animal);
		// ����
		insert_max_heap(&heap,e);
		count++;
		// �� ����
		heap_sort(&heap,count);
		// �� ���
		display(&heap,count);
	}
	printf("\n");

	// ����ڰ� �߰��� �� 
	while(1){
	printf("������ �����͸� ���� ������ �켱������ �̸��� �Է��Ͻÿ�(�Ϸ�� �켱���� 0)\n");
	    // �߰� ������ �޾ƿ���
		printf(">>");
		scanf("%d ", &e.key);
		if( e.key == 0 )
			break;
		scanf("%s", e.animal);
		// ����
		insert_max_heap(&heap,e);
		count++;
		// �� ����
		heap_sort(&heap,count);
		// �� ���
		display(&heap,count);
		printf("\n");
	}

	fclose(fp); // ������ �ݽ��ϴ�.
	return 0;
}