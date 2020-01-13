///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 12�� 4��
// ���α׷���   : AVL Ʈ��
//   ��  ��     : data.txt�� �ܾ��� ������ �Է¿� ���� AVLƮ���� �����ϰ�
//                Ž���Ͽ� �ǹ̸� ����϶�. ��� �Է� �� ����� ������ AVL
//                Ʈ���� ��� ����ϴ� ���α׷��� �ۼ��϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max����
#define max(x,y) (x) > (y) ? (x) : (y)

// AvlNode ����ü ����
typedef struct Avlnode {
	char data[20];
	char mean[20];
	struct Avlnode *left_child, *right_child;
}AvlNode;
// root �������� ����
AvlNode *root;

// LL ȸ���Լ�
AvlNode *rotate_LL(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// RR ȸ���Լ�
AvlNode *rotate_RR(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// RL ȸ���Լ�
AvlNode *rotate_RL(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->right_child = rotate_LL(child); // LLȸ��
	return rotate_RR(parent); // RRȸ��
}
// LR ȸ���Լ�
AvlNode *rotate_LR(AvlNode *parent){
	AvlNode *child = parent->left_child;
	parent->left_child = rotate_RR(child); // RRȸ��
	return rotate_LL(parent); // LLȸ��
}

// Ʈ���� ���� ��ȯ
int get_height(AvlNode *node)
{
	int height=0;
	if( node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}
// ����� �����μ� ��ȯ
int get_height_diff(AvlNode *node)
{
	if( node == NULL ) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// Ʈ���� ���� Ʈ���� ����� �Լ�
AvlNode *rebalance(AvlNode **node)
{
	int height_diff = get_height_diff(*node); // �����μ��� �ʱ�ȭ
	if( height_diff > 1){ // 1���� Ŭ ���(ȸ���ʿ�)
		if(get_height_diff((*node)->left_child) > 0) // ���� �ڽĳ�尡 ������ ���
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if( height_diff < -1 ) { // -1���� ���� ���(ȸ���ʿ�)
		if(get_height_diff((*node)->right_child) < 0) // ������ �ڽĳ�尡 ������ ���
			*node = rotate_RR(*node); // RRȸ��
		else
			*node = rotate_RL(*node); // RLȸ��
	}
	return *node;
}
// AVL Ʈ���� ���� ����
AvlNode *avl_add(AvlNode **root, AvlNode new_key)
{
	if( *root == NULL ){ // root�� NULL���
		// �����Ҵ�
		*root = (AvlNode *)malloc(sizeof(AvlNode));
		if( *root == NULL ){
			fprintf(stderr,"�޸� �Ҵ� ����\n");
			exit(1);
		}
		strcpy((*root)->data, new_key.data); // new_key ����
		strcpy((*root)->mean, new_key.mean); // new_key ����
		(*root)->left_child = (*root)->right_child = NULL; // ��ũ �ʱ�ȭ
	}
	else if( strcmp(new_key.data,(*root)->data) < 0 ){ // ���ο� ��尡 �������� ���� ���
		(*root)->left_child = avl_add( &((*root)->left_child), new_key);
		*root = rebalance(root);
	}
	else if( strcmp(new_key.data,(*root)->data) > 0){ // ���ο� ��尡 �������� Ŭ ���
		(*root)->right_child = avl_add( &((*root)->right_child), new_key);
		*root = rebalance(root);
	} 
	else{
		fprintf(stderr,"�ߺ��� Ű ����\n");
		exit(1);
	}
	return *root;
}

// AVL Ʈ���� Ž�� �Լ�
AvlNode *avl_search(AvlNode *node,AvlNode key)
{
	if( node == NULL ) return NULL;
	if( strcmp(key.data, node->data) == 0 )        // key�� �� ��庸�� ���� ���
		return node;                               // Ž�� ������ node ��ȯ
	else if( strcmp(key.data, node->data) < 0)     // key�� �� ��庸�� ���� ���(�����̵�)
		return avl_search(node->left_child, key); 
	else                                           // key�� �� ��庸�� Ŭ ���(�������̵�)
		return avl_search(node->right_child, key); 
}
// ������ȸ ���
void display(AvlNode *node)
{
	   if(node != NULL){
      printf(" | ");
	  display(node->left_child);
      printf("%s-%s", node->data, node->mean);
	  display(node->right_child);
      printf(" | ");
   }
}

int main()
{
	char ch; // i��s �Ǵ�
	AvlNode temp, *search_node; // ���Կ� temp,Ž����� ��� 
	// data3.txt �б� �������� ����
	FILE *fp = fopen("data3.txt","r");
	if(fp == NULL)
	{
		printf("���� ����\n");
		exit(1);
	}

	while(!feof(fp)){
		fscanf(fp,"%c ",&ch);
		switch(ch){
		// ����
		case 'i':
			fscanf(fp, "%s %s", temp.data, temp.mean);
			avl_add(&root, temp);
			break;
		// Ž��
		case 's':
			fscanf(fp, "%s", temp.data);
			printf("< %s�� �ǹ� Ž�� >\n", temp.data);
			search_node = avl_search(root, temp);
			printf("%s-%s\n\n", search_node->data, search_node->mean);
			break;
		}
	}
	// Ʈ�� ���
	printf("< AVL Ʈ�� ��� >\n");
	display(root);
	printf("\n");

	fclose(fp); // ������ �ݽ��ϴ�
	return 0;   // ����
}