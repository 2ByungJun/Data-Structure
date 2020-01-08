///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 2��
// ���α׷���   : �׷��� ���� �켱 Ž�� ���α׷�
//   ��  ��     : data3.txt���Ͽ� �ԷµǾ� �ִ� ������ ������ ������ �̿�
//                �Ͽ� �׷����� �����ϰ� ���� �켱 Ž���� ���� ����϶�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

int visited[MAX_VERTICES]; // �������� ����

typedef struct GraphType{
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

// �׷��� �ʱ�ȭ
void graph_init(GraphType *g)
{
	int r,c;
	g->n = 0;
	for(r=0; r<MAX_VERTICES; r++)
		for(c=0; c<MAX_VERTICES; c++)
			g->adj_mat[r][c]=0;
}

// ���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	if( ((g->n)+1 ) > MAX_VERTICES ) {
		fprintf(stderr,"�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType *g, int start, int end)
{
	if( start > g->n || end > g->n ) {
		fprintf(stderr,"�׷���: ���� ��ȣ ����\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// ���� ����Ʈ�� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType *g,int v)
{
	int w;
	visited[v] = TRUE;                  // ���� v�� �湮 ǥ��
	printf("%d ",v);                    // �湮�� ���� ���
	for(w=0; w<=g->n; w++) // ���� ���� Ž��
		if( g->adj_mat[v][w] && !visited[w] )
			dfs_mat(g,w);      // ���� w���� DFS ���ν��� 
}

int main()
{
	GraphType g;       // �׷��� ����
	char c;            // v�� e ����
	int num_v;         // v������ ��
	int num_e1,num_e2; // e������ ����

	// data3.txt �б�
	FILE *fp = fopen("data3.txt","r");
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
		}
	}

	// ���� �켱 Ž��
	printf("- �׷��� ���� �켱 Ž�� ��� -\n< ");
	dfs_mat(&g,0);
	printf(">\n");

	fclose(fp); // ������ �ݾ��ش�
	return 0;   // ����
}