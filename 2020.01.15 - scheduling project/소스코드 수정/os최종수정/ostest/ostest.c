#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define MAX_que 100
#define CPU_time 100
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct process process_pointer;
/* 프로세스의 구성 요소 구조체 */
typedef struct process {
	process_pointer *next;	
	int pid;         // 프로세스 번호
	char prcID2[10]; // 프로세스 ID
	int burst_time;  // 실행 시간
	int priority;    // 우선순위
	int arrive;      // 도착시간
	int wait;	     // 대기시간
	int turnaround;  // 반환시간
	int work;	     // 작업량
	int remain;      // 남은 수행시간
	int HRN_priority;// HRN 우선순위
} process;	

/* 각 스케쥴링을 위한 프로세스 구조체 선언 및 ready_queue 선언 */
process_pointer *head = NULL, *tail = NULL,              // head, tail
	            *ready_head = NULL, *ready_tail = NULL,  // ready_queue
				*fcfs_h = NULL, *fcfs_t = NULL,          // FCFS
				*nosjf_h = NULL, *nosjf_t = NULL,        // SJF
				*psjf_h = NULL, *psjf_t = NULL,          // SRT
				*nopri_h = NULL, *nopri_t = NULL,        // Nonpreempt_Priority
				*ppri_h = NULL, *ppri_t = NULL,          // Preempt_Priority
				*rr_h = NULL, *rr_t = NULL;              // R_R

// 함수 선언부
void Menu();	// 메뉴 출력 함수
void Scheduler_Selection(int select); // 원하는 CPU 스케쥴링 선택 함수
void Make_Process();   // 프로세스 생성 함수
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t); // ready_queue에 프로세스를 추가하는 함수
void Process_Output(process_pointer **temp); // 생성된 프로세스를 출력하는 함수
void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag); // 현재 작업중인 프로세스를 출력하는 함수
void Process_Result_Output(process_pointer **temp); // 스케쥴링 후의 프로세스 상태를 출력하는 함수
void Sort(process_pointer **h, process_pointer **t, int algorithm); // 알고리즘에 따른 프로세스의 진입 순서 정렬
void Copynode(process_pointer *h, process_pointer *temp); // 프로세스 복사 함수
void Copyqueue(process_pointer **node, process_pointer **node_head, process_pointer **node_tail); // 프로세스 큐 복사 함수
void Result_add(int falg, process_pointer **ready_head); // flag에 따라 스케줄링을 선택하는 함수
void Process_Result_Output_HRN(process_pointer **temp);  // HRN 프로세스의 상태를 출력하는 함수

void Nonpreempt(int flag);		// 비 선점 스케줄링 개념 구현
void Preempt(int flag);			// 선점 스케줄링 개념 구현
void R_Rpreempt(int flag);		// 라운드 로빈 스케줄링 개념 구현 
void FCFS();					// FCFS
void SJF();						// SJF
void SRT();						// SRT 
void Nonpreempt_Priority();		// 비선점 Priorty
void Preempt_Priority();		// 선점 Priorty
void R_R();						// Round-Robin
void HRN();						// HRN

void bubble_sort(process arr[], int count);	// 정렬


int process_num = 0; // 프로세스 갯수
int quantum;	     // 시간 할당량


// 메인 함수
main()
{
	Menu();
}	

// 메뉴 함수
void Menu()
{
	int select = 0;
	printf("\n\t <스케줄링 시뮬레이터 by. 백병전>\n");
	printf("\t┌───────────────────────────────┐\n");
	printf("\t│  0  →  프로세스 생성\t\t│\n");
	printf("\t│  1  →  FCFS\t\t\t│\n");
	printf("\t│  2  →  SJF\t\t\t│\n");
	printf("\t│  3  →  SRT\t\t\t│\n");
	printf("\t│  4  →  비선점 Priority\t│\n");
	printf("\t│  5  →  선점 Priority\t\t│\n");
	printf("\t│  6  →  Round-Robin\t\t│\n");
	printf("\t│  7  →  HRN\t\t\t│\n");
	printf("\t│  8  →  시뮬레이터 종료\t│\n");
	printf("\t└───────────────────────────────┘\n");
	printf("\n\t ▷ 원하는 작업을 선택하세요 : ");	
	scanf("%d", &select);
	Scheduler_Selection(select); // CPU 스케쥴러 프로그램 실행
}

