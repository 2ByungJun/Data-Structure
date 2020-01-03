#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
   element data;
   struct ListNode *link;
   struct ListNode *tail;
} ListNode;

// 오류 출력
void error(char *message)
{
   fprintf(stderr,"%s\n",message);
   exit(1);
}

static int index=0;

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


ListNode *which(ListNode *node, int num)
{
   int i;
   for(i=1; i<num; i++)
   {
      node = node->link;
   }
   return node;
}


// 삽입함수


void insert_node( ListNode **phead, ListNode *new_node, int num )   //데이터 삽입함수, num번째의 값을 삽입함 
{ 
   index++;

   if( num > index ) 
      error("총 노드의 개수보다 높은 수를 입력하셨습니다."); 
   if( *phead == NULL ) 
   {
      *phead = new_node;
      new_node->link = new_node; 
   }
   else if( num < index )
   {
      ListNode *p = which( *phead, num); 
      new_node->link = p->link;
      p->link = new_node; 
   } 
   else if( num == index ) 
   { 
      new_node->link = (*phead)->link;
      (*phead)->link = new_node;
      *phead = new_node; 
   }   
}



// 삭제함수
void remove_node(ListNode **phead, ListNode *remove,int num )   //삭제함수, num번째 수를 삭제함 
{
   if( *phead == NULL ) 
      error("삭제할 노드가 없습니다.");
   else if( num <= index )
   { 
      ListNode *p = which( *phead, num );
      remove = which( *phead , num + 1 );
      p->link = remove->link; 
      if( num == index ) 
         *phead = p; 
      free( remove ); 
   } 
   else 
      error("총 노드의 개수보다 높은 수를 입력하셨습니다.");
   index--;
}


// 역순
ListNode *reverse(ListNode *phead)
{
   ListNode *p, *q, *r=NULL;
   int i=0;
   p = phead->link;    // 시작노드 주소 저장
   q = phead;         // q는 역순으로 만들 노드

   while (p != phead)
   {
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
   ListNode *p;
   int head_num;
   int tail_num;
   int tail_next;
   if( head == NULL )
      return;
   p = head;
   head_num = p->link->data;
   printf("< ");
   do {
      if( p->link == head ){
         tail_num = p->link->data;
         tail_next = p->link->link->data;
      }
      p = p->link;
      printf("%d ",p->data);
   }while( p != head);
   printf(">\n");

   printf("Head : %d\n",head_num);
   printf("Tail : %d\n",tail_num);
   printf("Tail Next : %d\n",tail_next);
   printf("\n");
}
int main()
{

   int i=1;
   ListNode *list1=NULL,*list2=NULL;

   int num;
   int count=0;
   FILE *fp = fopen("data2.txt","r");
   if(fp==NULL){
      printf("파일이 열리지 않았습니다\n");
      exit(1);
   }
   
   while(!feof(fp))
   {      
      fscanf(fp,"%d",&num);
      insert_node(&list1, create_node(num,NULL),i);
      count++;
      i++;
   }
   

   display(list1);
   // 딜리트
   printf("< Delete 172 >\n");
   for(i=1; i<=index; i++)
   {
      if(list1->link->data==172)
      {
         remove_node(&list1,list1,1);
      }
      list1=list1->link;
   }
   
   // 리버스
   printf("< Reverse >\n\n");

   
   reverse(list1);

   display(list1);

   fclose(fp);
   return 0;
}