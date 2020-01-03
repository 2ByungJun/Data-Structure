///////////////////////////////////////////////////////////////////////
//
//  �� �� ��    : �̺���
//  �� �� ��    : 2018�� 5�� 14��
// ���α׷���   : ���� ���� ����Ʈ
//   ��  ��     : Data.txt���Ͽ� ����� ������ ���� ���� ����Ʈ�� �����ϰ� 
//                �Է��� ���ڸ� �����ͷ� ������ �ִ� ��带 �����ϴ� �Լ�
//                �� �����Ͽ� ����ϰ� Reverse�Լ��� ���� �ʰ� �����ͷ�
//                �̿��Ͽ� �������� ����Ͻÿ�.
//  ��������    : �ڷᱸ��1 �ǽ� ( ȫ �� ������ ) 
//
////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

typedef int el; // el �ڷ���Ÿ�� ����
typedef struct Dnode{ // Dnode ����ü ����
	el data;          // data��
	struct Dnode *llink; // ���� ��ũ
	struct Dnode *rlink; // ������ ��ũ
}Dnode;

static el count = 0; // count �ڷ��� ����
// �����Լ�
void error( char* mes)
{
	fprintf( stderr, "%s\n", mes);
	exit(1);
}
// ��ũ �ʱ�ȭ �Լ�
void init( Dnode *phead)
{
	phead->llink = phead; // phead�� ����Ű�鼭 ��ũ�ʱ�ȭ
	phead->rlink = phead; // phead�� ����Ű�鼭 ��ũ�ʱ�ȭ
}
// ��� ����
Dnode *create( el data )
{
	Dnode *new_node; // DnodeŸ�� new_node ����
	new_node = (Dnode *)malloc( sizeof(Dnode) ); // new_node �����Ҵ�
	new_node->data = data;  // data�ʱ�ȭ
	new_node->llink = NULL; // L��ũ NULL ����Ŵ
	new_node->rlink = NULL; // R��ũ NULL ����Ŵ
	return new_node; // new_node����
}
// ��� ��ġ�ľ�
// pnode = ����Ʈ
// num =  ��ġ
Dnode *node_which( Dnode *pnode, int num)
{
	int i;
	// �� ������ ��ġ ������ ���
	if( num == ( count+1) ) 
	{
		pnode = pnode->llink;
	}
	// (count[���� ���Ḯ��Ʈ�� ���ԵǾ� �ִ� ����ǰ���]+1)/2 ���� ���ų� �������
	else if( num <= (count+1)/2 ) 
	{
		for(i=0; i<num-1; i++ )
			pnode = pnode->rlink;
	}
	// �׿ܿ� ���
	else
	{
		for( i=0; i<2+(count-num); i++)
			pnode = pnode->llink;
	}
	return pnode;
}
// ����
// p = ����Ʈ
// new_node = ������ ���ο� ���
// num = ������ ��ġ
void dinsert_node( Dnode *p, Dnode *new_node, int num )
{
	if( num > count+1 ) // �� ��庸�� ���� ���� �Է��� ���
		error("�� ����� �������� ���� ���� �Է��ϼ̽��ϴ�.\n"); 
	if( num == 1 ) // ù��° ��ġ�� ������ ���
	{ 
		new_node->llink = p;         // new_node�� p���� ����Ŵ
		new_node->rlink = p->rlink;  // new_node�� p�� rlink�� ����Ŵ
		p->rlink->llink = new_node;  // p���� ��尪�� new_node����
		p->rlink = new_node;         // p rlink�� new_node�� ����Ŵ
	} 
	else // �� �ܿ� ��� 
	{	Dnode *pnode = node_which( p, num); // node_which�� �ճ����� �̵�

	new_node->llink = pnode;        // new_node�� pnode���� ����Ŵ
	new_node->rlink = pnode->rlink; // new_node�� pnode�� rlink�� ����Ŵ
	pnode->rlink->llink = new_node; // pnode���� ��尪�� new_node����
	pnode->rlink = new_node;        // pnode rlink�� new_node�� ����Ŵ
	} 
	count++; // ī��Ʈ ����
}
// ����
// head = ����Ʈ
// data = ������ ��
void dremove_node( Dnode *head, int data ) 
{ 
	Dnode *p,*temp; // p,temp ����Ʈ ����

	if(head->rlink==NULL) return; // NULL��� ����
	else{ 
		p=head; // p�� head�� ����Ŵ

		if(head->rlink->rlink==head->rlink) {  // ������ 1�� �ۿ� ���� ���

			p=p->rlink; // p�� ���� ���� �̵� 
			head->rlink=NULL; // head�� NULL�� ����Ŵ 
			free(p);    // p����
			return;     // ����
		}
		if(head->rlink->data==data){  // ù ������ ����
			do{
				p=p->rlink;
			}while(p->rlink != head->rlink); // p�� head�� ����ų������

			temp=head->rlink;        // hemp�� head�� ����Ű�� ��ũ�� ����Ŵ
			head->rlink=temp->rlink; // head ��ũ�� temp�� ����Ų ��ũ�� ����Ŵ
			temp->rlink->llink=p;    // temp�� ���� ��忡 p���� ����
			p->rlink=temp->rlink;    // p�� ����Ű�� ��ũ�� temp�� ����Ű�� ��ũ�� �ٲ�
			free(temp);              // twmp����
			return;                  // ����
		}
		do{ p=p->rlink;    // �� �ܿ� ������ ����
		if(p->data==data){ // ����Ʈ�� data�� ������ ���� ���� ���
			p->llink->rlink=p->rlink; // p�� �������� �����̵�
			p->rlink->llink=p->llink; // p�� �������� �����̵�
			return; // ����
		}
		}while(p->rlink!=head->rlink);
	}
}
// ���
void display(Dnode *phead)
{
	Dnode *p;
	printf("< ");
	// phead����Ʈ�� rlink�������� �ѹ� �о��ִ� �ݺ��� (����"<-")
	for( p = phead->llink; p != phead; p=p->llink )
		printf("%d ",p->data);
	printf(">\n");
}
// �ݴ�� ���
void rdisplay(Dnode *phead) {
	Dnode *p;
	printf("< ");
	// phead����Ʈ�� llink�������� �ѹ� �о��ִ� �ݺ��� (����"->")
	for( p = phead->rlink; p != phead; p=p->rlink )
		printf("%d ",p->data);
	printf(">\n");
}
int main()
{
	Dnode head_node;   // ����Ʈ ����
	int num;           // ���� �����Ͱ��� ������ ����
	int delete_num;    // ������ ��
	int file_count=0;  // ����ī���� ����
	int i;             // �ݺ�����

	FILE *fp = fopen("data3.txt","r"); // data3.txt������ �б��������� ����
	if(fp==NULL) // ���� ������
	{
		printf("������ ������ �ʾҽ��ϴ�.\n");
		return 1;
	}
	init( &head_node ); // ����Ʈ �ʱ�ȭ

	while(!feof(fp)) // ���� �ݺ���
	{
		fscanf(fp,"%d",&num); // num���� ���ϵ����Ͱ��� ����
		dinsert_node( &head_node , create(num), 1); // num������ �������� ����Ʈ�� '1'��ġ�� ����
		file_count++; // ���� �����ͼ� ����
	}
	display( &head_node); // ����Ʈ ���

	// '0' �Ͻ� ����Ǵ� ���ѷ���
	while(1){ 
		printf("���� ���� �Է��ϼ���(0:����) :");
		scanf("%d",&delete_num);

		if ( delete_num == 0 )
			break;
		else
		{
			i=0; // i=0 �ʱ�ȭ
			while( i < file_count){ // file_count��ŭ �ݺ�
				dremove_node(&head_node,delete_num); // delete_num���� ����
				i++;
			}
			file_count = i; // file_count�� i�� �ʱ�ȭ
		}
		display( &head_node);  // ����Ʈ ���
		rdisplay( &head_node); // ����Ʈ ���� ���
		printf("\n");
	}

	fclose(fp); // ������ �ݽ��ϴ�
	return 0;
}