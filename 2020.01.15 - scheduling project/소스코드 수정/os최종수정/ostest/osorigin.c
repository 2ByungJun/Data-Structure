#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MAX_que 100
#define CPU_time 100

typedef struct process process_pointer;
typedef struct process {
	process_pointer *next;	
	int pid;
	int burst_time;
	int priority;
	int arrive;
	int wait;	
	int turnaround;	
	int work;	
	int remain;
	int HRN_priority;
} process;	

process_pointer *head = NULL, *tail = NULL, *ready_head = NULL, *ready_tail = NULL,
				*fcfs_h = NULL, *fcfs_t = NULL, *nosjf_h = NULL, *nosjf_t = NULL,
				*psjf_h = NULL, *psjf_t = NULL, *nopri_h = NULL, *nopri_t = NULL,
				*ppri_h = NULL, *ppri_t = NULL, *rr_h = NULL, *rr_t = NULL;

void Menu();
void Scheduler_Selection(int select);
void Make_Process(); 
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t);
void Process_Output(process_pointer **temp);
void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag);
void Process_Result_Output(process_pointer **temp);
void Sort(process_pointer **h, process_pointer **t, int algorithm);
void Copynode(process_pointer *h, process_pointer *temp);
void Copyqueue(process_pointer **node, process_pointer **node_head, process_pointer **node_tail);
void Result_add(int falg, process_pointer **ready_head);

void Nonpreempt(int flag);
void Preempt(int flag);
void R_Rpreempt(int flag);
void FCFS();					//FCFS
void SJF();						//SJF
void SRT();						//SRT 
void Nonpreempt_Priority();		//비선점 Priorty
void Preempt_Priority();		//선점 Priorty
void R_R();						//Round-Robin
void HRN();						//HRN
//void Evaluation();				//모든 스케줄링 실행

int process_num = 0;
int quantum = 0;	

//메인 함수
main()
{
	Menu();
}	

//메뉴 함수
void Menu()
{
	int select = 0;
	printf("\n\t      <Scheduling Simulator>\n");
	printf("\t=================================\n");
	printf("\t|  0  ->  프로세스 생성\t\t|\n");
	printf("\t|  1  ->  FCFS\t\t\t|\n");
	printf("\t|  2  ->  SJF\t\t\t|\n");
	printf("\t|  3  ->  SRT\t\t\t|\n");
	printf("\t|  4  ->  비선점 Priority\t|\n");
	printf("\t|  5  ->  선점 Priority\t\t|\n");
	printf("\t|  6  ->  Round-Robin\t\t|\n");
	printf("\t|  7  ->  HRN\t\t\t|\n");
	printf("\t|  8  ->  시뮬레이터 종료\t|\n");
	printf("\t=================================\n");
	printf("\n\n\t실행할 서비스를 입력하세요 : ");	
	scanf("%d", &select);
	Scheduler_Selection(select);
}

//CPU 스케줄러 프로그램 실행
void Scheduler_Selection(int select) 
{

	if(select != 0 && select != 8 && head == NULL)
	{
		printf("\n\t프로세스를 생성하세요.\n\n");
		Menu();
	}
	
	switch(select)
	{
		case 0: Make_Process();			//프로세스 생성
			break;
		case 1: FCFS();					//FCFS
			break;
		case 2: SJF();					//SJF
			break;
		case 3: SRT();					//SRT
			break;		
		case 4: Nonpreempt_Priority();	//비선점 Priorty
			break;
		case 5: Preempt_Priority();		//선점 Priorty
			break;
		case 6: R_R();					//Round-Robin
			break;
		case 7 : HRN();					//HRN
			break;
		case 8 : printf("\n\t시뮬레이터를 종료합니다.\n\n\t");
			exit(0);				//종료
	}
}

