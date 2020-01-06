///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 10�� 16��
// ���α׷���   : �� ���� ���α׷�
//   ��  ��     : data3.txt�� ����Ǿ� �ִ� �����͸� �ҷ���
//                ������������ �����Ͽ� ����Ͻÿ�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// ���� ����
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

int count=0; // ���� ������ ����(�������� ����)

// ���� �Լ�
// *list : ������ �迭
// left : �迭 ó���� ��Ÿ���� �ε���
// right : ( �迭 ��-1 )�� ��Ÿ���� �ε���
int partition(int *list,int left,int right)
{
	int pivot,temp;
	int low,high;
	int i;
	low = left;     // low�� ó����ġ�� ����
	high = right+1; // high�� �迭�� ���� ����
	pivot = list[left]; // pivot�� list �� ������ ����
	printf("-Pivot : %d-\n",pivot);
	do{
		do{ // low�� right���� �۰� list[low]���� pivot���� ���� ��
			low++; // low ����
		}while(low <= right && list[low]<pivot);

		do{ // high�� left���� ũ�� list[high]���� pivot���� Ŭ ��
			high--; // high ����
		}while(high >= left && list[high]>pivot);

		// list[low]�� ������ �����ƴ� pivot�� ����ų �� over
		if( list[low] != 15 )
			printf("low:%d  ",list[low]);
		else
			printf("low:over  ");
		printf("high:%d  ",list[high]);

		// ���� �ǽð� ��¹�
		printf("[");
		for(i=left; i<=right; i++)
			printf("%d > ",list[i]);
		printf("]\n\n");

		// low�� high���� ������� �����Ͱ� ����
		if(low<high){
			SWAP(list[low],list[high],temp);

		}
	}while(low<high);

	// pivot �缳���� ���� ����
	SWAP(list[left],list[high],temp);
	return high;
}

// �� ����
void quick_sort(int *list,int left,int right)
{
	if(left<right){
		int q=partition(list,left,right); // ����
		quick_sort(list,left,q-1);  // ���� ����
		quick_sort(list,q+1,right); // ������ ����
	}
}

int main()
{
	int *temp;    // ������ temp �����迭 ����
	int num;      // ���� �����Ͱ� ������ �޾� �� ����
	int i=0;      // �ݺ�����
	// ���� ����
	FILE *fp= fopen("data3.txt","r");
	if(fp == NULL){
		printf("���� ����\n");
		exit(1);
	}
	// ���� ������ ����üũ
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		count++;
	}
	// ���� �Ҵ�
	temp = (int *)malloc(sizeof(int)*count);

	// ���������� ����
	rewind(fp);
	// temp[i]�� ���� �����Ͱ� ����
	while(!feof(fp)){
		fscanf(fp,"%d",&num);
		temp[i] = num;
		i++;
	}

	// ���ĵ��� ���� ����Ʈ ���
	printf("< ���ĵ��� ���� ����Ʈ >\n");
	for(i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n\n");

	// ������ ���
	printf("< ���� ����>\n");
	quick_sort(temp,0,count-1);
	
	// ���ĵ� ����Ʈ ���
	printf("< ���ĵ� ����Ʈ >\n");
	for(i=0; i<count; i++)
		printf("%d > ",temp[i]);
	printf("\n");

	free(temp); // temp �����ݳ�
	fclose(fp); // fp ������ �ݽ��ϴ�.
	return 0;
}