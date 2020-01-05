///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 9�� 27��
// ���α׷���   : ���� ���� Ʈ�� ����
//   ��  ��     : data.txt���� ������ �̷���� ������ �о�� ���� Ʈ����
//                �����ϰ� ������ Ʈ���� ���� ���� Ʈ������ �ƴ��� ����.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

typedef int element;
// ����� ����
typedef struct TreeNode {
	element key;
	struct TreeNode *left,*right;
} TreeNode;

int count = 0; // ��� ����

// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�.
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t; // p�� �θ���, t�� �ڽĳ��
	TreeNode *n;     // n�� ���ο� ���

	t = *root;
	p = NULL;
	// Ž���� ���� ����
	while(t != NULL ){
		if( key == t->key) return;
		p = t;
		if(key < p->key)
			t = p->left;
		else
			t = p->right;

	}
	// item�� Ʈ�� �ȿ� �����Ƿ� ���� ����
	n = (TreeNode*)malloc(sizeof(TreeNode));

	if(n == NULL) return;
	n->key = key; // ������ ����
	count++; // ��� ���� ����
	printf("Inserted %d\n",n->key);

	n->left = n->right = NULL;
	// �θ� ���� ��ũ ����
	if( p != NULL )
		if( key < p->key )
			p->left = n;
		else p->right = n;
	else *root = n;
}

// ���� ��ȸ
void preorder( TreeNode *root ){
	if ( root ){
		printf("%d ",root->key);  // ��� �湮
		preorder( root->left);  // ���� ���� Ʈ�� ��ȸ
		preorder( root->right); // ������ ���� Ʈ�� ��ȸ
	}
}

// Ʈ�� ���̰� ������ �Ǵ� �Լ�
int get_height(TreeNode *root){
	int left_h;  // �� ����
	int right_h; // �� ����
	if(!root)
		return 0;
	else {
		left_h = get_height(root->left);  // ���ʸ�ũ �̵�
		right_h = get_height(root->right);// �����ʸ�ũ �̵�
		return 1 + ( left_h > right_h ? left_h : right_h); // ���̰� ū ���� ����
	}
}

int main()
{
	TreeNode *root=NULL; // Ʈ�� ����
	int num;             // ���� ����
	int file_count=0;    // ���ϵ����� ����

	// data2������ �б��������� ����
	FILE *fp = fopen("data2.txt","r");
	if( fp == NULL ){ // ���� ������
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 1;
	}

	while(!feof(fp)){
		fscanf(fp,"%d",&num); 
		insert_node(&root,num); // ����
		file_count++; // ���ϵ����� ���� 
	}

	// ���� ��ȸ ���
	printf("Preorder >> ");
	preorder(root);
	printf("\n");

	// ���̿� ���� ��������Ʈ�� ����
	if( pow(2,get_height(root))-1 == count )
	{
		if( count == file_count) // ��尹���� ���� ������ ���� ���
			printf("���� ���� Ž��Ʈ���Դϴ�.\n");
	}
	else
		printf("���� ���� Ž��Ʈ���� �ƴմϴ�.\n");

	fclose(fp); // ������ �ݾ��ش�
	return 0;
}