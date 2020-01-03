///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 22��
// ���α׷���   : ���Ḯ��Ʈ
//   ��  ��     : Data.txt���� �й�,�̸�,����,����,���� ������ ������
//                ��ũ�� ����Ʈ�� �����ϰ� ����,����,����,���� �ְ�������
//                ���� �л��� �Ʒ��� ���� ����϶�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>

// People����ü ����
typedef struct {
	char name[10];	//�̸�
	int number;		//�й�
	int korean;		//����
	int eng;		//����
	int math;		//����
}People;

// ���Ḯ��Ʈ ����
typedef struct ListNode{
	People data;
	struct ListNode *link;
}ListNode;

// �����Լ�
void error (char *message)
{
	fprintf(stderr,"&s\n",message);
	exit(1);
}
// �����Լ�
// phead: ����Ʈ�� ��� ����Ʈ�� ������
// p : ������
// new_node : ���Ե� ���
void insert_node(ListNode **phead, ListNode *p,ListNode *new_node)
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
// �����Լ�
ListNode *reverse(ListNode *head)
{
	ListNode *p, *q, *r; // ��ȸ ������
	p = head;
	q = NULL;
	while(p!=NULL)
	{
		r=q;
		q=p;
		p=p->link;
		q->link=r;
	}
	return q;
}
// �������� ��带 ����
ListNode *create_node(People data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node==NULL) error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}
// �л����� ���
void display(ListNode *head)
{
	int total=0;   // ����
	double ever=0; // ���
	ListNode *p=head; // p ���� �� head�� �ʱ�ȭ
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  �й�  |  �̸�  |����|����|����|����| ��� |\n");
	printf("|========|========|====|====|====|====|======|\n");
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math; // ������ ����
		ever=total/3.0; // ��հ� ����
		printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;    // ���� ���� �̵�
	}
	printf("|========|========|====|====|====|====|======|\n\n");

}
// �ְ����� ���
void display_MAX(ListNode *head)
{
	int total=0;   // ����
	double ever=0; // ���
	int max=0;     // �ְ��� ã�� ������ ����
	ListNode *p=head;// p ���� �� head�� �ʱ�ȭ

	// ���� �ְ�����   ( ���� �Լ��� �� �ߺ��� ���� �ּ�ó���� �����ϵ��� �ϰڽ��ϴ�.[����������] )
	// total,ever,max ���ϱ�
	while(p!=NULL)
	{	
		total=p->data.korean+p->data.eng+p->data.math; // ������ ����
		if(max<=total)  // total�� max���� ũ�ų� ���� ��
			max= total; // max�� ����
		p = p->link;
	}
	p=head; // head�ʱ�ȭ
	printf("< ���� �ְ����� >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  �й�  |  �̸�  |����|����|����|����| ��� |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// ���
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==total)  // max�� �ְ������� ���� �� ���
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// ���� �ְ�����
	p=head;// head�ʱ�ȭ
	max=0; // max�ʱ�ȭ
	while(p!=NULL)
	{	
		if(max<=p->data.korean) // �������� �ִ밪�� max�� ����
			max= p->data.korean;
		p = p->link;
	}
	p=head; // head�ʱ�ȭ
	printf(" < ���� �ְ����� >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  �й�  |  �̸�  |����|����|����|����| ��� |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// ���
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==p->data.korean)  // max�� ���������� ���� �� ���
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// ���� �ְ�����
	p=head;
	max=0;
	while(p!=NULL)
	{	
		if(max<=p->data.math) // �������� �ִ밪�� max�� ����
			max= p->data.math;
		p = p->link;
	}
	p=head;
	printf(" < ���� �ְ����� >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  �й�  |  �̸�  |����|����|����|����| ��� |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// ���
	while(p!=NULL)
	{
		total=p->data.korean+p->data.eng+p->data.math;
		ever=total/3.0;
		if(max==p->data.math)  // max�� ���������� ���� �� ���
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");

	// ���� �ְ�����
	p=head;
	max=0;
	while(p!=NULL)
	{	
		if(max<=p->data.eng) // �������� �ִ밪�� max�� ����
			max= p->data.eng;
		p = p->link;
	}
	p=head;
	printf(" < ���� �ְ����� >\n");
	printf("|========|========|====|====|====|====|======|\n");
	printf("|  �й�  |  �̸�  |����|����|����|����| ��� |\n");
	printf("|========|========|====|====|====|====|======|\n");
	// ���
	while(p!=NULL)
	{
		if(max==p->data.eng)// max�� ���������� ���� �� ���
		{	
			total=p->data.korean+p->data.eng+p->data.math;
			ever=total/3.0;
			printf("|%d| %s | %d | %d | %d |%d |%.2lf |\n",p->data.number,p->data.name,p->data.korean,p->data.eng,p->data.math,total,ever);
		}
		p = p->link;
	}
	printf("|========|========|====|====|====|====|======|\n\n");
}

int main()
{
	ListNode *list1=NULL; // ����Ʈ ����
	People temp;    // temp ����ü ����
	FILE *fp = fopen("data1.txt","r"); // ����data1.txt �б��������� ����
	if(fp==NULL) // ���Ͽ����� ���
	{
		printf("���� ���� ����\n");
		exit(1);
	}

	// list1�� data����
	while(!feof(fp))
	{
		fscanf(fp,"%d %s %d %d %d",&temp.number,temp.name,&temp.korean,&temp.eng,&temp.math); // data����ü�� ����
		insert_node(&list1,NULL,create_node(temp,NULL)); // data����ü list1�� ����
	}
	list1=reverse(list1); // list1 ����

	display(list1);     // �л� ���� ���
	display_MAX(list1); // �ְ����� ���

	fclose(fp); // ������ �ݾ��ش�.
	return 0;
}