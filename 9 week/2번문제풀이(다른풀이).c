#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
   element data;
   struct ListNode *link;
   struct ListNode *tail;
} ListNode;

// ���� ���
void error(char *message)
{
   fprintf(stderr,"%s\n",message);
   exit(1);
}

static int index=0;

// �������� ��带 ����
ListNode *create_node(element data,ListNode *link) 
{
   ListNode *new_node;
   new_node = (ListNode *)malloc(sizeof(ListNode));
   if( new_node == NULL ) error("�޸� �Ҵ� ����");
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


// �����Լ�


void insert_node( ListNode **phead, ListNode *new_node, int num )   //������ �����Լ�, num��°�� ���� ������ 
{ 
   index++;

   if( num > index ) 
      error("�� ����� �������� ���� ���� �Է��ϼ̽��ϴ�."); 
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



// �����Լ�
void remove_node(ListNode **phead, ListNode *remove,int num )   //�����Լ�, num��° ���� ������ 
{
   if( *phead == NULL ) 
      error("������ ��尡 �����ϴ�.");
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
      error("�� ����� �������� ���� ���� �Է��ϼ̽��ϴ�.");
   index--;
}


// ����
ListNode *reverse(ListNode *phead)
{
   ListNode *p, *q, *r=NULL;
   int i=0;
   p = phead->link;    // ���۳�� �ּ� ����
   q = phead;         // q�� �������� ���� ���

   while (p != phead)
   {
      r = q;         // r�� �������� �� ����Ʈ, r�� q , q�� p�� ���ʷ� ����
      q = p;
      p = p->link;
      q->link = r; // q�� ��ũ ������ ����
   }
   phead = phead->link;
   p->link = q;

   return phead;
}





// ����Ʈ�� �׸� ���
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
      printf("������ ������ �ʾҽ��ϴ�\n");
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
   // ����Ʈ
   printf("< Delete 172 >\n");
   for(i=1; i<=index; i++)
   {
      if(list1->link->data==172)
      {
         remove_node(&list1,list1,1);
      }
      list1=list1->link;
   }
   
   // ������
   printf("< Reverse >\n\n");

   
   reverse(list1);

   display(list1);

   fclose(fp);
   return 0;
}