// CPU 스케줄러 프로그램 실행 함수
void Scheduler_Selection(int select) 
{
	if(select != 0 && select != 8 && head == NULL)
	{
		printf("\n\t프로세스를 생성하세요.\n\n");
		Menu();
	}
	
	switch(select)
	{
		case 0: Make_Process();			// 프로세스 생성
			break;
		case 1: FCFS();					// FCFS
			break;
		case 2: SJF();					// SJF
			break;
		case 3: SRT();					// SRT
			break;		
		case 4: Nonpreempt_Priority();	// 비선점 Priorty
			break;
		case 5: Preempt_Priority();		// 선점 Priorty
			break;
		case 6: R_R();					// Round-Robin
			break;
		case 7 : HRN();					// HRN
			break;
		case 8 : printf("\n\t시뮬레이터를 종료합니다.\n\n\t");
			exit(0);				    // 종료
	}
}

// 프로세스 생성 함수
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
	process data[MAX_que];		// 데이터를 저장할 구조체
	FILE *fp = fopen("data.txt", "r");

	process_pointer *temp;
	head = NULL, tail = NULL;

	seed = time(NULL);
    srand(seed);
	// 프로세스 생성
	// 프로세스 갯수 입력
	printf("\n\t프로세스 개수(100개 이하) : ");
	fscanf(fp, "%d", &process_num);
	printf("%d", process_num);
	
	// 프로세스 갯수가 최대 갯수 초과시, 프로그램 종료
	while(process_num > MAX_que)
	{
		printf("프로세스가 최대 갯수를 넘었습니다!\n");
		exit(1);
	}
	printf("\n");
	for(i = 1; i <= process_num; i++) 
	{	
		printf("\tProcess %d \n",i);
		fscanf(fp, "%s %d %d %d", prcID, &CPU_TIME_VALUE,&CPU_TIME_VALUE2,&PROCESS_NUM_VALUE);
		printf("\n\t프로세스 ID : %s\n\t도착 시간 : %d \n\t실행 시간 : %d\n\t우선 순위 : %d\n\n", prcID, CPU_TIME_VALUE,CPU_TIME_VALUE2,PROCESS_NUM_VALUE);
		data[i].arrive = CPU_TIME_VALUE;		// 도착시간
		data[i].burst_time = CPU_TIME_VALUE2;	// 실행시간
		data[i].priority = PROCESS_NUM_VALUE;	// 우선순위
		data[i].pid = i;
		strcpy(data[i].prcID2, prcID);
	}
		
	bubble_sort(data,process_num);


	// 프로세스 데이터 초기화
	printf("\n");
	printf("\t* 입력받은 프로세스ID, 도착시간, 실행시간, 우선순위 *\n");
	for(i = 1; i <= process_num; i++) 
	{
		if(max<data[i].burst_time)
			max=data[i].burst_time;
		tmp2[i-1]=data[i].arrive;		// 도착 시간
		tmp1[i-1]=data[i].burst_time;	// 실행시간
		tmp3[i-1]=data[i].priority;		// 우선 순위
		
		temp = (process_pointer *)malloc(sizeof(process_pointer)); 
		temp -> pid = data[i].pid;
		strcpy(temp -> prcID2, data[i].prcID2);
		temp -> burst_time = tmp1[i-1];	// 실행시간 삽입
		

		temp -> arrive = tmp2[i-1];		// 도착 시간 삽입
		temp -> priority = tmp3[i-1];	// 우선 순위 삽입
		temp -> wait = 0;		
		temp -> turnaround = 0;	
		temp -> work = 0;	
		temp -> remain = temp -> burst_time;	

		temp -> next = NULL;

		hrn_pri=((max-tmp2[i-1])+tmp1[i-1]) / tmp1[i-1];	// 도착시간 계산

		temp -> HRN_priority=hrn_pri;


		Add_Queue(temp, &head, &tail); 
	}
	// 시간할당량 초기화
	fscanf(fp, "%d", &quantum);
	printf("\t시간 할당량 : %d\n\n", quantum);

	temp = head; // temp를 head로 초기화
	Process_Output(&temp); // 프로세스 생성 출력
	temp = head; // temp를 head로 초기화
	Menu();      // 메뉴 함수
}

// 프로세스를 큐에 삽입
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t)
{	
	if(*h != NULL ) (*t)->next = temp; 	
	else *h = temp; 	
	*t = temp;
}

// flag에 따라 스케줄링을 선택하는 함수 
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
		default: printf("에러"); // 종료
				exit(0);
	}
}

