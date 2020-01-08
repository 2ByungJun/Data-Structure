///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 2��
// ���α׷���   : �պ� ���� ���α׷�
//   ��  ��     : data2.txt�� ����Ǿ� �ִ� �����͸� �ҷ��� �������� ����
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

int *sorted; // �պ����� �ӽð��� �迭

// �պ� ����
// list   : ���Ľ�ų �迭
// left   : �κ� �迭�� ù ���ڵ�
// mid    : ���� ����
// right  : �κ� �迭�� ������ ���ڵ�
void merge(int *list,int left,int mid,int right)
{
	int i,j,k,l;
	i=left; j=mid+1; k=left;

	/*���� ���ĵ� list�� �պ�*/
	while(i<=mid && j<=right){
		if(list[i]<=list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}
	if(i>mid) // ���� �ִ� ���ڵ��� �ϰ� ����
		for(l=j; l<=right; l++)
			sorted[k++] = list[l];
	else
		for(l=i; l<=mid; l++)
			sorted[k++] = list[l];
	// �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹��
	for(l=left; l<=right; l++)
		list[l] = sorted[l];
}
// list : ���Ľ�ų �迭
// left : �κ� �迭�� ù ���ڵ�
// right : �κ� �迭�� ������ ���ڵ� (�Լ� ����ϱ� ���� right���� �迭 MAX_SIZE-1�� �޴´�.)
void merge_sort(int *list,int left,int right)
{
	int mid;
	int i;
	if(left<right){
		mid = (left+right)/2;         // ����Ʈ �յ� ����
		merge_sort(list,left,mid);    // �κ� ����Ʈ ����
		merge_sort(list,mid+1,right); // �κ� ����Ʈ ����
		// ���� �κ� ����Ʈ ���
		printf("\nLeft list : ");     
		for( i = left; i<=mid; i++)
			printf("%d ",list[i]);
		// ������ �κ� ����Ʈ ���
		printf("\nRight list : ");    
		for( i = mid+1; i<=right; i++)
			printf("%d ",list[i]);

		merge(list,left,mid,right);   // �պ�
		// �պ���� ���
		printf("\nSorted list : ");   
		for( i = left; i<=right; i++)
			printf("%d ",list[i]);

		printf("\n");
	}
}

// ���
// list : ��½�ų �迭
// count: ���ϵ����� ����
void dispaly(int *list,int count)
{
	int i;
	for( i=0; i<count; i++)
		printf("<%d> ",list[i]);
	printf("\n");
}

int main()
{
	int *list;   // ����Ʈ ����
	int num;     // ���� ������ �� ����
	int count=0; // ���� ������ ����
	int j=0;     // �ݺ� ����

	// data2.txt �б�
	FILE *fp = fopen("data2.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}

	// ���ϵ����� ���� �ľ�
	while(!feof(fp)){
		fscanf(fp,"%d ",&num);
		count++;
	}

	// ���� �Ҵ�
	list = (int *)malloc(sizeof(int)*count);
	sorted = (int *)malloc(sizeof(int)*count);

	// ���� ������ list�� ����
	rewind(fp);
	while(!feof(fp)){
		fscanf(fp,"%d ",&num);
		list[j] = num;
		j++;
	}

	// ���� �� ����Ʈ ���
	printf("<< ���ĵ��� ���� ����Ʈ >>\n");
	dispaly(list,count);

	// �պ� ���� �� ���� ���
	printf("<< ���� ���� >>\n");
	printf("-----------------------------------------------\n");
	merge_sort(list,0,count-1);
	printf("-----------------------------------------------\n");
	
	// ���ĵ� ����Ʈ ���
	printf("<< ���ĵ� ����Ʈ >>\n");
	dispaly(list,count);

	fclose(fp);  // ������ �ݾ��ش�
	free(sorted);// sorted �����Ҵ� �ݳ�
	free(list);  // list �����Ҵ� �ݳ�
	return 0;
}
