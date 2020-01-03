///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 13일
// 프로그램명   : 포인터로 구현된 단순 연결리스트
//   설  명     : Data.txt파일에 저장된 정보를 원형 연결 리스트에 저장하고 
//                172를 가진 노드를 삭제한뒤 역순화하여 첫 노드,마지막 
//                노드,마지막 노드의 링크가 가리키고 있는 노드의 값을 출력하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int element;
// 구조체 생성
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;

// 오류 출력
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}
// 동적으로 노드를 생성
ListNode *create_node(element data,ListNode *link) 
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("메모리 할당 에러");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// 삽입함수
void insert_last(ListNode **phead, ListNode *node)
{
    if (*phead == NULL) { // *phead가 NULL경우
        *phead = node;
        node->link = node;
    }
    else { // *phead가 NULL이 아닐 경우
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node;
    }
}
// 삭제함수
void remove_first(ListNode **phead)
{
    ListNode* removed;
    if (*phead == NULL) return;      //공백리스트인 경우 삭제하지 않고 그냥 함수 종료
    else if (*phead == (*phead)->link) {//노드가 하나인 경우
        removed = *phead;
        *phead = NULL;
    }
    else {//노드가 둘 이상인 경우
        removed = (*phead)->link; //시작노드가 삭제될 도드.
        (*phead)->link = removed->link;     
    }//(*phead)->link가 시작노드임을 가리키는데 그걸 removed인 시작노드의 다음노드인removed->link로 해준다 
    free(removed);              //삭제될 노드는 free함수로 메모리 해제를 반드시 해줘야한다.
}
void remove_middle(ListNode **phead, ListNode *pre) //pre는 삭제할 노드의 선행자 노드
{
    ListNode* removed;
    if (*phead == NULL) return;      //공백리스트인 경우 삭제하지 않고 그냥 함수 종료
    else if (*phead == pre->link) {      //선행자노드의 다음노드가 phead면 삭제할 노드가 마지막 노드인 경우 
        removed = *phead;
        pre->link = (*phead)->link;
        *phead = pre;
    }
    else {//노드가 시작노드이거나 중간노드인 경우        
        removed = pre->link;
        pre->link = removed->link; //첫번째를 지우는거이기 때문에 phead는 변경될 필요가 없다.
    }
    free(removed);               //삭제될 노드는 free함수로 메모리 해제를 반드시 해줘야한다.
}
void remove_last(ListNode **phead)
{
    ListNode* removed, *pre;    //pre는 삭제할 노드의 선행자 노드
    if (*phead == NULL) return;      //공백리스트인 경우 삭제하지 않고 그냥 함수 종료
    else if (*phead == (*phead)->link) {//노드가 하나인 경우
        removed = *phead;
        *phead = NULL;
    }
    else {//노드가 둘 이상인 경우
        pre = (*phead)->link;
        while (*phead != pre->link)
            pre = pre->link;       //phead의 선행자 노드 위치 탐색(선행자의 링크필드가 선행자노드의 주소가 되어야 한다는 점)
        removed = *phead;       //phead가 삭제할 노드
        pre->link = removed->link; //시작노드의 주소를 저장.
        *phead = pre;           //선행자 노드가 마지막 노드로 변경하준다.
 
    }
    free(removed);               //삭제될 노드는 free함수로 메모리 해제를 반드시 해줘야한다.
}
// 역순
ListNode *reverse(ListNode *phead)
{
	ListNode *p, *q, *r;
	p = phead->link;    // 시작노드 주소 저장
	q = phead;         // q는 역순으로 만들 노드
	while (p != phead) {
		r = q;         // r은 역순으로 된 리스트, r은 q , q는 p를 차례로 따라감
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 변경
	}
	phead = phead->link;
	p->link = q;
	return phead;
}
// 리스트의 항목 출력
void display(ListNode *head)
{
	ListNode *p;  // p리스트 선언
	int head_num; // 헤드 변수
	int tail_num; // 테일 변수
	if( head == NULL ) return; // 헤드가 NULL 경우 리턴

	p = head; // p가 head를 가리키게 한다
	head_num = p->link->data; // 헤드에 p의 다음링크 데이터를 대입한다
	printf("< ");
	do {
		if( p->link == head )         // p다음링크가 헤드일 경우
			tail_num = p->link->data; // 테일에 p의 다음링크 데이터를 대입
		p = p->link; // p가 다음노드로 넘어간다
		printf("%d ",p->data); // p데이터 출력
	}while( p != head); // p가 헤드에 도달할때까지 반복문
	printf(">\n");

	printf("Head : %d\n",head_num);
	printf("Tail : %d\n",tail_num);
	printf("Tail Next : %d\n",head_num);
	printf("\n");
}
// display리버스
void display_reverse(ListNode *head)
{
	ListNode *p;
	int head_num;
	int tail_num;
	if( head == NULL ) return;

	p = head;
	head_num = p->data;
	printf("< ");
	do {
		if( p->link == head )
			tail_num = p->data;
		printf("%d ",p->data);
		p = p->link;
	}while( p != head);
	printf(">\n");

	printf("Head : %d\n",head_num);
	printf("Tail : %d\n",tail_num);
	printf("Tail Next : %d\n",head_num);
	printf("\n");
}
// 앞 항과 끝 항 노드 제거
void delete_node(ListNode *head,int count)
{
	ListNode *p = head; // p는 헤드를 가리킨다
	ListNode *q = NULL; // q는 NULL을 가리킨다
	int i=0; // 증가값변수

	if( p->data == 172 ){ // 첫번째 노드가 172일 경우
		remove_first(&p); // 첫번째 노드 삭제
		p=p->link; // p는 다음링크를 가리킨다
	}
	else{  // 아닐경우
		p=p->link;} // p는 다음링크를 가리킨다

	q = head; // q는 헤더를 가리킨다
	while(i<count-2){ // count-2값(첫항,끝항을 제외)크기의 반복문
		 // 중간 노드 중 172경우 삭제
		if( p->data == 172 )
			remove_middle(&p,q);
		p=p->link; // p는 다음노드를 가리킨다
		q=q->link; // q는 다음노드를 가리킨다
		i++; // i값 증가
	}
}
// 탐색
ListNode* search(ListNode *head, element x)
{
    ListNode *p;             
    p = head->link;          //첫번째 원형리스트부터 시작 물론 p= head 로 하고 마지막 노드부터 시작해도 상관없다.
    do {
        if (p->data == x)  // 만약 같다면 
			return p; //탐색 성공
 
        p = p->link;      //if문 충족하지 않으면 p를 이동시켜줌
    } while (p != head->link);
    return NULL; //탐색 실패  //if문에 충족하지 않아서 밖으로 빠져나오게 된다면, 그냥 null값 return해서 밖으로 나옴.
 
}
int main()
{
	ListNode *list1=NULL; // list1 선언
	int num;              // 파일 데이터값 변수
	int count=0;          // 파일 데이터 개수

	FILE *fp = fopen("data2.txt","r"); // "data2.txt"를 읽기형식으로 오픈
	if(fp==NULL){  // 파일 에러시
		printf("파일이 열리지 않았습니다\n");
		return 1;
	}
	while(!feof(fp)) // 파일포인터가 끝에 도달할때가지 반복
	{
		fscanf(fp,"%d",&num); // num값에 파일데이터 대입
		insert_last(&list1, create_node(num,NULL) ); // list1에 num값과 NULL을 가리키는 노드를 생성해 삽입
		count++; // 카운팅
	}
	display(list1); // list1 출력

	// 딜리트172
	printf("< Delete 172 >\n");
	delete_node(list1,count); // 첫번째 노드값과 중간노드값이 172인 경우
	if( search(list1,172) ) // 마지막 노드값이 172일 경우
	remove_last(&list1); // 끝 노드값 삭제
	// 리버스
	printf("< Reverse >\n\n");
	reverse(list1); // list1 리버스
	display_reverse(list1); // list1 출력

	fclose(fp); // 파일을 닫아준다
	return 0;   
}