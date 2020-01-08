///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 11�� 2��
// ���α׷���   : ���� ���� ���α׷�(�ܼ� ���Ḯ��Ʈ)
//   ��  ��     : data1.txt�� �л��� ������ ����Ǿ� �ִ�. �̸� �о��
//                ����� ���ϰ� ���������� ������������ �����Ͽ� ���
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// element ����ü ����
typedef struct {
	int num;   // �й�
	int kor;   // ����
	int eng;   // ����
	int math;  // ����
	int total; // ����
}element;

// ����Ʈ ����
typedef struct ListNode{
	element data;
	struct ListNode *link;
}ListNode;

// ���� ���
void error(char *message)
{
	fprintf(stderr,"s\n",message);
	exit(1);
}

// phead: ����Ʈ�� ��� ����Ʈ�� ������
// p : ������
// new_node : ���Ե� ���
void insert_node(ListNode **phead,ListNode *p, ListNode *new_node)
{
	if( *phead == NULL ){  // ���� ����Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if( p == NULL ) { // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {  // p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}

// �������� ��带 ����
// data : data�� ����
// link : link�� ����
ListNode *create(element data,ListNode *link) 
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if( new_node == NULL ) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// ����
// head : ������ ����Ʈ
ListNode *reverse(ListNode *head)
{
	// ��ȸ ������
	ListNode *p,*q, *r;
	p = head;
	q = NULL;
	while ( p != NULL){
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

// ���� ����
// head : ������ ����Ʈ
ListNode *insertion_sort(ListNode *head)
{
	ListNode *p = head; // p�� ��带 ����Ŵ
	ListNode *temp;     // temp�� �ӽð���
	while(p->link != NULL ) { // p�� ������ũ�� NULL���
		if(p->data.total < p->link->data.total){ // total�� (�����尡 ������庸�� ������� �߻�)
			temp = p->link; // temp�� p�� ������带 ����Ŵ | ��(p) ��(<-temp) �� �� |
			p->link = p->link->link; // p�� �������� �� ���� ��带 ����Ŵ | ��(p) ��(temp)->��(p) �� |
			temp->link = head; // temp���� ��尪�� ����
			head = p = temp; // head�� �������� ����Ŵ
			continue;
		}
		p = p->link; // ������ũ��
	}
	return head;
}

// ���
// head : ����� ����Ʈ
void display(ListNode *head)
{
	ListNode *p = head;
	printf("|========================================|\n");
	printf("|  �й�  | ����| ����| ����| �� ��| �� ��|\n");
	while( p != NULL ){
		printf("|%d| %3d | %3d | %3d | %3d  | %3.2lf|\n",p->data.num,p->data.kor,p->data.eng,p->data.math
			                                            ,p->data.total , (float)p->data.total/3);
		p = p->link;
	}
	printf("|========================================|\n");
}

int main()
{
	ListNode *list=NULL; // ����Ʈ ����
	element e;           // ����ü ����

	// data1.txt �б�
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL){
		printf("���� ����\n");
		exit(1);
	}
	
	// ����Ʈ�� e����ü ����(e:���ϵ����� ���� ����)
	while(!feof(fp))
	{
		fscanf(fp,"%d %d %d %d",&e.num,&e.kor,&e.eng,&e.math); // �й�,����,����,����
		e.total = e.kor+e.math+e.eng; // ����
		insert_node(&list,NULL,create(e,NULL)); // �����Լ�
	}

	// ���� ��
	printf("<���� ��>\n");
	list = reverse(list); // ���� ����
	display(list); // ���

	// ���� ��
	printf("\n<���� ��>\n");
	list = insertion_sort(list); // ���� ����
	display(list); // ���

	fclose(fp); // ������ �ݾ��ݴϴ�
	return 0;   // ����
}