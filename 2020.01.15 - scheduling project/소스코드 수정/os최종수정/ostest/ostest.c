#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define MAX_que 100
#define CPU_time 100
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct process process_pointer;
/* ���μ����� ���� ��� ����ü */
typedef struct process {
	process_pointer *next;	
	int pid;         // ���μ��� ��ȣ
	char prcID2[10]; // ���μ��� ID
	int burst_time;  // ���� �ð�
	int priority;    // �켱����
	int arrive;      // �����ð�
	int wait;	     // ���ð�
	int turnaround;  // ��ȯ�ð�
	int work;	     // �۾���
	int remain;      // ���� ����ð�
	int HRN_priority;// HRN �켱����
} process;	

/* �� �����층�� ���� ���μ��� ����ü ���� �� ready_queue ���� */
process_pointer *head = NULL, *tail = NULL,              // head, tail
	            *ready_head = NULL, *ready_tail = NULL,  // ready_queue
				*fcfs_h = NULL, *fcfs_t = NULL,          // FCFS
				*nosjf_h = NULL, *nosjf_t = NULL,        // SJF
				*psjf_h = NULL, *psjf_t = NULL,          // SRT
				*nopri_h = NULL, *nopri_t = NULL,        // Nonpreempt_Priority
				*ppri_h = NULL, *ppri_t = NULL,          // Preempt_Priority
				*rr_h = NULL, *rr_t = NULL;              // R_R

// �Լ� �����
void Menu();	// �޴� ��� �Լ�
void Scheduler_Selection(int select); // ���ϴ� CPU �����층 ���� �Լ�
void Make_Process();   // ���μ��� ���� �Լ�
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t); // ready_queue�� ���μ����� �߰��ϴ� �Լ�
void Process_Output(process_pointer **temp); // ������ ���μ����� ����ϴ� �Լ�
void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag); // ���� �۾����� ���μ����� ����ϴ� �Լ�
void Process_Result_Output(process_pointer **temp); // �����층 ���� ���μ��� ���¸� ����ϴ� �Լ�
void Sort(process_pointer **h, process_pointer **t, int algorithm); // �˰��� ���� ���μ����� ���� ���� ����
void Copynode(process_pointer *h, process_pointer *temp); // ���μ��� ���� �Լ�
void Copyqueue(process_pointer **node, process_pointer **node_head, process_pointer **node_tail); // ���μ��� ť ���� �Լ�
void Result_add(int falg, process_pointer **ready_head); // flag�� ���� �����ٸ��� �����ϴ� �Լ�
void Process_Result_Output_HRN(process_pointer **temp);  // HRN ���μ����� ���¸� ����ϴ� �Լ�

void Nonpreempt(int flag);		// �� ���� �����ٸ� ���� ����
void Preempt(int flag);			// ���� �����ٸ� ���� ����
void R_Rpreempt(int flag);		// ���� �κ� �����ٸ� ���� ���� 
void FCFS();					// FCFS
void SJF();						// SJF
void SRT();						// SRT 
void Nonpreempt_Priority();		// ���� Priorty
void Preempt_Priority();		// ���� Priorty
void R_R();						// Round-Robin
void HRN();						// HRN

void bubble_sort(process arr[], int count);	// ����


int process_num = 0; // ���μ��� ����
int quantum;	     // �ð� �Ҵ緮


// ���� �Լ�
main()
{
	Menu();
}	

// �޴� �Լ�
void Menu()
{
	int select = 0;
	printf("\n\t <�����ٸ� �ùķ����� by. �麴��>\n");
	printf("\t������������������������������������������������������������������\n");
	printf("\t��  0  ��  ���μ��� ����\t\t��\n");
	printf("\t��  1  ��  FCFS\t\t\t��\n");
	printf("\t��  2  ��  SJF\t\t\t��\n");
	printf("\t��  3  ��  SRT\t\t\t��\n");
	printf("\t��  4  ��  ���� Priority\t��\n");
	printf("\t��  5  ��  ���� Priority\t\t��\n");
	printf("\t��  6  ��  Round-Robin\t\t��\n");
	printf("\t��  7  ��  HRN\t\t\t��\n");
	printf("\t��  8  ��  �ùķ����� ����\t��\n");
	printf("\t������������������������������������������������������������������\n");
	printf("\n\t �� ���ϴ� �۾��� �����ϼ��� : ");	
	scanf("%d", &select);
	Scheduler_Selection(select); // CPU �����췯 ���α׷� ����
}

