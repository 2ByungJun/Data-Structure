///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 27��
// ���α׷���   : ����������� �̿��� HashTable
//   ��  ��     : data.txt�� ����� �������� ���� ������� �̿��� HashTable
//                �� �����϶�. �Ŀ� ���ǿ� �°� ����ϴ� ���α׷�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

// ����
#define TABLE_SIZE 10  
#define empty(e) (e.key == 0)

// element ����ü
typedef struct {
	int key; // ������ key
}element;

// key���� ���� Hash_table�迭
element hash_table[TABLE_SIZE];

// Hash_table �ʱ�ȭ
void init_table(element *ht)
{
	int i;
	for(i=0; i<TABLE_SIZE; i++) {
		ht[i].key=NULL;
	}
}

// hash �Լ�
int hash_function(int key)
{
	return key%7;
}

// hash ����
void hash_lp_add(element item,element *ht)
{
	int i,hash_value;

	hash_value = i = hash_function(item.key); // hash_function() ������ �ʱ�ȭ

	while(!empty(ht[i])){
		if(item.key != ht[i].key){ // �浿 ��
			printf("data = %d ���� ���� Hashtaable : %d ���� �浹 ���� ", item.key, i);
		}
		i = (i+1) % TABLE_SIZE; // i ����
		printf("- index = %d�� �����Ͽ����ϴ�.\n",i);
		if(i == hash_value) { // ���̺��� �ʰ��� ��
			fprintf(stderr,"���̺��� ����á���ϴ�\n");
			return;
		}
	}
	ht[i] = item; // item ����
}

// Hash Ž��
void hash_lp_search(element item, element *ht)
{
	int i,hash_value;

	hash_value = i = hash_function(item.key);

	while(!empty(ht[i])) 
	{
		if(item.key == ht[i].key ){ // �˻��� ���
			printf("%2d �� HashTable : %d ���� �˻��Ǿ����ϴ�..\n",item.key,i);
			return;
		}
		i = (i+1) % TABLE_SIZE; // i+1�� �� ���
	}
	if(item.key != ht[i].key) // �˻����� ���� ���
	{
		printf("�Է��Ͻ� �� %d �� HashTable���� �˻������ʾҽ��ϴ�.\n",item.key);
	}
}

int main()
{
	element tmp; // ����ü tmp
	char ch;     // i�� s �Ǵ�
	int z = 0;   // ��¹� ���Ǻ���

	// data1.txt�� �б��������� ����
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}
	
	// HashTable Size ���
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);
    
	// Date Insert Finish 
	printf("< Date Insert Finish >\n");
	while(!feof(fp))
	{
		fscanf(fp," %c",&ch);
		if( ch == 'i')
		{
			fscanf(fp,"%d",&tmp.key);
			hash_lp_add(tmp,hash_table); // hash ����
		}
		else if( ch == 's') 
		{
			// Find Data Location
			if( z == 0 )
			{
				printf("\n< Find Data Location >\n");
				z++;
			}
			fscanf(fp,"%d",&tmp.key);
			hash_lp_search(tmp,hash_table); // hash Ž��
		}
	}

	printf("< Finish >\n\n");

	fclose(fp); // ������ �ݽ��ϴ�
	return 0;   // ����
}