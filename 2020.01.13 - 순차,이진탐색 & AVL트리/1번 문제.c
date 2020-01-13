///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 12�� 4��
// ���α׷���   : ������ ���� Ž��
//   ��  ��     : data.txt�� ����� �������� P.504�� �ڵ带 �̿��Ͽ�
//                Ž���� ������ ���� Ž�� �ð��� �����Ͽ� ���϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �������� ����
int *list;

// ���� Ž��
int seq_search(int key,int low,int high)
{
	int i;
	for(i=low; i<=high; i++)
		if(list[i]==key) return i;
	return -1;
}
// ������ ���� Ž��
int seq_search2(int key,int low,int high)
{
	int i;
	list[high+1] = key;
	for(i=low; list[i] != key; i++)
		;
	if(i==(high+1)) return -1;
	else return i;
}

int main()
{
	int num,s_num=0;   // ������ ���Ϻ���, �Էº���
	int count=0,i=0;   // ���� ������ ����, �ݺ� ����
	clock_t start=0,finish=0; // �ð� ��������, ��ħ����
	double savetime=0;        // �ð� ���� ����
	// data1.txt ���� �б�
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL)
	{
		printf("���� ����\n");
		exit(1);
	}

	// list �����Ҵ�
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	list = (int *)malloc(sizeof(int)*count);

	// list�� �����Ͱ� ����
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		list[i] = num;
		i++;
	}

	// �Է�
	printf(">>������ ����: %d\n",count);
	printf("ã���� �ϴ� ������ �Է��ϼ��� : ");
	scanf("%d",&s_num);

	// Ž��
	printf("\n<Ž�� ����>\n");
	start = clock();       // ���� �ð�
	seq_search(s_num, 0,count-1);
	finish = clock();      // ���� �ð�
	savetime = (double)(finish-start)/CLOCKS_PER_SEC; // �ð� ���
	printf("����Ž�� ���� �ӵ� : %lf\n",savetime);

	start = clock();       // ���� �ð�
	seq_search2(s_num, 0, count-1);
	finish = clock();      // ���� �ð�
	savetime = (double)(finish-start)/CLOCKS_PER_SEC; // �ð� ���
	printf("������ ����Ž�� ���� �ӵ� : %lf\n",savetime);

	fclose(fp); // ������ �ݽ��ϴ�
	free(list); // �Ҵ� �ݳ�
	return 0;
}
