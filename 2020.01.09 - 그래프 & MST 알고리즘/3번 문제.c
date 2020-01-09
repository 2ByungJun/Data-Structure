///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 11��
// ���α׷���   : Prim�� MST �˰���
//   ��  ��     : å p436�� �ڵ带 �����Ͽ� Prim�� �ּ� ��� ���� Ʈ��
//                ���α׷��� �ۼ��Ͽ� �׽�Ʈ�ϱ�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1    // ���� �� TRUEǥ�� ����
#define FALSE 0   // FALSE�� �ʱ�ȭ
#define INF 1000L // INF�� ���������� ������ ������ ǥ��

int **weight;  // ������ ���
int *selected; // �ӽ� ���� �迭
int *dist;     // ������ ���� ũ���� �迭, ������ ����ġ ũ�⸦ ��Ÿ��

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n)
{
	int v,i;
	for ( i=0; i<n; i++)
		// �鸮�� �ʾҴٸ�
		if ( !selected[i]) {
			v = i;
			break;
		}
	for( i = 0; i<n; i++)
		// �鸮�� �ʾҰų� ����ġ�� �� ���� ��츦 ��
		if( !selected[i] && (dist[i] < dist[v])) 
			v = i;
	// ���� ��ȯ
	return (v);
}
// s : ���� ����
// n : ���� ����
void prim(int s,int n)
{
	int i,j,v,u; // i,j,v : �ݺ�����, u : ����
	int *Array;  // u������ ������ ����� �迭
	int sum = 0;   // ����ġ ���� �� ����

	// ���� �Ҵ�
	Array = (int *)malloc(sizeof(int)*n);

	printf(">> ����\n");
	// dist�� selected �迭 �ʱ�ȭ
	for(u=0; u<n; u++)
	{
		dist[u] = INF; selected[u] = FALSE; 
	}
	// ������ ���ۺκ��� ����ġ�� 0���� �ʱ�ȭ
	dist[s]=0;

	for(i=0; i<n; i++){
		u=get_min_vertex(n);
		// ���� �� TRUE ǥ��
		selected[u] = TRUE;
		// ����ġ�� INF�� ����
		if( dist[u] == INF ) return;

		// ���� ���
		printf("%d >> ",i+1); 
		Array[i] = u;
		// ���� ���� ���
		for( j=0; j<i+1; j++)
			printf("%d ",Array[j]); 
		// ����ġ ���� �� ���
		sum += dist[u];
		printf(": %d\n",sum);

		for( v=0; v<n; v++)
			if(weight[u][v] != INF)
				if( !selected[v] && weight[u][v] < dist[v] )
					dist[v] = weight[u][v];
	}
	// ���� �Ҵ� �ݳ�
	free(Array);
	// �ּ� ��� ���
	printf("\n< �ʿ��� �ּ� ��� %d >\n",sum);
	exit(1);
}
//
int main()
{
	int num_x;   // ���� x 
	int num_y;   // ���� y
	int num_add; // ����ġ
	int max_num=0; // �ִ� ����
	int count=0;   // ���� ������ ��
	int i,j;       // �ݺ� ����

	// data3.txt ���� ����
	FILE *fp = fopen("data3.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}
	// �ִ����� ���ϱ�
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d",&num_x,&num_y,&num_add);
		if( max_num < num_y ) // �ִ����� ���ϱ�
			max_num = num_y;
	}
	// ���� �Ҵ�
	weight = (int **)malloc(sizeof(int*)*max_num);
	for( i=0; i<=max_num; i++ ){
		weight[i] = (int *)malloc(sizeof(int)*max_num);
	}
	selected = (int *)malloc(sizeof(int)*max_num);
	dist = (int *)malloc(sizeof(int)*max_num);

	// weight �ʱ�ȭ
	for(i=0; i<=max_num; i++){
		for(j=0; j<=max_num; j++)
			weight[i][j] = INF;
	}

	// weight ����
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d",&num_x,&num_y,&num_add);
		weight[num_x][num_y] = num_add;
		weight[num_y][num_x] = num_add;
	}
	for( i=0; i<=max_num; i++){
		weight[i][i] = 0;
	}

	// Prim ���α׷� ����
	printf("- Prim�� �ּ� ��� ���� Ʈ�� ���α׷� -\n\n");
	prim(0,max_num+1);

	// ���� �ݱ�
	fclose(fp);
	// ���� �Ҵ� �ݳ�
	for(i=0; i<=max_num; i++) free(weight);
	free(weight);
	free(dist);
	free(selected);
	return 0;
}
