///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 27��
// ���α׷���   : ü�̴��� �̿��� HashTable
//   ��  ��     : data.txt�� ����� �������� ü�̴��� �̿��� HashTable
//                �� �����϶�. �Ŀ� ���ǿ� �°� ����ϴ� ���α׷�
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // ���̺� ������

// ���Ǻ�
#define empty(e) (e.key == 0)
#define equal(e1,e2) (e1 == e2)

// element ����
typedef struct element{
	int key;
}element;

// ListNode ����
typedef struct ListNode{
	element item;
	struct ListNode *link;
}ListNode;

// ListNode�� �ؽ� ���̺� ����
ListNode *hash_table[TABLE_SIZE]={NULL};

// �ؽ� �Լ�
int hash_function(int key)
{
	int hash_index = key % 7;
	if(hash_index < 0)
		hash_index += 7;
	return hash_index;
}
// �ؽ� ü�̴� ����
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *ptr;                   // ����Ʈ ���
	ListNode *node_before=NULL;      // �� ���
	ListNode *node = ht[hash_value]; // ���ο� ���

	node_before = node;

	for(; node; node_before=node, node = node->link){
		if(equal(node->item.key,item.key)){
			fprintf(stderr,"�̹� Ž�� Ű�� ����Ǿ� ����\n");
			return;
		}
	}
	// ���ο� ��� ����
	ptr = (ListNode *)malloc(sizeof(ListNode));
	ptr->item = item;
	ptr->link = NULL;
	// �� ���� ����
	if(node_before)
		node_before->link = ptr;
	else{
		ht[hash_value] = ptr;
	}
}
// �ؽ� ü�̴� Ž��
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;
	int i=0;
	int hash_value = i = hash_function(item.key);

	// ��� Ž��
	for(node = ht[hash_value]; node; node = node->link){
		// �����尪�� ����Ű�� ��尪�� ���� ���
		if(equal(node->item.key,item.key)){
			printf("%3d�� �˻� ��� - HashTable[%d] : ",item.key,i);
			node = ht[hash_value];
			// ��� ��¹�
			while(node != NULL){
				printf("(%d) - > ",node->item.key);	
				// �����尪�� ����Ű�� ��尪�� ���� ��� �ٹٲ�
				if(equal(node->item.key ,item.key)){
					printf("\n");
					return;
				}
				node = node->link; // ���� ����		
			}			
		}		
	}
	// ���� ���
	printf(" �Է��Ͻ� �� %d �� HashTable���� �˻����� �ʾҽ��ϴ�. \n",item.key);
}

int main()
{
	element tmp; // ����ü tmp
	char ch;     // i�� s�Ǵ�

	// data3.txt�� �б� �������� ����
	FILE *fp = fopen("data3.txt","r");
	if(fp == NULL){
		printf("���� ���� ����");
		exit(1);
	}
    // ���̺� ũ��
	printf("< HashTable Size = [%d] >\n\n",TABLE_SIZE);

	// ���̺� ����
	printf("< Data Insert Finish >\n");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(ch=='i'){
			fscanf(fp,"%d",&tmp.key);
			hash_chain_add(tmp,hash_table); // ����
		}
		else if(ch =='s'){
			fscanf(fp,"%d",&tmp.key);
		}
	}
	printf("\n\n");

	// ���̺� Ž��
	rewind(fp);
	printf("< Find Data Location >\n");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&ch);
		if(ch=='i'){
			fscanf(fp,"%d",&tmp.key);

		}
		else if(ch =='s'){
			fscanf(fp,"%d",&tmp.key);
			hash_chain_find(tmp,hash_table); // Ž��
		}
	}

	printf("< Finish >\n\n");
	fclose(fp); // ������ �ݽ��ϴ�
	return 0;   // ����
}