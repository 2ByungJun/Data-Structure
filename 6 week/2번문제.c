///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 10��
// ���α׷���   : ����ü �迭
//   ��  ��     : ���������� ������ �����ϴ� ���α׷��� ����Ϸ� �Ѵ�.
//                ������ ��, ������ȣ, ��ġ, ���� ���Ͽ� �����ϰ�
//                ����Ϸ� �Ѵ�. �̸� ���� �Ҵ����� ����ü �迭��
//                �����ϰ� �˻��ϴ� ���α׷��� �ۼ��Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h> 
#include <stdlib.h>  // malloc,free�� ���ֱ� ���� ���̺귯�� �Լ� 
#include <string.h>  // ���ڿ��� �ٷ�� ���̺귯�� �Լ�

typedef struct Animal // Animal����ü ����
{
	char animal[20];  // ��
	char num[20];     // ������ȣ
	char area[20];    // ��ġ
	char total[20];   // ��ü ��
}Animal; // Animal�� ����

int main()
{
    Animal *tmep;     // tmep �����Ҵ� ����ü�迭 ����
	int F_line; // ������ �о��� ���κ�������
	int count = 0;    // ������ ���� ī�������� ����
	int i=0 , j=0;    // �ݺ��� ������ ����
	int select;       // �˻��� ������ �Է��� ����
	char type[20];    // �˻����� ������ �迭

	FILE *fp = fopen("data2.txt","r");  // data2.txt������ �б��������� ����
	if(fp == NULL)                      // ���� ������ ��¹���
	{
		printf("������ ���� ���߽��ϴ�.\n");
		return 0;
	}
	
	while(!feof(fp))   // ���� �����Ͱ� ������ �����Ҷ����� �ݺ��ϴ� �ݺ���
	{
		F_line = fgetc(fp);
		if(F_line == '\n')
			count++; // �����Ͱ� ī���� ������
	}
	count++; // ������ ���� ī��Ʈ ����

	tmep = (Animal *)malloc(sizeof(Animal)*count); // temp ����ü �迭 �����Ҵ�
	if ( tmep == NULL)      // �����Ҵ� ������ ����
	{
		printf("���� �޸� �Ҵ� ����\n"); // �����Ҵ� ������ ��¹���
		return 0;
	}
	
	rewind(fp); // ���� ������ �ʱ�ȭ
	while(!feof(fp))   // ���� �����Ͱ� ������ �����Ҷ����� �ݺ��ϴ� �ݺ���
	{
		// ����ü �迭�� �������� ���ϵ����Ͱ� ����
		fscanf(fp,"%s %s %s %s", tmep[i].animal, tmep[i].num, tmep[i].area, tmep[i].total);
		i++; // i���� ����
	}

	printf("�˻��Ͻ� ������ �����Ͽ� �ֽʽÿ�.\n");
	printf("< 1.��  2.������ȣ  3.��ġ  4.��ü �� >\n");
	scanf("%d",&select);  // �˻��� ������ �Է��� select�� ���� 

	printf("�˻��Ͻ� ������ �Է��Ͽ� �ֽʽÿ� : ");
	scanf("%s",&type);  // �˻��� ������ �Է��� type �迭�� ���� 

	while( j < count)
	{
		if( ( strcmp(type , tmep[j].animal ) == 0 ) ) { // ���� �˻��� ����(type)�� ���ٸ�
			select = j; // j���� select�� ����
			break;      // �ݺ��� Ż��
		}
		if( ( strcmp(type , tmep[j].num ) == 0 ) )  { // ������ȣ�� �˻��� ����(type)�� ���ٸ�
			select = j; // j���� select�� ����
			break;      // �ݺ��� Ż��
		}
		if( ( strcmp(type , tmep[j].area ) == 0 ) ) { // ��ġ�� �˻��� ����(type)�� ���ٸ�
			select = j;	// j���� select�� ����
			break;     // �ݺ��� Ż��
		}
		if( ( strcmp(type , tmep[j].total ) == 0 ) ) { // ��ü ���� �˻��� ����(type)�� ���ٸ�
			select = j; // j���� select�� ����
			break;      // �ݺ��� Ż��
		}
		j++; // j�� ����
	}

	printf("�� : %s \n",tmep[select].animal);    // �ش� �� ���
	printf("������ȣ : %s \n",tmep[select].num); // �ش� ������ȣ ���
	printf("��ġ : %s \n",tmep[select].area);    // �ش� ��ġ ���
	printf("��ü �� : %s \n",tmep[select].total);// �ش� ��ü �� ���
	
	free(tmep); // ���� �޸� �ݳ�
	fclose(fp); // ������ �ݾ��ش�
	return 0;
}