///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 12�� 4��
// ���α׷���   : �ݺ��� �̿��� ���� Ž��
//   ��  ��     : data.txt�� ����� �������� P.509�� ���� Ž���� ���� �Ҵ���
//                �̿��� �迭�� �����ϰ� Ž���Ͽ� �ɸ� �ð��� ����϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �������� ����
int *list;

// ���� Ž��
int search_binary2(int key,int low, int high)
{
	int middle;

	while( low <= high ){
		middle = (low+high)/2;
		if(key == list[middle] ){
			return middle;
		}
		else if( key > list[middle] ){
			low = middle + 1;
		}
		else{
			high = middle-1;
		}
	}
	return -1;
}

int main()
{
	int num,s_num=0;   // ������ ���Ϻ���, �Էº���
	int count=0,i=0;   // ���� ������ ����, �ݺ� ����
	clock_t start=0,finish=0; // �ð� ��������, ��ħ����
	double savetime=0;        // �ð� ���� ����
	// data2.txt ���� �б�
	FILE *fp = fopen("data2.txt","r");
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
	printf("ã���� �ϴ� ������ �Է��ϼ��� : ");
	scanf("%d",&s_num);

	// Ž��
	printf("\n<Ž�� ����>\n");
	start = clock();       // ���� �ð�
	search_binary2(s_num, 0, count-1);
	finish = clock();      // ���� �ð�
	savetime = (double)(finish-start)/CLOCKS_PER_SEC; // �ð� ���

	for( i=0; i<count; i++){
		if(list[i] == s_num) break;
	}
	printf("%d ��°�� ����Ǿ� ����\n",i);
	printf("����Ž�� ���� �ӵ� : %lf\n",savetime);

	fclose(fp); // ������ �ݽ��ϴ�
	free(list); // �Ҵ� �ݳ�
	return 0;
}