// CPU �����ٷ� ���α׷� ���� �Լ�
void Scheduler_Selection(int select) 
{
	if(select != 0 && select != 8 && head == NULL)
	{
		printf("\n\t���μ����� �����ϼ���.\n\n");
		Menu();
	}
	
	switch(select)
	{
		case 0: Make_Process();			// ���μ��� ����
			break;
		case 1: FCFS();					// FCFS
			break;
		case 2: SJF();					// SJF
			break;
		case 3: SRT();					// SRT
			break;		
		case 4: Nonpreempt_Priority();	// ���� Priorty
			break;
		case 5: Preempt_Priority();		// ���� Priorty
			break;
		case 6: R_R();					// Round-Robin
			break;
		case 7 : HRN();					// HRN
			break;
		case 8 : printf("\n\t�ùķ����͸� �����մϴ�.\n\n\t");
			exit(0);				    // ����
	}
}

// ���μ��� ���� �Լ�
void Make_Process()
{
	int i;
	int CPU_TIME_VALUE;
	int CPU_TIME_VALUE2;
	int PROCESS_NUM_VALUE;
	long seed;
	int max=0;
	char prcID[10];

	int tmp1[100];
	int tmp2[100];
	int tmp3[100];
	int hrn_pri;
	process data[MAX_que];		// �����͸� ������ ����ü
	FILE *fp = fopen("data.txt", "r");

	process_pointer *temp;
	head = NULL, tail = NULL;

	seed = time(NULL);
    srand(seed);
	// ���μ��� ����
	// ���μ��� ���� �Է�
	printf("\n\t���μ��� ����(100�� ����) : ");
	fscanf(fp, "%d", &process_num);
	printf("%d", process_num);
	
	// ���μ��� ������ �ִ� ���� �ʰ���, ���α׷� ����
	while(process_num > MAX_que)
	{
		printf("���μ����� �ִ� ������ �Ѿ����ϴ�!\n");
		exit(1);
	}
	printf("\n");
	for(i = 1; i <= process_num; i++) 
	{	
		printf("\tProcess %d \n",i);
		fscanf(fp, "%s %d %d %d", prcID, &CPU_TIME_VALUE,&CPU_TIME_VALUE2,&PROCESS_NUM_VALUE);
		printf("\n\t���μ��� ID : %s\n\t���� �ð� : %d \n\t���� �ð� : %d\n\t�켱 ���� : %d\n\n", prcID, CPU_TIME_VALUE,CPU_TIME_VALUE2,PROCESS_NUM_VALUE);
		data[i].arrive = CPU_TIME_VALUE;		// �����ð�
		data[i].burst_time = CPU_TIME_VALUE2;	// ����ð�
		data[i].priority = PROCESS_NUM_VALUE;	// �켱����
		data[i].pid = i;
		strcpy(data[i].prcID2, prcID);
	}
		
	bubble_sort(data,process_num);


	// ���μ��� ������ �ʱ�ȭ
	printf("\n");
	printf("\t* �Է¹��� ���μ���ID, �����ð�, ����ð�, �켱���� *\n");
	for(i = 1; i <= process_num; i++) 
	{
		if(max<data[i].burst_time)
			max=data[i].burst_time;
		tmp2[i-1]=data[i].arrive;		// ���� �ð�
		tmp1[i-1]=data[i].burst_time;	// ����ð�
		tmp3[i-1]=data[i].priority;		// �켱 ����
		
		temp = (process_pointer *)malloc(sizeof(process_pointer)); 
		temp -> pid = data[i].pid;
		strcpy(temp -> prcID2, data[i].prcID2);
		temp -> burst_time = tmp1[i-1];	// ����ð� ����
		

		temp -> arrive = tmp2[i-1];		// ���� �ð� ����
		temp -> priority = tmp3[i-1];	// �켱 ���� ����
		temp -> wait = 0;		
		temp -> turnaround = 0;	
		temp -> work = 0;	
		temp -> remain = temp -> burst_time;	

		temp -> next = NULL;

		hrn_pri=((max-tmp2[i-1])+tmp1[i-1]) / tmp1[i-1];	// �����ð� ���

		temp -> HRN_priority=hrn_pri;


		Add_Queue(temp, &head, &tail); 
	}
	// �ð��Ҵ緮 �ʱ�ȭ
	fscanf(fp, "%d", &quantum);
	printf("\t�ð� �Ҵ緮 : %d\n\n", quantum);

	temp = head; // temp�� head�� �ʱ�ȭ
	Process_Output(&temp); // ���μ��� ���� ���
	temp = head; // temp�� head�� �ʱ�ȭ
	Menu();      // �޴� �Լ�
}

