///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 20��
// ���α׷���   : ���� ����
//   ��  ��     : p457�� ���α׷��� �����Ͽ� data.txt�� ����� ������
//                ���� ����Ʈ�� �����Ϳ� ���� ���� �˰����� ����Ͽ�
//                �����Ϳ� ���� ���� ������ ����϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 50

// element ����
typedef struct {
	int num;
	char name[20];
}element;

// ���� ����
element *temp; // ������ �̸��� ���� temp �迭
int count=0;   // ���� ������ ����

// GraphNode ����
typedef struct GraphNode{
	int vertex;
	struct GraphNode *link;
} GraphNode;

// GraphType ����
typedef struct GraphType{
	int n;
	char name[20];
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

// ���� ����
typedef struct {
	element stack[MAX_VERTICES];
	int top;
}StackType;

// �׷��� �ʱ�ȭ
void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for( v=0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// ���� ���Կ���
int insert_vertex(GraphType *g,int v)
{
	if( ((g->n)+1) > MAX_VERTICES ) {
		fprintf(stderr,"�׷���:������ ���� �ʰ�");
		return 0;
	}
	g->n++;
}

// ���� ���Կ���
void insert_edge(GraphType *g,int u,int v)
{
	GraphNode *node;
	if( u >= g->n || v >= g->n ) {
		fprintf(stderr,"�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

/* ���� �Լ� */
// ���� �ʱ�ȭ �Լ�
void init(StackType *s)
{
	s->top = -1;
}
// ���� ���� ���� �Լ�
int is_empty(StackType *s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType *s)
{
	return (s->top == (MAX_VERTICES-1));
}
// ���� �Լ�
void push(StackType *s,element item)
{
	if( is_full(s) ) {
		fprintf(stderr,"���� ��ȭ ����\n");
		return;
	}
	else s->stack[++(s->top)] = item;
}
// ���� �Լ�
element pop(StackType *s)
{
	if( is_empty(s) ) {
		fprintf(stderr,"���� ���� ����\n");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

// ���� ����
void topo_sort(GraphType *g)
{
	int i,j;        // �ݺ� ����
	StackType s;    // ���� ����
	GraphNode *node;// GraphNode ����
	int *in_degree; // push�� �̿��� ���� �ӽ� �迭

	// in_degree �����Ҵ�
	in_degree = (int *)malloc(g->n* sizeof(int));

	// �ʱ�ȭ
	for( i=0; i<g->n; i++)
		in_degree[i]=0;
	// ��� ������ ���� ������ ���
	for( i=0; i<g->n; i++) {
		GraphNode *node = g->adj_list[i];
		while( node != NULL ) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	// ���� ������ 0�� ������ ���ÿ� ����
	init(&s); // ���� �ʱ�ȭ
	for( i=0; i<g->n; i++)
	{
		if( in_degree[i] == 0 ) 
		{
			for( j=0; j<count; j++){ // �����Ϳ� ���� ���� ����
				if( temp[j].num == i )
					push(&s,temp[j]);// temp����ü�迭�� push
			}
		}
	}

	// ���� ������ ����
	i=1; // j �ʱ�ȭ
	while(!is_empty(&s)){
		element w;   // ����ü w ����
		w = pop(&s); // pop
		printf("%d. %d-%s\n",i++,w.num,w.name); // ��¹�
		node = g->adj_list[w.num];
		// in_degree���� --�Ͽ� �� 0�ϰ�� temp����ü �迭 push
		while(node != NULL) {
			int u = node->vertex;
			in_degree[u]--;
			if(in_degree[u] == 0){
				for( j=0; j<count; j++){ // �����Ϳ� ���� ���� ����
					if( temp[j].num == u )
						push(&s,temp[j]);
				}
			}
			node = node->link; // ���� ����
		}
	}
	free(in_degree); // in_degree ����
	return; // ����
}


int main()
{
	GraphType g;     // GraphType g ����
	char ch;         // v,e �Ǻ�
	int num_x,num_y; // ����x,y
	int i=0;

	// ���� ���� fp
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}

	// ���� ���� �ľ�
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if( ch == 'v'){
			count++;
		}
	}

	// ���� ���� ������ �迭 ���� �Ҵ�
	temp = (element *)malloc(sizeof(element)*count);

	// �׷��� �ʱ�ȭ
	graph_init(&g);

	// ������
	printf("< ������ >\n");
	printf("------------------\n");
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch); // v, e �Ǻ�
		// v�� ���
		if( ch == 'v')
		{
			fscanf(fp,"%d %s",&g.n,&g.name);
			printf("%d-%s\n",g.n,g.name);
			// temp�迭�� ���� �����Ͱ� ����
			temp[i].num = g.n;
			strcpy(temp[i].name,g.name);
			i++;
			// ���� ����
			insert_vertex(&g,g.n);
		}
		// e�� ���
		else if( ch == 'e')
		{
			fscanf(fp,"%d %d",&num_x,&num_y);
			// ���� ����
			insert_edge(&g,num_x,num_y);
		}
	}
	printf("------------------\n\n");

	// ���� ���� ���
	printf("< ���� ���� ��� >\n");
	printf("------------------\n");
	topo_sort(&g); // ���� ���� �Լ�
	printf("------------------\n");

	free(temp); // temp�����Ҵ� �ݳ�
	fclose(fp); // ������ �ݽ��ϴ�
	return 0;   // ����
}