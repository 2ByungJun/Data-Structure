///////////////////////////////////////////////////////////////////////
//
//  작 성 자    : 이병준
//  작 성 일    : 2018년 5월 14일
// 프로그램명   : 이중 연결 리스트
//   설  명     : Data.txt파일에 저장된 정보를 원형 연결 리스트에 저장하고 
//                입력한 숫자를 데이터로 가지고 있는 노드를 삭제하는 함수
//                를 구현하여 출력하고 Reverse함수를 쓰지 않고 포인터로
//                이용하여 역순으로 출력하시오.
//  수강과목    : 자료구조1 실습 ( 홍 민 교수님 ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int el; // el 자료형타입 생성
typedef struct Dnode{ // Dnode 구조체 생성
	el data;          // data값
	struct Dnode *llink; // 왼쪽 링크
	struct Dnode *rlink; // 오른쪽 링크
}Dnode;

static el count = 0; // count 자료형 선언
// 에러함수
void error( char* mes)
{
	fprintf( stderr, "%s\n", mes);
	exit(1);
}
// 링크 초기화 함수
void init( Dnode *phead)
{
	phead->llink = phead; // phead를 가리키면서 링크초기화
	phead->rlink = phead; // phead를 가리키면서 링크초기화
}
// 노드 생성
Dnode *create( el data )
{
	Dnode *new_node; // Dnode타입 new_node 생성
	new_node = (Dnode *)malloc( sizeof(Dnode) ); // new_node 동적할당
	new_node->data = data;  // data초기화
	new_node->llink = NULL; // L링크 NULL 가리킴
	new_node->rlink = NULL; // R링크 NULL 가리킴
	return new_node; // new_node리턴
}
// 노드 위치파악
// pnode = 리스트
// num =  위치
Dnode *node_which( Dnode *pnode, int num)
{
	int i;
	// 맨 마지막 위치 삽입할 경우
	if( num == ( count+1) ) 
	{
		pnode = pnode->llink;
	}
	// (count[이중 연결리스트의 삽입되어 있는 노드의개수]+1)/2 보다 같거나 작은경우
	else if( num <= (count+1)/2 ) 
	{
		for(i=0; i<num-1; i++ )
			pnode = pnode->rlink;
	}
	// 그외에 경우
	else
	{
		for( i=0; i<2+(count-num); i++)
			pnode = pnode->llink;
	}
	return pnode;
}
// 삽입
// p = 리스트
// new_node = 연결할 새로운 노드
// num = 연결할 위치
void dinsert_node( Dnode *p, Dnode *new_node, int num )
{
	if( num > count+1 ) // 총 노드보다 높은 수를 입력할 경우
		error("총 노드의 개수보다 높은 수를 입력하셨습니다.\n"); 
	if( num == 1 ) // 첫번째 위치에 삽입할 경우
	{ 
		new_node->llink = p;         // new_node가 p값을 가리킴
		new_node->rlink = p->rlink;  // new_node가 p의 rlink를 가리킴
		p->rlink->llink = new_node;  // p다음 노드값에 new_node대입
		p->rlink = new_node;         // p rlink가 new_node를 가리킴
	} 
	else // 그 외에 경우 
	{	Dnode *pnode = node_which( p, num); // node_which로 앞노드까지 이동

	new_node->llink = pnode;        // new_node가 pnode값을 가리킴
	new_node->rlink = pnode->rlink; // new_node가 pnode의 rlink를 가리킴
	pnode->rlink->llink = new_node; // pnode다음 노드값에 new_node대입
	pnode->rlink = new_node;        // pnode rlink가 new_node를 가리킴
	} 
	count++; // 카운트 증가
}
// 제거
// head = 리스트
// data = 삭제할 값
void dremove_node( Dnode *head, int data ) 
{ 
	Dnode *p,*temp; // p,temp 리스트 선언

	if(head->rlink==NULL) return; // NULL경우 리턴
	else{ 
		p=head; // p가 head를 가리킴

		if(head->rlink->rlink==head->rlink) {  // 데이터 1개 밖에 없을 경우

			p=p->rlink; // p가 다음 노드로 이동 
			head->rlink=NULL; // head가 NULL을 가리킴 
			free(p);    // p삭제
			return;     // 리턴
		}
		if(head->rlink->data==data){  // 첫 데이터 삭제
			do{
				p=p->rlink;
			}while(p->rlink != head->rlink); // p가 head를 가리킬때까지

			temp=head->rlink;        // hemp가 head가 가리키는 링크를 가리킴
			head->rlink=temp->rlink; // head 링크가 temp가 가리킨 링크를 가리킴
			temp->rlink->llink=p;    // temp의 다음 노드에 p값을 대입
			p->rlink=temp->rlink;    // p가 가리키는 링크를 temp가 가리키는 링크로 바꿈
			free(temp);              // twmp삭제
			return;                  // 리턴
		}
		do{ p=p->rlink;    // 그 외에 데이터 삭제
		if(p->data==data){ // 리스트의 data와 삭제할 값이 같을 경우
			p->llink->rlink=p->rlink; // p가 다음노드로 교차이동
			p->rlink->llink=p->llink; // p가 다음노드로 교차이동
			return; // 리턴
		}
		}while(p->rlink!=head->rlink);
	}
}
// 출력
void display(Dnode *phead)
{
	Dnode *p;
	printf("< ");
	// phead리스트를 rlink기준으로 한번 읽어주는 반복문 (방향"<-")
	for( p = phead->llink; p != phead; p=p->llink )
		printf("%d ",p->data);
	printf(">\n");
}
// 반대로 출력
void rdisplay(Dnode *phead) {
	Dnode *p;
	printf("< ");
	// phead리스트를 llink기준으로 한번 읽어주는 반복문 (방향"->")
	for( p = phead->rlink; p != phead; p=p->rlink )
		printf("%d ",p->data);
	printf(">\n");
}
int main()
{
	Dnode head_node;   // 리스트 선언
	int num;           // 파일 데이터값을 저장할 변수
	int delete_num;    // 삭제할 값
	int file_count=0;  // 파일카운팅 변수
	int i;             // 반복변수

	FILE *fp = fopen("data3.txt","r"); // data3.txt파일을 읽기형식으로 오픈
	if(fp==NULL) // 파일 에러시
	{
		printf("파일이 열리지 않았습니다.\n");
		return 1;
	}
	init( &head_node ); // 리스트 초기화

	while(!feof(fp)) // 파일 반복문
	{
		fscanf(fp,"%d",&num); // num값에 파일데이터값을 대입
		dinsert_node( &head_node , create(num), 1); // num값으로 노드생성과 리스트의 '1'위치에 삽입
		file_count++; // 파일 데이터수 증가
	}
	display( &head_node); // 리스트 출력

	// '0' 일시 종료되는 무한루프
	while(1){ 
		printf("지울 값을 입력하세요(0:종료) :");
		scanf("%d",&delete_num);

		if ( delete_num == 0 )
			break;
		else
		{
			i=0; // i=0 초기화
			while( i < file_count){ // file_count만큼 반복
				dremove_node(&head_node,delete_num); // delete_num수를 삭제
				i++;
			}
			file_count = i; // file_count를 i로 초기화
		}
		display( &head_node);  // 리스트 출력
		rdisplay( &head_node); // 리스트 역순 출력
		printf("\n");
	}

	fclose(fp); // 파일을 닫습니다
	return 0;
}