// 표 생성
void Process_Output(process_pointer **temp) 
{
	printf("\n\n");
	printf("\t<생성된 프로세스>\n");
	printf("\t┌────────────────────────────────────────────────────────────────────────┐ \n");
	printf("\t│ ID  실행시간  도착시간  우선순위  대기시간   작업량   남은량   응답시간│\n");
	printf("\t├────────────────────────────────────────────────────────────────────────┤ \n");
	// 데이터 출력문
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t│ %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    │\n",(*temp) -> prcID2, (*temp) -> burst_time, 
			(*temp) -> arrive, (*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t└────────────────────────────────────────────────────────────────────────┘  \n");
	printf("\n");
}

// 현재 작업중인 프로세스를 출력하는 함수
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

// 스케쥴링 후의 프로세스 상태를 출력하는 함수
void Process_Result_Output(process_pointer **temp)
{
	printf("\n");
	printf("\t┌────────────────────────────────────────────────────────────────────────┐ \n");
	printf("\t│ ID  실행시간  도착시간  우선순위  대기시간   작업량   남은량   응답시간│\n");
	printf("\t├────────────────────────────────────────────────────────────────────────┤ \n");
	// 데이터 출력문
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t│ %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    │\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
			(*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t└────────────────────────────────────────────────────────────────────────┘  \n");
	printf("\n");

}

// HRN 프로세스의 상태를 출력하는 함수
void Process_Result_Output_HRN(process_pointer **temp)
{
	printf("\n");
	printf("\t┌────────────────────────────────────────────────────────────────────────┐ \n");
	printf("\t│ ID  실행시간  도착시간  우선순위  대기시간   작업량   남은량   응답시간│\n");
	printf("\t├────────────────────────────────────────────────────────────────────────┤ \n");
	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t│ %2s  %6d  %7d    %5d  %8d  %8d  %7d  %8d    │\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
		(*temp) ->HRN_priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
	printf("\t└────────────────────────────────────────────────────────────────────────┘\n");
	printf("\n");
}

// 프로세스 복사 함수
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

// 프로세스 큐 복사 함수
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

// 알고리즘에 따른 프로세스의 진입 순서 정렬
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

	// 초기화
	fcfs_h = NULL, fcfs_t = NULL;
	printf("\n\t");
	Nonpreempt(1); // 비 선점 스케줄링 개념 구현 'FCFS'

	// FCFS 프로세스 결과표 출력
	temp = fcfs_h;
	printf("\n\n\t<FCFS 스케줄링>");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산 
	temp = fcfs_h;
	aver_wait = 0, aver_turn = 0, aver_answer = 0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; fcfs_h; fcfs_h = fcfs_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",fcfs_h->prcID2,fcfs_h->wait,fcfs_h->turnaround,(fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time);
		aver_wait += fcfs_h->wait;
		aver_turn += fcfs_h->turnaround;
		aver_answer += (fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time;
	}

	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// SJF
void SJF()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 초기화
	nosjf_h = NULL, nosjf_t = NULL;
	printf("\n\t");
	Nonpreempt(2);// 비 선점 스케줄링 개념 구현 'SJF'

	// SJF 프로세스 결과표 출력
	temp = nosjf_h;
	printf("\n\n\t<SJF 스케줄링>");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
	temp = nosjf_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; nosjf_h; nosjf_h = nosjf_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",nosjf_h->prcID2,nosjf_h->wait,nosjf_h->turnaround,(nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time);
		aver_wait += nosjf_h->wait;
		aver_turn += nosjf_h->turnaround;
		aver_answer += (nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// SRT
void SRT()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 초기화
	psjf_h = NULL, psjf_t = NULL;
	printf("\n\t");
	Preempt(3); // 선점 스케줄링 개념 구현 'SRT'

	// SRT 프로세스 결과표 출력
	temp = psjf_h;
	printf("\n\n\t<SRT 스케줄링>");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
    temp = psjf_h;
    aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; psjf_h; psjf_h = psjf_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",psjf_h->prcID2,psjf_h->wait,psjf_h->turnaround,(psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time);
		aver_wait += psjf_h->wait;
		aver_turn += psjf_h->turnaround;
		aver_answer += (psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// Nonpreempt_Priority
void Nonpreempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0,aver_answer = 0;

	// 초기화
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(4); // 비선점 스케줄링 개념 구현 'Nonpreempt_Priority'

	// 비선점 Priority 프로세스 결과표 출력
	temp = nopri_h;
	printf("\n\n\t<비선점 Priority 스케줄링>");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// Preempt_Priority
void Preempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 초기화
	ppri_h = NULL, ppri_t = NULL;
	printf("\n\t");
	Preempt(5); // 선점 스케줄링 개념 구현 'Preempt_Priority'

	// 선점 Priority 프로세스 결과표 출력
	temp = ppri_h;
	printf("\n\n\t<선점 Priority 스케줄링>");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
	temp = ppri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; ppri_h; ppri_h = ppri_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",ppri_h->prcID2,ppri_h->wait,ppri_h->turnaround,(ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time);
		aver_wait += ppri_h->wait;
		aver_turn += ppri_h->turnaround;
		aver_answer += (ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// R_R
void R_R()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 초기화
	rr_h = NULL, rr_t = NULL;

	// 간격 출력
	printf("\t TQ 간격 입력 : ");
	printf("%d", quantum);
	printf("\n\t");
	R_Rpreempt(6); // R_R 스케줄링 개념 구현 'R_R'

	// R_R 프로세스 결과표 출력
	temp = rr_h;
	printf("\n\n\tRound-Robin 스케줄링");
	Process_Result_Output(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
	temp = rr_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; rr_h; rr_h = rr_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",rr_h->prcID2,rr_h->wait,rr_h->turnaround,(rr_h->wait+rr_h->burst_time)/rr_h->burst_time);
		aver_wait += rr_h->wait;
		aver_turn += rr_h->turnaround;
		aver_answer += (rr_h->wait+rr_h->burst_time)/rr_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	printf("\n");
	Menu();
}

// HRN
void HRN()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 초기화
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(7); // 비선점 스케줄링 개념 구현 'HRN'

	// HRN 프로세스 결과표 출력
	temp = nopri_h;
	printf("\n\n\t<HRN 스케줄링>");
	Process_Result_Output_HRN(&temp);

	// 평균 대기 시간,평균 반환 시간 계산
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t┌─────────────────────────────────────┐ \n");
	printf("\t│  ID     대기시간  반환시간  응답시간│\n");
	printf("\t├─────────────────────────────────────┤ \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t│  %2s    %7d  %7d   %7d   │\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t│  평균  %7.3f   %7.3f   %7.3f  │\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t└─────────────────────────────────────┘  \n");
	Menu();
}

// 비선점 계산 함수
void Nonpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// 초기화
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// 프로세스 큐 복사 함수
	Copyqueue(&node, &node_head, &node_tail); 
	
	while(exit_num < process_num)
	{
		node = node_head; // node 헤드 초기화

		// 노드가 도착할 경우
		while(node != NULL && node -> arrive == time )
		{
			// temp 동적할당
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp 프로세스 복사
			Copynode(node, temp);
			// 실행되는 프로세스에 temp 적용
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
		// ready 노드 초기화
		ready_node = ready_head;

		// ready_node 반복
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
		// 현재 작업중인 프로세스를 출력하는 함수
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 초 단위
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 초 단위");
	// flag에 따라 스케줄링을 선택하는 함수
	printf("\n\t 간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}

// 선점 계산 함수
void Preempt(int flag)
{	
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// 초기화
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// 프로세스 큐 복사 함수
	Copyqueue(&node, &node_head, &node_tail);

	while(exit_num < process_num)
	{
		node = node_head;

		while(node != NULL && node -> arrive == time )
		{
			// temp 동적할당
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp 프로세스 복사
			Copynode(node, temp);
			// 실행되는 프로세스에 temp 적용
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
		// 현재 작업중인 프로세스를 출력하는 함수
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 초 단위
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 초 단위");
	// flag에 따라 스케줄링을 선택하는 함수
	printf("\n\t 간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}

// 라운드 로빈 스케줄링 개념 구현 
void R_Rpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, timequantum = 0, exit_num = 0;
	// 초기화
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// 프로세스 큐 복사 함수
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
				// temp 동적할당
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				// temp 프로세스 복사
				Copynode(ready_head, temp);
				// 실행되는 프로세스에 temp 적용
				Add_Queue(temp, &ready_head, &ready_tail);
				ready_head = ready_head->next;

			}
			else if(cpu == -2)
			{
				Result_add(flag, &ready_head); // flag에 따라 스케줄링을 선택
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
		// 현재 작업중인 프로세스를 출력하는 함수
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 초 단위
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 초 단위");
	// flag에 따라 스케줄링을 선택하는 함수
	printf("\n\t 간트차트 길이 : %d\n",time);
	Result_add(flag, &ready_head);
}



void bubble_sort(process arr[], int count)    // 매개변수로 정렬할 배열과 요소의 개수를 받음
{
	int i,j;
    process temp;

    for (i = 1; i <= count; i++)    // 요소의 개수만큼 반복
    {
        for (j = 1; j <= count - 1; j++)   // 요소의 개수 - 1만큼 반복
        {
			if (arr[j].arrive> arr[j + 1].arrive)          // 현재 요소의 값과 다음 요소의 값을 비교하여
            {                                 // 큰 값을
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;            // 다음 요소로 보냄
            }
        }
    }
}