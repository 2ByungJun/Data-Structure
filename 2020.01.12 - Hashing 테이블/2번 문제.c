///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 12�� 1��
// ���α׷���   : ����������� �̿��� HashTable ����
//   ��  ��     : data.txt�� ����� �ܾ�� �ǹ̵��� ��� ������ �̿��Ͽ�
//                ��ȯ �� ����������� �̿��� HashTable�� �����ϰ� ����
//                �������� �浹�� �Ͼ�ٸ� �Ʒ��� ���� �浹 ���� ������
//                ����ϴ� ���α׷�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10 // ���̺� ������
#define SIZE 20
#define empty(e) (e.value == 0)
#define equal(e1,e2) (e1 == e2)

typedef struct element{
	char key[TABLE_SIZE]; // �ܾ�
	char name[TABLE_SIZE];// ��
	int value;            // ������� �� ��
}element;

element hash_table[TABLE_SIZE];	// �ؽ� ���̺�

// ���̺� �ʱ�ȭ �Լ�
void init_table(element ht[])
{
	int i;
	for(i=0; i<TABLE_SIZE; i++){
		ht[i].key[0] = NULL; // �ܾ� �ʱ�ȭ
	}
}
// �ؽ� �Լ�
int hash_function(int key)
{
	int hash_index = key % 7; // ��ġ
	if(hash_index < 0) // 0���� ������� +�Ͽ� ��ġ����
		hash_index += 7;
	return hash_index; // ��ġ ��ȯ
}

// �ؽ� ����
void hash_lp_add(element item, element *ht)
{
	int i, hash_value;
	int inc=1;

	hash_value = i = hash_function(item.value);

	while(!empty(ht[i])){
		if(equal(item.value, ht[i].value)){
			fprintf(stderr,"Ž��Ű�� �ߺ��Ǿ����ϴ�.\n");
			return;
		}
		printf("data = %s ���� ���� HashTable : %d ���� �浹���� ",item.key,i);
		
		i = (i +inc*inc) % 7;
		inc = inc+1;

		printf("- index = %d �� �����Ͽ����ϴ�.\n",i);

	
	}
	ht[i] = item;
}

// ������� �Լ�
int boundary_function(char *key)
{
	char s[SIZE];   // �ܾ �ϳ��� �����ϴ� ����
	int sum=0, i;    

	for(i=0; i<SIZE; i++)
	{
		if(key[i] ==NULL) // NULL�� ��� break
			break;

		if(i%2 == 0){ // Ȧ�� ��°�� ���
			sprintf(s,"%d",key[i]);
			sum += atoi(s);
		}
		else { // ¦�� ��°�� ���
			sprintf(s,"%d",key[i]); // key�ܾ �����Ͽ� s[]�� ���� 
			strrev(s);      // ���ڿ� ����
			sum += atoi(s); // �ƽ�Ű �ڵ� �� ���� ��
		}	
	}
	return sum;
}

// �ؽ� ���̺� ���
void hash_Ip_print(element *ht)
{
	int i;
	for(i=0; i<TABLE_SIZE; i++){
		if(ht[i].key[0] != NULL) // ���� NULL�� �ƴѰ��
			printf("hashtable[%d] - %s > %s\n",i ,ht[i].key ,ht[i].name);
		else // NULL ��� ���
			printf("hashtable[%d] - %s\n",i ,ht[i].key);
	}
}

int main()
{
	element tmp;     // ����ü tmp
	char name[SIZE]; // ������� ��� �ܾ�
	int list[SIZE];  // ��������Լ� ������ �����ϴ� �迭
	int count=0;   // �ݺ�����

	// data1.txt�� �б��������� ����
	FILE *fp = fopen("data2.txt","r");
	if(fp == NULL){
		printf("���� ����\n");
		exit(1);
	}

	// ���̺� �ʱ�ȭ
	init_table(hash_table);

	// ���̺� ũ��
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);

	// list�� �ܾ� ����
	printf("< Data Insert Finish >\n");	
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&tmp.key, &tmp.name);	
		strcpy(name,tmp.key);                 // name�迭�� ������ ���� '�ܾ�' ����
		list[count]= boundary_function(name); // ��������� ����Ͽ� ���� �迭�� ����
		count++;
	}

	// �ؽ� ���̺� ������ ����
	rewind(fp); // ���� �ʱ�ȭ
	count =0;   // count �ʱ�ȭ
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",&tmp.key, &tmp.name);		
		tmp.value = list[count];     // list������ tmp.value�� ����
		hash_lp_add(tmp,hash_table); // tmp�� �ؽ����̺� ����
		count++;
	}

	// �ؽ� ���̺� ���
	printf("\n\n< table >\n");
	hash_Ip_print(hash_table);

	printf("< Finish >\n\n");
	fclose(fp); // ������ �ݽ��ϴ�
	return 0;   // ����
}