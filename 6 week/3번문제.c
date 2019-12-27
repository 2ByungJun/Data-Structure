///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 4�� 10��
// ���α׷���   : ���� ���� ���α׷�
//   ��  ��     : �л� �� �й�,����,����,������ ������ data.txt ���Ͽ�
//                ����Ǿ� �ִ�. �� ������ �����͸� �о� �鿩 ��������
//                ���� ����ü �迭�� �����ϰ�, �л��� �й� �Ǵ� �̸���
//                �Է� �޾� �� �л��� ���� �� ����, ���, ����� ����϶�
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>  // malloc,free�� ���ֱ� ���� ���̺귯�� �Լ� 
#include <string.h>  // ���ڿ��� �ٷ�� ���̺귯�� �Լ�

typedef struct Student // Student ����ü ����
{
   char number[20];   // �й�
   char name[20];     // �̸�
   int korean;        // ����
   int english;       // ����
   int math;          // ����
}Student; // Animal�� ����

int main()
{
   Student *temp;      // tmep �����Ҵ� ����ü�迭 ����
   int F_line;         // ������ �о��� ���κ�������
   int count=0;        // ������ ���� ī�������� ����
   int i=0;            // �ݺ��� ������ ����
    char name_num[20];  // �й��� �̸��� ���� �迭
   int index;          // �й��� �̸��� ���Ͻ� ��ġ�� �������� ��
   int sum;            // ����
   double average;     // ���
   char rank[20];      // ������ ���ϱ����� ������ ������ �迭 
   int rank1=1;        // ����
   
   FILE *fp = fopen("data3.txt","r");  // data3.txt������ �б��������� ����
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

   temp = (Student *)malloc(sizeof(Student)*count); // temp ����ü �迭 �����Ҵ�
   if ( temp == NULL)      // �����Ҵ� ������ ����
   {
      printf("���� �޸� �Ҵ� ����\n"); // �����Ҵ� ������ ��¹���
      return 0;
   }

   rewind(fp); // ���� ������ �ʱ�ȭ
   while(!feof(fp))   // ���� �����Ͱ� ������ �����Ҷ����� �ݺ��ϴ� �ݺ���
   {
      // ����ü �迭�� �������� ���ϵ����Ͱ� ����
      fscanf(fp,"%s %s %d %d %d", temp[i].number, temp[i].name, &temp[i].korean, &temp[i].english,&temp[i].math);
	  rank[i] =  temp[i].korean + temp[i].english + temp[i].math; // rank[i]�迭�� ������ ����
	  i++; // i���� ����
   }

   // �л��� �̸��� �й����� ���� ã��
   printf("�л��� �̸� �Ǵ� �й��� �Է��ϼ��� : ");
   scanf("%s",&name_num);   // �л��̸� �Ǵ� �й��� �Է�
   for ( i=0; i<count; i++) // countũ���� �ݺ���
   {
      if( strcmp ( name_num , temp[i].name ) == 0 ){ // �Է��� �̸��� temp[i]�̸��� �񱳿��� ���� ���
         index = i; // index�� i�� ����
         break;     // �ݺ��� Ż��
      }
      if( strcmp ( name_num , temp[i].number ) == 0 ){ // �Է��� �й��� temp[i]�й��� ���ؼ� ���� ���
         index = i; // index�� i�� ����
         break;     // �ݺ��� Ż��
      }
   }

   sum = temp[index].korean + temp[index].english + temp[index].math;  // �Է��� �л��� ����
   average = (double)sum/count; // �Է��� �л��� ���
    for ( i=0; i<count; i++) // countũ���� �ݺ���
   {
      if(rank[index] < rank[i]) // �Է��� �л��� ���� < ������ �ο��� ������ ���ǽ�
         rank1++; // rank1���� �ö󰣴�
   }

   // �Է��� �л� ���� ���
   printf("�Է��Ͻ� �л� \"%s\"�л��� ������ �Ʒ��� �����ϴ�.\n" , temp[index].name ); // �Էµ� �л��̸� ���
   printf("| ��     �� | ���� | ���� | ���� | �� �� | �� �� | �� �� |\n");
   printf("| %s  |  %d  |  %d  |  %d  |  %d  | %.2lf |  %d/%d  |\n",temp[index].number,temp[index].korean,temp[index].english,temp[index].math,sum,(double)average,rank1,count);

   free(temp); // temp �����޸� �ݳ�
   fclose(fp); // ������ �ݾ��ش�
   return 0;
}