// ���μ����� ť�� ����
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t)
{	
	if(*h != NULL ) (*t)->next = temp; 	
	else *h = temp; 	
	*t = temp;
}

// flag�� ���� �����ٸ��� �����ϴ� �Լ� 
void Result_add(int falg, process_pointer **node)
{
	process_pointer *temp;
	switch(falg)
	{
		case 1: // FCFS
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &fcfs_h, &fcfs_t);
				break;
		case 2: // SJF
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nosjf_h, &nosjf_t);
				break;
		case 3: // SRT
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &psjf_h, &psjf_t);
				break;
		case 4:	// Nonpreempt_Priority
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nopri_h, &nopri_t);
				break;
		case 5: // Preempt_Priority
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &ppri_h, &ppri_t);
				break;
		case 6: // R_R
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &rr_h, &rr_t);
				break;
		case 7: // HRN
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nopri_h, &nopri_t);
				break;
		default: printf("����"); // ����
				exit(0);
	}
}

// ǥ ����
void Process_Output(process_pointer **temp) 
{
	printf("\n\n");
	printf("\t<������ ���μ���>\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\t�� ID  ����ð�  �����ð�  �켱����  ���ð�   �۾���   ������   ����ð���\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	// ������ ��¹�
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t�� %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    ��\n",(*temp) -> prcID2, (*temp) -> burst_time, 
			(*temp) -> arrive, (*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t����������������������������������������������������������������������������������������������������������������������������������������������������  \n");
	printf("\n");
}

// ���� �۾����� ���μ����� ����ϴ� �Լ�
void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag)
{
	int count=0;
	process_pointer *ready_node, *node, *node_f;
	ready_node = *ready_head;

	if(ready_node != NULL)
	{
			printf(" %2s ",ready_node->prcID2);
			ready_node = ready_node->next;
	}
}

// �����층 ���� ���μ��� ���¸� ����ϴ� �Լ�
void Process_Result_Output(process_pointer **temp)
{
	printf("\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\t�� ID  ����ð�  �����ð�  �켱����  ���ð�   �۾���   ������   ����ð���\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	// ������ ��¹�
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t�� %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    ��\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
			(*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t����������������������������������������������������������������������������������������������������������������������������������������������������  \n");
	printf("\n");

}

// HRN ���μ����� ���¸� ����ϴ� �Լ�
void Process_Result_Output_HRN(process_pointer **temp)
{
	printf("\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\t�� ID  ����ð�  �����ð�  �켱����  ���ð�   �۾���   ������   ����ð���\n");
	printf("\t���������������������������������������������������������������������������������������������������������������������������������������������������� \n");
	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t�� %2s  %6d  %7d    %5d  %8d  %8d  %7d  %8d    ��\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
		(*temp) ->HRN_priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
	printf("\t����������������������������������������������������������������������������������������������������������������������������������������������������\n");
	printf("\n");
}

// ���μ��� ���� �Լ�
void Copynode(process_pointer *h, process_pointer *temp)
{	
	temp -> pid = h -> pid;
	strcpy(temp -> prcID2, h -> prcID2);
	temp -> HRN_priority = h->HRN_priority;
	temp -> burst_time = h -> burst_time;	
	temp -> priority = h -> priority; 
	temp -> arrive = h -> arrive;	
	temp -> wait = h -> wait;
	temp -> turnaround = h -> turnaround;
	temp -> work = h -> work;
	temp -> remain = h -> remain;
	temp -> next = NULL;	
}

// ���μ��� ť ���� �Լ�
void Copyqueue(process_pointer **node, process_pointer **node_head, process_pointer **node_tail)
{
	process_pointer *temp;

	for(; *node; *node = (*node)->next) 
	{
		temp = (process_pointer *)malloc(sizeof(process_pointer));
		Copynode(*node, temp);
		Add_Queue(temp, node_head, node_tail);
	}
}

// �˰��� ���� ���μ����� ���� ���� ����
void Sort(process_pointer **h, process_pointer **t, int algorithm)
{
	int flag = 1;
	process_pointer *start, *mid, *end, *h1, *h2, *t1, *temp;
	h1 = (process_pointer *)malloc(sizeof(process_pointer));
	t1 = (process_pointer *)malloc(sizeof(process_pointer));
	(*t)->next = (process_pointer *)malloc(sizeof(process_pointer));

	h1 -> next = *h;	
	t1 = (*t)->next;
	t1 -> next = NULL;
	
	while(1 == flag) 
	{
		flag = 0;
		start = h1;
		mid = start -> next;
		end = mid -> next;

		while(end != t1)
		{
			if(algorithm ==1) 
			{
				if(mid -> arrive > end -> arrive)
				{
					printf("%d",t1->pid);
					start -> next = end;
					mid -> next = end->next;
					end->next = mid;
					flag = 1;
				}
			}
			else if(algorithm == 2)	
			{
				if(mid -> burst_time > end -> burst_time)
				{
					start -> next = end;
					mid -> next = end->next;
					end->next = mid;
					flag = 1;
				}

			}
			else if(algorithm == 3)	
			{
				if(mid -> remain > end -> remain)
				{
					start -> next = end;
					mid -> next = end->next;
					end->next = mid;
					flag = 1;
				}
			}
			else if(algorithm == 4 || algorithm == 5)
			{	
				if(mid -> priority > end -> priority)
				{
					start -> next = end;
					mid -> next = end->next;
					end->next = mid;
					flag = 1;
				}
			}
			else if(algorithm == 7)
			{
				if(mid -> HRN_priority > end -> HRN_priority)
				{
					start -> next = end;
					mid -> next = end->next;
					end->next = mid;
					flag = 1;
				}
			}

			start = start->next;
			mid = start->next;
			end = mid->next;
		}
	}

	*h = h1->next;	
	
	flag = 1;
	h2 = h1;

	while(1 == flag) {	
		if(h2->next == NULL)
		{
			flag = 0;
			*t = temp; 
			(*t)->next = NULL;
		}
		else
		{
			temp = h2;
			h2 = h2->next;
		}
	}
	free(h1);
	free(t1);
}

// FCFS
void FCFS()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer=0;

	// �ʱ�ȭ
	fcfs_h = NULL, fcfs_t = NULL;
	printf("\n\t");
	Nonpreempt(1); // �� ���� �����ٸ� ���� ���� 'FCFS'

	// FCFS ���μ��� ���ǥ ���
	temp = fcfs_h;
	printf("\n\n\t<FCFS �����ٸ�>");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ��� 
	temp = fcfs_h;
	aver_wait = 0, aver_turn = 0, aver_answer = 0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; fcfs_h; fcfs_h = fcfs_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",fcfs_h->prcID2,fcfs_h->wait,fcfs_h->turnaround,(fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time);
		aver_wait += fcfs_h->wait;
		aver_turn += fcfs_h->turnaround;
		aver_answer += (fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time;
	}

	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// SJF
void SJF()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// �ʱ�ȭ
	nosjf_h = NULL, nosjf_t = NULL;
	printf("\n\t");
	Nonpreempt(2);// �� ���� �����ٸ� ���� ���� 'SJF'

	// SJF ���μ��� ���ǥ ���
	temp = nosjf_h;
	printf("\n\n\t<SJF �����ٸ�>");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
	temp = nosjf_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; nosjf_h; nosjf_h = nosjf_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",nosjf_h->prcID2,nosjf_h->wait,nosjf_h->turnaround,(nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time);
		aver_wait += nosjf_h->wait;
		aver_turn += nosjf_h->turnaround;
		aver_answer += (nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// SRT
void SRT()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// �ʱ�ȭ
	psjf_h = NULL, psjf_t = NULL;
	printf("\n\t");
	Preempt(3); // ���� �����ٸ� ���� ���� 'SRT'

	// SRT ���μ��� ���ǥ ���
	temp = psjf_h;
	printf("\n\n\t<SRT �����ٸ�>");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
    temp = psjf_h;
    aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; psjf_h; psjf_h = psjf_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",psjf_h->prcID2,psjf_h->wait,psjf_h->turnaround,(psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time);
		aver_wait += psjf_h->wait;
		aver_turn += psjf_h->turnaround;
		aver_answer += (psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// Nonpreempt_Priority
void Nonpreempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0,aver_answer = 0;

	// �ʱ�ȭ
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(4); // ���� �����ٸ� ���� ���� 'Nonpreempt_Priority'

	// ���� Priority ���μ��� ���ǥ ���
	temp = nopri_h;
	printf("\n\n\t<���� Priority �����ٸ�>");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// Preempt_Priority
void Preempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// �ʱ�ȭ
	ppri_h = NULL, ppri_t = NULL;
	printf("\n\t");
	Preempt(5); // ���� �����ٸ� ���� ���� 'Preempt_Priority'

	// ���� Priority ���μ��� ���ǥ ���
	temp = ppri_h;
	printf("\n\n\t<���� Priority �����ٸ�>");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
	temp = ppri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; ppri_h; ppri_h = ppri_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",ppri_h->prcID2,ppri_h->wait,ppri_h->turnaround,(ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time);
		aver_wait += ppri_h->wait;
		aver_turn += ppri_h->turnaround;
		aver_answer += (ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// R_R
void R_R()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// �ʱ�ȭ
	rr_h = NULL, rr_t = NULL;

	// ���� ���
	printf("\t TQ ���� �Է� : ");
	printf("%d", quantum);
	printf("\n\t");
	R_Rpreempt(6); // R_R �����ٸ� ���� ���� 'R_R'

	// R_R ���μ��� ���ǥ ���
	temp = rr_h;
	printf("\n\n\tRound-Robin �����ٸ�");
	Process_Result_Output(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
	temp = rr_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; rr_h; rr_h = rr_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",rr_h->prcID2,rr_h->wait,rr_h->turnaround,(rr_h->wait+rr_h->burst_time)/rr_h->burst_time);
		aver_wait += rr_h->wait;
		aver_turn += rr_h->turnaround;
		aver_answer += (rr_h->wait+rr_h->burst_time)/rr_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	printf("\n");
	Menu();
}

// HRN
void HRN()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// �ʱ�ȭ
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(7); // ���� �����ٸ� ���� ���� 'HRN'

	// HRN ���μ��� ���ǥ ���
	temp = nopri_h;
	printf("\n\n\t<HRN �����ٸ�>");
	Process_Result_Output_HRN(&temp);

	// ��� ��� �ð�,��� ��ȯ �ð� ���
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t������������������������������������������������������������������������������ \n");
	printf("\t��  ID     ���ð�  ��ȯ�ð�  ����ð���\n");
	printf("\t������������������������������������������������������������������������������ \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t��  %2s    %7d  %7d   %7d   ��\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t��  ���  %7.3f   %7.3f   %7.3f  ��\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t������������������������������������������������������������������������������  \n");
	Menu();
}

// ���� ��� �Լ�
void Nonpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// �ʱ�ȭ
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// ���μ��� ť ���� �Լ�
	Copyqueue(&node, &node_head, &node_tail); 
	
	while(exit_num < process_num)
	{
		node = node_head; // node ��� �ʱ�ȭ

		// ��尡 ������ ���
		while(node != NULL && node -> arrive == time )
		{
			// temp �����Ҵ�
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp ���μ��� ����
			Copynode(node, temp);
			// ����Ǵ� ���μ����� temp ����
			Add_Queue(temp, &ready_head, &ready_tail);
			node = node -> next;
			node_head = node_head-> next;			
		}
		
		if(cpu == -2)
		{
			cpu = -1; 

			Result_add(flag, &ready_head);

			ready_head = ready_head->next;

			if(ready_head != NULL)
			{
				if(flag == 2) 
					Sort(&ready_head, &ready_tail, flag);
				if(flag == 4)	
					Sort(&ready_head, &ready_tail, flag);
				if(flag == 7)	
					Sort(&ready_head, &ready_tail, flag);
			}			
		}
		// ready ��� �ʱ�ȭ
		ready_node = ready_head;

		// ready_node �ݺ�
		while(ready_node != NULL)
		{
			if(cpu == ready_node->pid)
			{
				if(ready_node->remain == 1)
				{	
					exit_num++; 
					cpu = -2; 
				}
				ready_node->work++;
				ready_node->remain--;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			else if(cpu == -1) 
			{
				cpu = ready_node->pid; 
				if(ready_node->remain == 1)
				{
					exit_num++;
					cpu = -2;
				}
				ready_node->work++;
				ready_node->remain--;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			else
			{	
				ready_node->wait++;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			ready_node = ready_node->next;
		}
		// ���� �۾����� ���μ����� ����ϴ� �Լ�
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// �� ����
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- �� ����");
	// flag�� ���� �����ٸ��� �����ϴ� �Լ�
	printf("\n\t ��Ʈ��Ʈ ���� : %d\n",time);
	Result_add(flag, &ready_head);
}

// ���� ��� �Լ�
void Preempt(int flag)
{	
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// �ʱ�ȭ
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// ���μ��� ť ���� �Լ�
	Copyqueue(&node, &node_head, &node_tail);

	while(exit_num < process_num)
	{
		node = node_head;

		while(node != NULL && node -> arrive == time )
		{
			// temp �����Ҵ�
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp ���μ��� ����
			Copynode(node, temp);
			// ����Ǵ� ���μ����� temp ����
			Add_Queue(temp, &ready_head, &ready_tail);		
			node = node -> next;	
			node_head = node_head-> next;			
		}
		if(cpu == -2)
		{
			Result_add(flag, &ready_head);
			cpu = -1;
			ready_head = ready_head->next;
		}
		if(ready_head != NULL)
		{
			if(flag == 3)	
				Sort(&ready_head, &ready_tail, flag);
			if(flag == 5)	
				Sort(&ready_head, &ready_tail, flag);
			cpu = ready_head->pid;	
		}			
		ready_node = ready_head;

		while(ready_node != NULL)
		{
			if(cpu == ready_node->pid)
			{
				if(ready_node->remain == 1)
				{
					exit_num++;
					cpu = -2;
				}
				ready_node->work++;
				ready_node->remain--;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			else
			{
				ready_node->wait++;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			ready_node = ready_node->next;
		}		
		// ���� �۾����� ���μ����� ����ϴ� �Լ�
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// �� ����
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- �� ����");
	// flag�� ���� �����ٸ��� �����ϴ� �Լ�
	printf("\n\t ��Ʈ��Ʈ ���� : %d\n",time);
	Result_add(flag, &ready_head);
}

// ���� �κ� �����ٸ� ���� ���� 
void R_Rpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, timequantum = 0, exit_num = 0;
	// �ʱ�ȭ
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// ���μ��� ť ���� �Լ�
	Copyqueue(&node, &node_head, &node_tail);
	
	while(exit_num < process_num)
	{
		node = node_head;

		while(node != NULL && node -> arrive == time )
		{	
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			Copynode(node, temp);
			Add_Queue(temp, &ready_head, &ready_tail);
			
			node = node -> next; 
	
			node_head = node_head-> next;			
		}

		if(cpu < 0 || timequantum == 0)
		{	
			timequantum = quantum;
			if(cpu >= 0)
			{
				// temp �����Ҵ�
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				// temp ���μ��� ����
				Copynode(ready_head, temp);
				// ����Ǵ� ���μ����� temp ����
				Add_Queue(temp, &ready_head, &ready_tail);
				ready_head = ready_head->next;

			}
			else if(cpu == -2)
			{
				Result_add(flag, &ready_head); // flag�� ���� �����ٸ��� ����
				cpu = -1;
				ready_head = ready_head->next;

			}
			if(ready_head != NULL)
				cpu = ready_head->pid;
		}
		ready_node = ready_head;

		while(ready_node != NULL)
		{
			if(cpu == ready_node->pid)
			{
				if(ready_node->remain == 1)
				{	
					exit_num++; 
					cpu = -2; 
				}
				ready_node->work++;
				ready_node->remain--;
				ready_node->turnaround = ready_node->wait + ready_node->work;
				timequantum--;
			}
			else
			{	
				ready_node->wait++;
				ready_node->turnaround = ready_node->wait + ready_node->work;
			}
			ready_node = ready_node->next;
		}
		// ���� �۾����� ���μ����� ����ϴ� �Լ�
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// �� ����
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- �� ����");
	// flag�� ���� �����ٸ��� �����ϴ� �Լ�
	printf("\n\t ��Ʈ��Ʈ ���� : %d\n",time);
	Result_add(flag, &ready_head);
}



void bubble_sort(process arr[], int count)    // �Ű������� ������ �迭�� ����� ������ ����
{
	int i,j;
    process temp;

    for (i = 1; i <= count; i++)    // ����� ������ŭ �ݺ�
    {
        for (j = 1; j <= count - 1; j++)   // ����� ���� - 1��ŭ �ݺ�
        {
			if (arr[j].arrive> arr[j + 1].arrive)          // ���� ����� ���� ���� ����� ���� ���Ͽ�
            {                                 // ū ����
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;            // ���� ��ҷ� ����
            }
        }
    }
}