//프로세스 생성 함수
void Make_Process()
{
	int i;
	int CPU_TIME_VALUE;
	int CPU_TIME_VALUE2;
	int PROCESS_NUM_VALUE;
	long seed;
	int max=0;
	int tmp1[100];
	int tmp2[100];
	int tmp3[100];
	int hrn_pri;

	process_pointer *temp;
	head = NULL, tail = NULL;

	seed = time(NULL);
    srand(seed);
	
	printf("\n\t프로세스 개수(최대 100개) : ");
	scanf("%d", &process_num);
	
	while(process_num > MAX_que)
	{
		printf("프로세스는 100개 이하로 생성해주세요!\n");
		scanf("%d", &process_num);
	}

	printf("\n");
	printf("\t* 실행시간, 도착시간, 우선순위를 순서대로 입력 *\n");
	for(i = 1; i <= process_num; i++) 
	{	
		printf("\tProcess %d : ",i);
		scanf("%d %d %d",&CPU_TIME_VALUE,&CPU_TIME_VALUE2,&PROCESS_NUM_VALUE);

		if(max<CPU_TIME_VALUE2)
			max=CPU_TIME_VALUE2;
		tmp1[i-1]=CPU_TIME_VALUE;
		tmp2[i-1]=CPU_TIME_VALUE2;
		tmp3[i-1]=PROCESS_NUM_VALUE;

		temp = (process_pointer *)malloc(sizeof(process_pointer)); 
		temp -> pid = i;	
		temp -> burst_time = tmp1[i-1];
		temp -> arrive = tmp2[i-1];
		temp -> priority = tmp3[i-1];
		temp -> wait = 0;	
		temp -> turnaround = 0;	
		temp -> work = 0;	
		temp -> remain = temp -> burst_time;	
		temp -> next = NULL;
		hrn_pri=((max-tmp2[i-1])+tmp1[i-1]) / tmp1[i-1];
		temp -> HRN_priority=hrn_pri;
		Add_Queue(temp, &head, &tail); 
	}

	/*for(i = 1; i <= process_num; i++) 
	{
		temp = (process_pointer *)malloc(sizeof(process_pointer)); 
		temp -> pid = i;	
		temp -> burst_time = tmp1[i-1];
		temp -> arrive = tmp2[i-1];
		temp -> priority = tmp3[i-1];
		temp -> wait = 0;	
		temp -> turnaround = 0;	
		temp -> work = 0;	
		temp -> remain = temp -> burst_time;	
		temp -> next = NULL;
		hrn_pri=((max-tmp2[i-1])+tmp1[i-1]) / tmp1[i-1];
		temp -> HRN_priority=hrn_pri;
		Add_Queue(temp, &head, &tail); 
	}*/

	temp = head;
	Process_Output(&temp);
	temp=head;	
	Menu();
}

//프로세스를 큐에 삽입
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t)
{	
	if(*h != NULL ) (*t)->next = temp; 	
	else *h = temp; 	
	*t = temp;
}


void Result_add(int falg, process_pointer **node)
{
	process_pointer *temp;
	switch(falg)
	{
		case 1:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &fcfs_h, &fcfs_t);
				break;
		case 2:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nosjf_h, &nosjf_t);
				break;
		case 3:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &psjf_h, &psjf_t);
				break;
		case 4:	
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nopri_h, &nopri_t);
				break;
		case 5:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &ppri_h, &ppri_t);
				break;
		case 6:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &rr_h, &rr_t);
				break;
		case 7:
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(*node, temp);
				Add_Queue(temp, &nopri_h, &nopri_t);
				break;
		default: printf("에러");
				exit(0);
	}
}

//표 생성
void Process_Output(process_pointer **temp) 
{
	printf("\n\n");
	printf("\t<생성된 프로세스>\n");
	printf("\t______________________________________________________________ \n");
	printf("\t ID  실행시간  도착시간  우선순위  대기시간   작업량   남은량  \n");
	printf("\t______________________________________________________________ \n");

	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t%2d  %6d  %8d  %8d  %8d  %8d  %7d  \n",(*temp) -> pid, (*temp) -> burst_time, (*temp) -> arrive, (*temp) -> priority + 1, (*temp) -> wait, (*temp) -> work, (*temp) -> remain);
	printf("\t______________________________________________________________ \n");
	printf("\n");
}

void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag)
{
	int count=0;
	process_pointer *ready_node, *node;
	ready_node = *ready_head;

	if(ready_node != NULL)
	{
		printf("%2d",ready_node->pid);
		ready_node = ready_node->next;
	}
}


void Process_Result_Output(process_pointer **temp)
{
	printf("\n");
	printf("\t______________________________________________________________ \n");
	printf("\tID  실행시간  도착시간  우선순위  대기시간   작업량   남은량  \n");
	printf("\t______________________________________________________________ \n");

	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t%2d  %6d  %8d  %8d  %8d  %8d  %7d  \n",(*temp) -> pid, (*temp) -> burst_time, (*temp) -> arrive, (*temp) -> priority + 1, (*temp) -> wait, (*temp) -> work, (*temp) -> remain);
	printf("\t______________________________________________________________ \n");
	printf("\n");
}

void Process_Result_Output_HRN(process_pointer **temp)
{
	printf("\n");
	printf("\t______________________________________________________________ \n");
	printf("\tID  실행시간  도착시간  우선순위  대기시간   작업량   남은량  \n");
	printf("\t______________________________________________________________ \n");

	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t%2d  %6d  %7d    %5d  %8d  %8d  %7d  \n",(*temp) -> pid, (*temp) -> burst_time, (*temp) -> arrive, (*temp) ->HRN_priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain);
	printf("\t______________________________________________________________ \n");
	printf("\n");
}


