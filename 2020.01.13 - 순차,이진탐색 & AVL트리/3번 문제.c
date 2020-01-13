///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 12월 4일
// 프로그램명   : AVL 트리
//   설  명     : data.txt에 단어의 정보를 입력에 따라 AVL트리에 저장하고
//                탐색하여 의미를 출력하라. 모든 입력 및 출력이 끝나면 AVL
//                트리를 모두 출력하는 프로그램을 작성하라.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// max정의
#define max(x,y) (x) > (y) ? (x) : (y)

// AvlNode 구조체 생성
typedef struct Avlnode {
	char data[20];
	char mean[20];
	struct Avlnode *left_child, *right_child;
}AvlNode;
// root 전역변수 선언
AvlNode *root;

// LL 회전함수
AvlNode *rotate_LL(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}
// RR 회전함수
AvlNode *rotate_RR(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// RL 회전함수
AvlNode *rotate_RL(AvlNode *parent){
	AvlNode *child = parent->right_child;
	parent->right_child = rotate_LL(child); // LL회전
	return rotate_RR(parent); // RR회전
}
// LR 회전함수
AvlNode *rotate_LR(AvlNode *parent){
	AvlNode *child = parent->left_child;
	parent->left_child = rotate_RR(child); // RR회전
	return rotate_LL(parent); // LL회전
}

// 트리의 높이 반환
int get_height(AvlNode *node)
{
	int height=0;
	if( node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}
// 노드의 균형인수 반환
int get_height_diff(AvlNode *node)
{
	if( node == NULL ) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
}

// 트리를 균형 트리로 만드는 함수
AvlNode *rebalance(AvlNode **node)
{
	int height_diff = get_height_diff(*node); // 균형인수로 초기화
	if( height_diff > 1){ // 1보다 클 경우(회전필요)
		if(get_height_diff((*node)->left_child) > 0) // 왼쪽 자식노드가 존재할 경우
			*node = rotate_LL(*node);
		else
			*node = rotate_LR(*node);
	}
	else if( height_diff < -1 ) { // -1보다 작을 경우(회전필요)
		if(get_height_diff((*node)->right_child) < 0) // 오른쪽 자식노드가 존재할 경우
			*node = rotate_RR(*node); // RR회전
		else
			*node = rotate_RL(*node); // RL회전
	}
	return *node;
}
// AVL 트리의 삽입 연산
AvlNode *avl_add(AvlNode **root, AvlNode new_key)
{
	if( *root == NULL ){ // root가 NULL경우
		// 동적할당
		*root = (AvlNode *)malloc(sizeof(AvlNode));
		if( *root == NULL ){
			fprintf(stderr,"메모리 할당 에러\n");
			exit(1);
		}
		strcpy((*root)->data, new_key.data); // new_key 복사
		strcpy((*root)->mean, new_key.mean); // new_key 복사
		(*root)->left_child = (*root)->right_child = NULL; // 링크 초기화
	}
	else if( strcmp(new_key.data,(*root)->data) < 0 ){ // 새로운 노드가 기존보다 작을 경우
		(*root)->left_child = avl_add( &((*root)->left_child), new_key);
		*root = rebalance(root);
	}
	else if( strcmp(new_key.data,(*root)->data) > 0){ // 새로운 노드가 기존보다 클 경우
		(*root)->right_child = avl_add( &((*root)->right_child), new_key);
		*root = rebalance(root);
	} 
	else{
		fprintf(stderr,"중복된 키 에러\n");
		exit(1);
	}
	return *root;
}

// AVL 트리의 탐색 함수
AvlNode *avl_search(AvlNode *node,AvlNode key)
{
	if( node == NULL ) return NULL;
	if( strcmp(key.data, node->data) == 0 )        // key가 비교 노드보다 같을 경우
		return node;                               // 탐색 성공시 node 반환
	else if( strcmp(key.data, node->data) < 0)     // key가 비교 노드보다 작을 경우(왼쪽이동)
		return avl_search(node->left_child, key); 
	else                                           // key가 비교 노드보다 클 경우(오른쪽이동)
		return avl_search(node->right_child, key); 
}
// 중위순회 출력
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
	char ch; // i와s 판단
	AvlNode temp, *search_node; // 삽입용 temp,탐색결과 노드 
	// data3.txt 읽기 형식으로 오픈
	FILE *fp = fopen("data3.txt","r");
	if(fp == NULL)
	{
		printf("파일 에러\n");
		exit(1);
	}

	while(!feof(fp)){
		fscanf(fp,"%c ",&ch);
		switch(ch){
		// 삽입
		case 'i':
			fscanf(fp, "%s %s", temp.data, temp.mean);
			avl_add(&root, temp);
			break;
		// 탐색
		case 's':
			fscanf(fp, "%s", temp.data);
			printf("< %s의 의미 탐색 >\n", temp.data);
			search_node = avl_search(root, temp);
			printf("%s-%s\n\n", search_node->data, search_node->mean);
			break;
		}
	}
	// 트리 출력
	printf("< AVL 트리 출력 >\n");
	display(root);
	printf("\n");

	fclose(fp); // 파일을 닫습니다
	return 0;   // 종료
}