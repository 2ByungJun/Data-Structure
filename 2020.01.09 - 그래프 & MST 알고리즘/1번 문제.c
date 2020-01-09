///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 11��
// ���α׷���   : �׷��� �ʺ� �켱 Ž�� ���α׷�
//   ��  ��     : å p418�� �ִ� ���α׷� 10.5�� �ʺ� �켱 Ž�� ���α׷���
//                �����Ͽ� ���Ͽ� �ԷµǾ��ִ� ������ ������ ������ �̿��Ͽ�
//                �׷����� �����ϰ� ���� �ʺ� Ž���� �ϴ� ���α׷�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1    // ���� �� TRUEǥ�� ����
#define FALSE 0   // FALSE�� �ʱ�ȭ
#define MAX_VERTICES 50 

// GraphNode ����ü ����
typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
} GraphNode;

// GraphType ����ü ����
typedef struct GraphType{
	int n;
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

/* ť Ÿ�� ���� */
typedef int element;
typedef struct {    
	element queue[MAX_VERTICES]; 
	int front, rear;
} QueueType;

// �׷��� �ʱ�ȭ
void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for(v=0; v<MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

// ���� ���� ����
void insert_vertex(GraphType *g,int v)
{
	if( ((g->n)+1) > MAX_VERTICES )
	{
		fprintf(stderr,"�׷��� : ������ ���� �ʰ�" );
		return;
	}
	g->n++;
}

// ���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g,int u,int v)
{
	GraphNode *node;
	if( u > g->n || v > g->n ) {
		fprintf(stderr,"�׷���: ���� ��ȣ ����\n");
		return;
	}
	node = ( GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

int visited[MAX_VERTICES]; 

/* ť */
// ť ���� �Լ�
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// ť �ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
// ť�� ����ִ��� Ȯ���ϴ� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
// ť�� ���ִ��� Ȯ���ϴ� �Լ�
int is_full(QueueType *q)
{
	return (q->rear+1)%MAX_VERTICES == q->front;
}
// ť ���� �Լ�
void enqueue(QueueType *q,element item)
{
	if( is_full(q) )
		error("ť�� ��ȭ�����Դϴ�\n");
	q->rear = (q->rear+1)%MAX_VERTICES;
	q->queue[q->rear] = item;
}
// ť ���� �Լ�
element dequeue(QueueType *q)
{
	if( is_empty(q) )
		error("ť�� ��������Դϴ�.");
	q->front = (q->front +1)%MAX_VERTICES;
	return q->queue[q->front];
}

// �ʺ� �켱 Ž��
void bfs_list(GraphType *g,int v)
{
	GraphNode *w;
	QueueType q;
	init(&q);          // ť �ʱ�ȭ
	visited[v] = TRUE; // ���� v �湮
	printf("%d ",v);
	enqueue(&q, v);
	while(!is_empty(&q))
	{
		v = dequeue(&q);
		for(w=g->adj_list[v]; w; w = w->link)
		{
			if(!visited[w->vertex])
			{
				visited[w->vertex] = TRUE;
				printf("%d ",w->vertex);
				enqueue(&q, w->vertex);
			}
		}
	}
}

int main()
{
	GraphType g;       // �׷��� ����
	char c;            // v�� e ����
	int num_v;         // v������ ��
	int num_e1,num_e2; // e������ ����

	// data1.txt �б�
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}
	// �׷��� �ʱ�ȭ
	graph_init(&g);

	// ���� �о�� �׷��� ����
	while(!feof(fp))
	{
		fscanf(fp,"%c",&c); // v,e ����
		if( c == 'v')
		{
			fscanf(fp,"%d",&num_v);
			insert_vertex(&g,num_v); // num_v�� ���� ����
		}
		else if( c == 'e') 
		{
			fscanf(fp,"%d %d",&num_e1,&num_e2);
			insert_edge(&g,num_e1,num_e2); // e1�� e2 ���� ����
			insert_edge(&g,num_e2,num_e1); // e2�� e1 ���� ����
		}
	}

	// �ʺ� �켱 Ž��
	printf("- �׷��� �ʺ� �켱 Ž�� ��� -\n< ");
	bfs_list(&g,0);
	printf(">\n");

	fclose(fp); // ������ �ݾ��ش�
	return 0;   // ����
}