void Copynode(process_pointer *h, process_pointer *temp)
{	
	temp -> pid = h -> pid;	
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


void FCFS()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	fcfs_h = NULL, fcfs_t = NULL;
	printf("\n\t");
	Nonpreempt(1);

	temp = fcfs_h;
	printf("\n\n\t<FCFS 스케줄링>");
	Process_Result_Output(&temp);
	temp = fcfs_h;
	aver_wait = 0, aver_turn = 0;
	for(; fcfs_h; fcfs_h = fcfs_h->next)
	{
		aver_wait += fcfs_h->wait;
		aver_turn += fcfs_h->turnaround;
	}

	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", aver_wait, aver_turn);
	Menu();
}


void SJF()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	nosjf_h = NULL, nosjf_t = NULL;
	printf("\n\t");
	Nonpreempt(2);

	temp = nosjf_h;
	printf("\n\n\t<SJF 스케줄링>");
	Process_Result_Output(&temp);
	temp = nosjf_h;
	aver_wait = 0, aver_turn = 0;
	for(; nosjf_h; nosjf_h = nosjf_h->next)
	{
		aver_wait += nosjf_h->wait;
		aver_turn += nosjf_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", 
	aver_wait, aver_turn);

	Menu();
}


void SRT()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	psjf_h = NULL, psjf_t = NULL;
	printf("\n\t");
	Preempt(3);

	temp = psjf_h;
	printf("\n\n\t<SRT 스케줄링>");
	Process_Result_Output(&temp);
    temp = psjf_h;
    aver_wait = 0, aver_turn = 0;
	for(; psjf_h; psjf_h = psjf_h->next)
	{
		aver_wait += psjf_h->wait;
		aver_turn += psjf_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", 
		aver_wait, aver_turn);

	Menu();
}


void Nonpreempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(4);

	temp = nopri_h;
	printf("\n\n\t<비선점 Priority 스케줄링>");
	Process_Result_Output(&temp);
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0;
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", 
		aver_wait, aver_turn);

	Menu();
}


void Preempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	ppri_h = NULL, ppri_t = NULL;
	printf("\n\t");
	Preempt(5);

	temp = ppri_h;
	printf("\n\n\t<선점 Priority 스케줄링>");
	Process_Result_Output(&temp);
	temp = ppri_h;
	aver_wait = 0, aver_turn = 0;
	for(; ppri_h; ppri_h = ppri_h->next)
	{
		aver_wait += ppri_h->wait;
		aver_turn += ppri_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", 
		aver_wait, aver_turn);

	Menu();
}


void R_R()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	rr_h = NULL, rr_t = NULL;
	printf("\tTQ 간격 입력 : ");
	scanf("%d", &quantum);
	printf("\n\t");
	R_Rpreempt(6);

	temp = rr_h;
	printf("\n\n\tRound-Robin 스케줄링");
	Process_Result_Output(&temp);
	temp = rr_h;
	aver_wait = 0, aver_turn = 0;
	for(; rr_h; rr_h = rr_h->next)
	{
		aver_wait += rr_h->wait;
		aver_turn += rr_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n\n", 
		aver_wait, aver_turn);

	Menu();
}

void HRN()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0;

	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(7);

	temp = nopri_h;
	printf("\n\n\t<HRN 스케줄링>");
	Process_Result_Output_HRN(&temp);
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0;
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	printf("\t평균 대기 시간 = %.3f, 평균 반환 시간 = %.3f\n", 
		aver_wait, aver_turn);

	Menu();
}


void Nonpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;

	int time =0, cpu = -1, exit_num = 0;

	ready_head = NULL, ready_tail = NULL;
	node = head; 

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
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	printf("\n\t간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}


void Preempt(int flag)
{	
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;

	int time =0, cpu = -1, exit_num = 0;

	ready_head = NULL, ready_tail = NULL;
	node = head; 

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
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	printf("\n\t간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}


void R_Rpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;

	int time =0, cpu = -1, timequantum = 0, exit_num = 0;

	ready_head = NULL, ready_tail = NULL;
	node = head; 

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
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				Copynode(ready_head, temp);
				Add_Queue(temp, &ready_head, &ready_tail);
				ready_head = ready_head->next;

			}
			else if(cpu == -2)
			{
				Result_add(flag, &ready_head);
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

		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	printf("\n\t간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}
