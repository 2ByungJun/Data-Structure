///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 9�� 13��
// ���α׷���   : ���Ͽ��� �ڷ� �о����
//   ��  ��     : ���Ͽ��� �̸�,�����,���� ������ ����� �����Ǿ�����
//                ���� ���·� ����Ǿ� �ִ�. �� ������ �̿��Ͽ� ���ǿ�
//                �°� ���α׷��� �ۼ��϶�.
//  ��������    : �ڷᱸ��2 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student ����ü
typedef struct Student{
	char name[10]; // �̸�
	int math;      // ����
	int eng;       // ����
	int kor;	   // ����
}Student;

// ����Ʈ ����
typedef struct ListNode{
	Student data;
	struct ListNode *link;
} ListNode;

// ���� ���
void error(char *message)
{
	fprintf(stderr,"%s\n",message);
	exit(1);
}

// ���� �Լ�
// phead: ����Ʈ�� ��� ����Ʈ�� ������
// p : ������
// new_node : ���Ե� ���
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if(*phead == NULL){
		new_node->link =NULL;
		*phead = new_node;
	}
	else if(p == NULL){
		new_node->link = *phead;
		*phead = new_node;
	}
	else{
		new_node->link = p->link;
		p->link = new_node;
	}
}

// ���� ��� ����
ListNode *create_node(Student data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if(new_node == NULL)
		error("�޸� �Ҵ� ����");
	new_node->data = data;
	new_node->link = link;
	return(new_node);
}

// Ž�� �Լ�
// head : ����Ʈ
// file_name : ���Ͽ����� �̸���
ListNode *search(ListNode *head,char file_name[] )
{
	ListNode *p=head;
	while(p !=NULL)
	{
		if(strcmp(p->data.name,file_name) == 0) // �������̸��� ���ϵ����� �̸��� ���� ���
			return p;
		p= p->link; // ������带 ����Ŵ
	}
	return p;
}

// ��� �Լ�
// head : �޾� �� ����Ʈ
void display(ListNode *head)
{
	ListNode *p=head;
	while(p != NULL)
	{
		printf("< %s �л��� ���� >\n",p->data.name); // �л� �̸� ���
		printf("- ���� : %5d��\n- ���� : %5d��\n- ���� : %5d��\n- ��� : %.2f��\n\n", 
			                              p->data.kor,p->data.math,p->data.eng,(double)(p->data.kor+p->data.math+p->data.eng)/3);
		                                  // ����,����,����,��� ���
		p=p->link; // ���� ��带 ����Ŵ
	}
	printf("\n");
}

int main()
{

	ListNode *list=NULL;  // ����Ʈ ����
	ListNode *p;          // �̸����� Ž������ ������ 
	Student tmp;          // ����ü tmp���� ( �̸�,����,���� )
	char file_subject[10];
	FILE *fp =NULL;

	fp = fopen("data2.txt","r"); // data2.txt������ �б��������� ����
	if(fp==NULL) // ���� �б� ������
	{
		error("���� �б� ����\n");
		exit(1);
	}
	// ���� �ʱ�ȭ( �� ����ĭ�� 0���� �־��ֱ� ���� )
	tmp.eng = 0;
	tmp.kor = 0;
	tmp.math = 0;

	while(!feof(fp))
	{
		fscanf(fp,"%s",&tmp.name); // ���� �̸����� ������
		if(search(list,tmp.name) != NULL) // ����Ʈ���� �̸��� �ִ��� ��ü Ž���Ͽ� ���� ���
		{
			p = search(list,tmp.name);  // p�� tmp.name�̸����� ���� ��带 Ž���Ͽ� ����
			fscanf(fp,"%s",&file_subject); // ���� �����̸��� ������

			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ���п� ���� ������Ʈ
				fscanf(fp,"%d",&p->data.math);
			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ��� ���� ������Ʈ
				fscanf(fp,"%d",&p->data.kor);
			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ��� ���� ������Ʈ
				fscanf(fp,"%d",&p->data.eng);
		}			
		else // �̸��� ���� ���
		{
			fscanf(fp,"%s",&file_subject); // ���Ͽ��� ������ ����

			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ���п� ���� ������Ʈ
				fscanf(fp,"%d",&tmp.math);
			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ��� ���� ������Ʈ
				fscanf(fp,"%d",&tmp.kor);
			if(strcmp(file_subject,"����") == 0) // �����ϰ�� ��� ���� ������Ʈ
				fscanf(fp,"%d",&tmp.eng);

			insert_node(&list,NULL,create_node(tmp,NULL)); // tmp����
		}
	}
	display(list); // list���

	fclose(fp); // ������ �ݾ��ش�
	return 0;	
}
