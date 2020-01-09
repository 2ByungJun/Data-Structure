///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 11��
// ���α׷���   : Kruskal�� MST �˰���
//   ��  ��     : å p431�� �ڵ带 �����Ͽ� Kruskal�� �ּ� ��� ���� Ʈ��
//                ���α׷��� �ۼ��ϰ� ����� ����� ����ϴ� ���α׷�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000 // INF�� ���������� ������ ������ ǥ��

int parent[MAX_VERTICES]; // �θ� �迭
int num[MAX_VERTICES];

// �ʱ�ȭ
void set_init(int n)
{
	int i;
	for( i=0; i<n; i++){
		parent[i] = -1;
		num[i] = 1;
	}
}
// vertex�� ���ϴ� ������ ��ȯ�Ѵ�
int set_find(int vertex)
{
	int p,s,i=-1;
	for(i=vertex; (p=parent[i])>=0; i=p) // ��Ʈ ������ �ݺ�
		;
	s = i; // ������ ��ǥ ����
	for(i=vertex; (p=parent[i])>=0; i=p )
		parent[i] = s; // ������ ��� ���ҵ��� �θ� s�� ����
	return s;
}
// �� ���� ���Ұ� ���� ������ ��ģ��.
void set_union(int s1,int s2)
{
	if( num[s1] < num[s2] ){
		parent[s1] = s2;
		num[s2] += num[s1];
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

// element ����ü ����
typedef struct {
	int key; // ������ ����ġ
	int u;   // ���� x
	int v;   // ���� y
} element;

// ���� ����ü ����
typedef struct{
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

// ���� �ʱ�ȭ
void init(HeapType *h)
{
	h->heap_size = 0;
}
// ���� ����
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);
	//
	while( (i != 1) && (item.key < h->heap[i/2].key )){
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = item;
}
// ���� ����
element delete_min_heap(HeapType *h)
{
	int parent,child;
	element item,temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while( child <= h->heap_size ){
		//
		if( ( child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child+1].key)
			child++;
		if( temp.key <= h->heap[child].key) break;
		//
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
// ���� u�� ���� v�� �����ϴ� ����ġ�� weight�� ������ ������ ����
void insert_heap_edge(HeapType *h,int u,int v,int weight,int n)
{
	element e;
	int i;
	e.u = u;
	e.v = v;
	e.key = weight;

	for(i = 1; i<n; i++)
	{
		if(((h->heap[i].u == e.u) && (h->heap[i].v == e.v)) ||
			((h->heap[i].v == e.u) && (h->heap[i].u == e.v)))
		{
				printf("���� %d - %d�� �̹� �߰��� �����Դϴ�. -- ����\n",e.u,e.v);
				return;
		}
	}
	insert_min_heap(h,e);
	printf("���� %d - %d �߰� �Ϸ�\n",u,v);
}
// ���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ����
void insert_all_edges(HeapType *h,int n)
{
	int edg1,edg2,length; // ����1,����2,���� ����ġ

	// data2.txt ������ �б�
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}
	// ���� ����
	while(!feof(fp)){
		fscanf(fp,"%d %d %d",&edg1,&edg2,&length);
		insert_heap_edge(h,edg1,edg2,length,n);
	}
	fclose(fp); // ������ �ݾ��ش�.
}
// kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(int n)
{
	int edge_accepted=0; // ������� ���õ� ������ ��
	HeapType h;          // �ּ� ����
	int uset, vset;      // ���� u�� ���� v�� ���� ��ȣ
	int mul_sum=0;       // �ּ� ������
	element e;           // ���� ���
	int i=0;             // �ݺ� ����

	init(&h); // ���� �ʱ�ȭ
	printf(">> ������ �Է�\n");
	
	insert_all_edges(&h,n); // ������ �������� ����
	set_init(n);            // ���� �ʱ�ȭ

	// ����
	printf("\n>> ����\n");
	while( edge_accepted < (n-1) ) // ������ �� < n-1
	{
		e = delete_min_heap(&h); // �ּ� �������� ����
		uset = set_find(e.u);    // ���� u�� ���� ��ȣ
		vset = set_find(e.v);    // ���� v�� ���� ��ȣ
		if( uset != vset) {      // ���� ���� ������ �ٸ���
			printf("���� %d-%d : %d \n",e.u ,e.v ,e.key);
			mul_sum += e.key;    // �ּ� ��� ���� ��
			edge_accepted++;
			set_union(uset, vset);
		}
		else{                    // ���� ���� ������ ���� ���
			printf("���� %d-%d : %d - ����Ŭ �������� ���� \n",e.u, e.v, e.key);
			// ������ ���� ������ �� ����� �����ϱ� ���� ������ ���� ������ ����
			if( edge_accepted == n-2 ) // ���� while�������� -1
				edge_accepted++;
		}
	}
	// �ּ� ��� ���
	printf("\n< �ʿ��� �ּ� ��� %d >\n",mul_sum);
}
int main()
{
	int edg1,edg2,length; // ����1, ����2, ����ġ
	int high=0;           // �ִ� ����

	// data2.txt ������ �б�
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}

	// high���� ���� �ִ� ���� ����
	while(!feof(fp)){
		fscanf(fp,"%d %d %d",&edg1,&edg2,&length);
		if( high < edg2)
			high = edg2;
	}

	// kruskal ���α׷� ����
	rewind(fp);
	kruskal(high+1);

	// ������ ���� �� ����
	fclose(fp);
	return 0;
}