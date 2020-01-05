///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 9월 27일
// 프로그램명   : 완전 이진 트리 검증
//   설  명     : data.txt에서 정수로 이루어진 정보를 읽어와 이진 트리를
//                생성하고 생성된 트리가 완전 이진 트리인지 아닌지 검증.
//  수강과목    : 자료구조2 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

typedef int element;
// 노드의 구조
typedef struct TreeNode {
	element key;
	struct TreeNode *left,*right;
} TreeNode;

int count = 0; // 노드 개수

// key를 이진 탐색 트리 root에 삽입한다.
// key가 이미 root안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t; // p는 부모노드, t는 자식노드
	TreeNode *n;     // n은 새로운 노드

	t = *root;
	p = NULL;
	// 탐색을 먼저 수행
	while(t != NULL ){
		if( key == t->key) return;
		p = t;
		if(key < p->key)
			t = p->left;
		else
			t = p->right;

	}
	// item이 트리 안에 없으므로 삽입 가능
	n = (TreeNode*)malloc(sizeof(TreeNode));

	if(n == NULL) return;
	n->key = key; // 데이터 복사
	count++; // 노드 개수 증가
	printf("Inserted %d\n",n->key);

	n->left = n->right = NULL;
	// 부모 노드와 링크 연결
	if( p != NULL )
		if( key < p->key )
			p->left = n;
		else p->right = n;
	else *root = n;
}

// 전위 순회
void preorder( TreeNode *root ){
	if ( root ){
		printf("%d ",root->key);  // 노드 방문
		preorder( root->left);  // 왼쪽 서브 트리 순회
		preorder( root->right); // 오른쪽 서브 트리 순회
	}
}

// 트리 높이가 같은지 판단 함수
int get_height(TreeNode *root){
	int left_h;  // 좌 높이
	int right_h; // 우 높이
	if(!root)
		return 0;
	else {
		left_h = get_height(root->left);  // 왼쪽링크 이동
		right_h = get_height(root->right);// 오른쪽링크 이동
		return 1 + ( left_h > right_h ? left_h : right_h); // 높이가 큰 쪽을 리턴
	}
}

int main()
{
	TreeNode *root=NULL; // 트리 변수
	int num;             // 정수 변수
	int file_count=0;    // 파일데이터 개수

	// data2파일을 읽기형식으로 오픈
	FILE *fp = fopen("data2.txt","r");
	if( fp == NULL ){ // 파일 에러시
		printf("파일이 열리지 않았습니다.\n");
		return 1;
	}

	while(!feof(fp)){
		fscanf(fp,"%d",&num); 
		insert_node(&root,num); // 삽입
		file_count++; // 파일데이터 개수 
	}

	// 전위 순회 출력
	printf("Preorder >> ");
	preorder(root);
	printf("\n");

	// 높이에 따른 완전이진트리 유무
	if( pow(2,get_height(root))-1 == count )
	{
		if( count == file_count) // 노드갯수가 파일 개수와 같을 경우
			printf("완전 이진 탐색트리입니다.\n");
	}
	else
		printf("완전 이진 탐색트리가 아닙니다.\n");

	fclose(fp); // 파일을 닫아준다
	return 0;
}