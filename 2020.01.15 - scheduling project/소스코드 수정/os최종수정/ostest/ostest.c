#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#define MAX_que 100
#define CPU_time 100
#define SWAP(x,y,t) ( (t)=(x), (x)=(y), (y)=(t) )

typedef struct process process_pointer;
/* Щ煎撮蝶曖 掘撩 蹂模 掘褻羹 */
typedef struct process {
	process_pointer *next;	
	int pid;         // Щ煎撮蝶 廓��
	char prcID2[10]; // Щ煎撮蝶 ID
	int burst_time;  // 褒ч 衛除
	int priority;    // 辦摹牖嬪
	int arrive;      // 紫雜衛除
	int wait;	     // 渠晦衛除
	int turnaround;  // 奩�紗簸�
	int work;	     // 濛機榆
	int remain;      // 陴擎 熱ч衛除
	int HRN_priority;// HRN 辦摹牖嬪
} process;	

/* 陝 蝶馨鍰葭擊 嬪и Щ煎撮蝶 掘褻羹 摹樹 塽 ready_queue 摹樹 */
process_pointer *head = NULL, *tail = NULL,              // head, tail
	            *ready_head = NULL, *ready_tail = NULL,  // ready_queue
				*fcfs_h = NULL, *fcfs_t = NULL,          // FCFS
				*nosjf_h = NULL, *nosjf_t = NULL,        // SJF
				*psjf_h = NULL, *psjf_t = NULL,          // SRT
				*nopri_h = NULL, *nopri_t = NULL,        // Nonpreempt_Priority
				*ppri_h = NULL, *ppri_t = NULL,          // Preempt_Priority
				*rr_h = NULL, *rr_t = NULL;              // R_R

// л熱 摹樹睡
void Menu();	// 詭景 轎溘 л熱
void Scheduler_Selection(int select); // 錳ж朝 CPU 蝶馨鍰葭 摹鷗 л熱
void Make_Process();   // Щ煎撮蝶 儅撩 л熱
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t); // ready_queue縑 Щ煎撮蝶蒂 蹺陛ж朝 л熱
void Process_Output(process_pointer **temp); // 儅撩脹 Щ煎撮蝶蒂 轎溘ж朝 л熱
void State_Result_Out(int time, process_pointer **ready_head, process_pointer **node_head, int flag); // ⑷營 濛機醞檣 Щ煎撮蝶蒂 轎溘ж朝 л熱
void Process_Result_Output(process_pointer **temp); // 蝶馨鍰葭 �釋� Щ煎撮蝶 鼻鷓蒂 轎溘ж朝 л熱
void Sort(process_pointer **h, process_pointer **t, int algorithm); // 憲堅葬闈縑 評艇 Щ煎撮蝶曖 霞殮 牖憮 薑溺
void Copynode(process_pointer *h, process_pointer *temp); // Щ煎撮蝶 犒餌 л熱
void Copyqueue(process_pointer **node, process_pointer **node_head, process_pointer **node_tail); // Щ煎撮蝶 聽 犒餌 л熱
void Result_add(int falg, process_pointer **ready_head); // flag縑 評塭 蝶馨還葭擊 摹鷗ж朝 л熱
void Process_Result_Output_HRN(process_pointer **temp);  // HRN Щ煎撮蝶曖 鼻鷓蒂 轎溘ж朝 л熱

void Nonpreempt(int flag);		// 綠 摹薄 蝶馨還葭 偃喃 掘⑷
void Preempt(int flag);			// 摹薄 蝶馨還葭 偃喃 掘⑷
void R_Rpreempt(int flag);		// 塭遴萄 煎綴 蝶馨還葭 偃喃 掘⑷ 
void FCFS();					// FCFS
void SJF();						// SJF
void SRT();						// SRT 
void Nonpreempt_Priority();		// 綠摹薄 Priorty
void Preempt_Priority();		// 摹薄 Priorty
void R_R();						// Round-Robin
void HRN();						// HRN

void bubble_sort(process arr[], int count);	// 薑溺


int process_num = 0; // Щ煎撮蝶 偎熱
int quantum;	     // 衛除 й渡榆


// 詭檣 л熱
main()
{
	Menu();
}	

// 詭景 л熱
void Menu()
{
	int select = 0;
	printf("\n\t <蝶馨還葭 衛嘆溯檜攪 by. 寥煽瞪>\n");
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
	printf("\t弛  0  ⊥  Щ煎撮蝶 儅撩\t\t弛\n");
	printf("\t弛  1  ⊥  FCFS\t\t\t弛\n");
	printf("\t弛  2  ⊥  SJF\t\t\t弛\n");
	printf("\t弛  3  ⊥  SRT\t\t\t弛\n");
	printf("\t弛  4  ⊥  綠摹薄 Priority\t弛\n");
	printf("\t弛  5  ⊥  摹薄 Priority\t\t弛\n");
	printf("\t弛  6  ⊥  Round-Robin\t\t弛\n");
	printf("\t弛  7  ⊥  HRN\t\t\t弛\n");
	printf("\t弛  8  ⊥  衛嘆溯檜攪 謙猿\t弛\n");
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\n\t Ⅰ 錳ж朝 濛機擊 摹鷗ж撮蹂 : ");	
	scanf("%d", &select);
	Scheduler_Selection(select); // CPU 蝶馨鍰楝 Щ煎斜極 褒ч
}

// CPU 蝶馨還楝 Щ煎斜極 褒ч л熱
void Scheduler_Selection(int select) 
{
	if(select != 0 && select != 8 && head == NULL)
	{
		printf("\n\tЩ煎撮蝶蒂 儅撩ж撮蹂.\n\n");
		Menu();
	}
	
	switch(select)
	{
		case 0: Make_Process();			// Щ煎撮蝶 儅撩
			break;
		case 1: FCFS();					// FCFS
			break;
		case 2: SJF();					// SJF
			break;
		case 3: SRT();					// SRT
			break;		
		case 4: Nonpreempt_Priority();	// 綠摹薄 Priorty
			break;
		case 5: Preempt_Priority();		// 摹薄 Priorty
			break;
		case 6: R_R();					// Round-Robin
			break;
		case 7 : HRN();					// HRN
			break;
		case 8 : printf("\n\t衛嘆溯檜攪蒂 謙猿м棲棻.\n\n\t");
			exit(0);				    // 謙猿
	}
}

// Щ煎撮蝶 儅撩 л熱
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
	process data[MAX_que];		// 等檜攪蒂 盪濰й 掘褻羹
	FILE *fp = fopen("data.txt", "r");

	process_pointer *temp;
	head = NULL, tail = NULL;

	seed = time(NULL);
    srand(seed);
	// Щ煎撮蝶 儅撩
	// Щ煎撮蝶 偎熱 殮溘
	printf("\n\tЩ煎撮蝶 偃熱(100偃 檜ж) : ");
	fscanf(fp, "%d", &process_num);
	printf("%d", process_num);
	
	// Щ煎撮蝶 偎熱陛 譆渠 偎熱 蟾婁衛, Щ煎斜極 謙猿
	while(process_num > MAX_que)
	{
		printf("Щ煎撮蝶陛 譆渠 偎熱蒂 剩歷蝗棲棻!\n");
		exit(1);
	}
	printf("\n");
	for(i = 1; i <= process_num; i++) 
	{	
		printf("\tProcess %d \n",i);
		fscanf(fp, "%s %d %d %d", prcID, &CPU_TIME_VALUE,&CPU_TIME_VALUE2,&PROCESS_NUM_VALUE);
		printf("\n\tЩ煎撮蝶 ID : %s\n\t紫雜 衛除 : %d \n\t褒ч 衛除 : %d\n\t辦摹 牖嬪 : %d\n\n", prcID, CPU_TIME_VALUE,CPU_TIME_VALUE2,PROCESS_NUM_VALUE);
		data[i].arrive = CPU_TIME_VALUE;		// 紫雜衛除
		data[i].burst_time = CPU_TIME_VALUE2;	// 褒ч衛除
		data[i].priority = PROCESS_NUM_VALUE;	// 辦摹牖嬪
		data[i].pid = i;
		strcpy(data[i].prcID2, prcID);
	}
		
	bubble_sort(data,process_num);


	// Щ煎撮蝶 等檜攪 蟾晦��
	printf("\n");
	printf("\t* 殮溘嫡擎 Щ煎撮蝶ID, 紫雜衛除, 褒ч衛除, 辦摹牖嬪 *\n");
	for(i = 1; i <= process_num; i++) 
	{
		if(max<data[i].burst_time)
			max=data[i].burst_time;
		tmp2[i-1]=data[i].arrive;		// 紫雜 衛除
		tmp1[i-1]=data[i].burst_time;	// 褒ч衛除
		tmp3[i-1]=data[i].priority;		// 辦摹 牖嬪
		
		temp = (process_pointer *)malloc(sizeof(process_pointer)); 
		temp -> pid = data[i].pid;
		strcpy(temp -> prcID2, data[i].prcID2);
		temp -> burst_time = tmp1[i-1];	// 褒ч衛除 鳶殮
		

		temp -> arrive = tmp2[i-1];		// 紫雜 衛除 鳶殮
		temp -> priority = tmp3[i-1];	// 辦摹 牖嬪 鳶殮
		temp -> wait = 0;		
		temp -> turnaround = 0;	
		temp -> work = 0;	
		temp -> remain = temp -> burst_time;	

		temp -> next = NULL;

		hrn_pri=((max-tmp2[i-1])+tmp1[i-1]) / tmp1[i-1];	// 紫雜衛除 啗骯

		temp -> HRN_priority=hrn_pri;


		Add_Queue(temp, &head, &tail); 
	}
	// 衛除й渡榆 蟾晦��
	fscanf(fp, "%d", &quantum);
	printf("\t衛除 й渡榆 : %d\n\n", quantum);

	temp = head; // temp蒂 head煎 蟾晦��
	Process_Output(&temp); // Щ煎撮蝶 儅撩 轎溘
	temp = head; // temp蒂 head煎 蟾晦��
	Menu();      // 詭景 л熱
}

// Щ煎撮蝶蒂 聽縑 鳶殮
void Add_Queue(process_pointer *temp, process_pointer **h, process_pointer **t)
{	
	if(*h != NULL ) (*t)->next = temp; 	
	else *h = temp; 	
	*t = temp;
}

// flag縑 評塭 蝶馨還葭擊 摹鷗ж朝 л熱 
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
		default: printf("縑楝"); // 謙猿
				exit(0);
	}
}

// ル 儅撩
void Process_Output(process_pointer **temp) 
{
	printf("\n\n");
	printf("\t<儅撩脹 Щ煎撮蝶>\n");
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛 ID  褒ч衛除  紫雜衛除  辦摹牖嬪  渠晦衛除   濛機榆   陴擎榆   擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	// 等檜攪 轎溘僥
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t弛 %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    弛\n",(*temp) -> prcID2, (*temp) -> burst_time, 
			(*temp) -> arrive, (*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
}

// ⑷營 濛機醞檣 Щ煎撮蝶蒂 轎溘ж朝 л熱
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

// 蝶馨鍰葭 �釋� Щ煎撮蝶 鼻鷓蒂 轎溘ж朝 л熱
void Process_Result_Output(process_pointer **temp)
{
	printf("\n");
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛 ID  褒ч衛除  紫雜衛除  辦摹牖嬪  渠晦衛除   濛機榆   陴擎榆   擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	// 等檜攪 轎溘僥
	for(;*temp != NULL; *temp = (*temp) -> next)
	{
		printf("\t弛 %s  %4d  %8d  %8d  %8d  %8d  %7d  %8d    弛\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
			(*temp) -> priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
		
	}
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");

}

// HRN Щ煎撮蝶曖 鼻鷓蒂 轎溘ж朝 л熱
void Process_Result_Output_HRN(process_pointer **temp)
{
	printf("\n");
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛 ID  褒ч衛除  紫雜衛除  辦摹牖嬪  渠晦衛除   濛機榆   陴擎榆   擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(;*temp != NULL; *temp = (*temp) -> next)
		printf("\t弛 %2s  %6d  %7d    %5d  %8d  %8d  %7d  %8d    弛\n",(*temp) -> prcID2, (*temp) -> burst_time, (*temp) -> arrive, 
		(*temp) ->HRN_priority, (*temp) -> wait, (*temp) -> work, (*temp) -> remain, ( (*temp) -> wait+(*temp) -> burst_time)/(*temp) -> burst_time);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
	printf("\n");
}

// Щ煎撮蝶 犒餌 л熱
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

// Щ煎撮蝶 聽 犒餌 л熱
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

// 憲堅葬闈縑 評艇 Щ煎撮蝶曖 霞殮 牖憮 薑溺
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

	// 蟾晦��
	fcfs_h = NULL, fcfs_t = NULL;
	printf("\n\t");
	Nonpreempt(1); // 綠 摹薄 蝶馨還葭 偃喃 掘⑷ 'FCFS'

	// FCFS Щ煎撮蝶 唸婁ル 轎溘
	temp = fcfs_h;
	printf("\n\n\t<FCFS 蝶馨還葭>");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯 
	temp = fcfs_h;
	aver_wait = 0, aver_turn = 0, aver_answer = 0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; fcfs_h; fcfs_h = fcfs_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",fcfs_h->prcID2,fcfs_h->wait,fcfs_h->turnaround,(fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time);
		aver_wait += fcfs_h->wait;
		aver_turn += fcfs_h->turnaround;
		aver_answer += (fcfs_h->wait+fcfs_h->burst_time)/fcfs_h->burst_time;
	}

	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// SJF
void SJF()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 蟾晦��
	nosjf_h = NULL, nosjf_t = NULL;
	printf("\n\t");
	Nonpreempt(2);// 綠 摹薄 蝶馨還葭 偃喃 掘⑷ 'SJF'

	// SJF Щ煎撮蝶 唸婁ル 轎溘
	temp = nosjf_h;
	printf("\n\n\t<SJF 蝶馨還葭>");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
	temp = nosjf_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; nosjf_h; nosjf_h = nosjf_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",nosjf_h->prcID2,nosjf_h->wait,nosjf_h->turnaround,(nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time);
		aver_wait += nosjf_h->wait;
		aver_turn += nosjf_h->turnaround;
		aver_answer += (nosjf_h->wait+nosjf_h->burst_time)/nosjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// SRT
void SRT()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 蟾晦��
	psjf_h = NULL, psjf_t = NULL;
	printf("\n\t");
	Preempt(3); // 摹薄 蝶馨還葭 偃喃 掘⑷ 'SRT'

	// SRT Щ煎撮蝶 唸婁ル 轎溘
	temp = psjf_h;
	printf("\n\n\t<SRT 蝶馨還葭>");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
    temp = psjf_h;
    aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; psjf_h; psjf_h = psjf_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",psjf_h->prcID2,psjf_h->wait,psjf_h->turnaround,(psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time);
		aver_wait += psjf_h->wait;
		aver_turn += psjf_h->turnaround;
		aver_answer += (psjf_h->wait+psjf_h->burst_time)/psjf_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// Nonpreempt_Priority
void Nonpreempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0,aver_answer = 0;

	// 蟾晦��
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(4); // 綠摹薄 蝶馨還葭 偃喃 掘⑷ 'Nonpreempt_Priority'

	// 綠摹薄 Priority Щ煎撮蝶 唸婁ル 轎溘
	temp = nopri_h;
	printf("\n\n\t<綠摹薄 Priority 蝶馨還葭>");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
	printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// Preempt_Priority
void Preempt_Priority()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 蟾晦��
	ppri_h = NULL, ppri_t = NULL;
	printf("\n\t");
	Preempt(5); // 摹薄 蝶馨還葭 偃喃 掘⑷ 'Preempt_Priority'

	// 摹薄 Priority Щ煎撮蝶 唸婁ル 轎溘
	temp = ppri_h;
	printf("\n\n\t<摹薄 Priority 蝶馨還葭>");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
	temp = ppri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; ppri_h; ppri_h = ppri_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",ppri_h->prcID2,ppri_h->wait,ppri_h->turnaround,(ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time);
		aver_wait += ppri_h->wait;
		aver_turn += ppri_h->turnaround;
		aver_answer += (ppri_h->wait+ppri_h->burst_time)/ppri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// R_R
void R_R()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 蟾晦��
	rr_h = NULL, rr_t = NULL;

	// 除問 轎溘
	printf("\t TQ 除問 殮溘 : ");
	printf("%d", quantum);
	printf("\n\t");
	R_Rpreempt(6); // R_R 蝶馨還葭 偃喃 掘⑷ 'R_R'

	// R_R Щ煎撮蝶 唸婁ル 轎溘
	temp = rr_h;
	printf("\n\n\tRound-Robin 蝶馨還葭");
	Process_Result_Output(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
	temp = rr_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; rr_h; rr_h = rr_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",rr_h->prcID2,rr_h->wait,rr_h->turnaround,(rr_h->wait+rr_h->burst_time)/rr_h->burst_time);
		aver_wait += rr_h->wait;
		aver_turn += rr_h->turnaround;
		aver_answer += (rr_h->wait+rr_h->burst_time)/rr_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	printf("\n");
	Menu();
}

// HRN
void HRN()
{
	process_pointer *temp;
	float aver_wait = 0, aver_turn = 0, aver_answer = 0;

	// 蟾晦��
	nopri_h = NULL, nopri_t = NULL;
	printf("\n\t");
	Nonpreempt(7); // 綠摹薄 蝶馨還葭 偃喃 掘⑷ 'HRN'

	// HRN Щ煎撮蝶 唸婁ル 轎溘
	temp = nopri_h;
	printf("\n\n\t<HRN 蝶馨還葭>");
	Process_Result_Output_HRN(&temp);

	// ゎ敕 渠晦 衛除,ゎ敕 奩�� 衛除 啗骯
	temp = nopri_h;
	aver_wait = 0, aver_turn = 0, aver_answer=0;
	printf("\t忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
	printf("\t弛  ID     渠晦衛除  奩�紗簸�  擬港衛除弛\n");
	printf("\t戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣 \n");
	for(; nopri_h; nopri_h = nopri_h->next)
	{
		printf("\t弛  %2s    %7d  %7d   %7d   弛\n",nopri_h->prcID2,nopri_h->wait,nopri_h->turnaround,(nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time);
		aver_wait += nopri_h->wait;
		aver_turn += nopri_h->turnaround;
		aver_answer += (nopri_h->wait+nopri_h->burst_time)/nopri_h->burst_time;
	}
	aver_wait /= process_num;
	aver_turn /= process_num;
	aver_answer /= process_num;
		printf("\t弛  ゎ敕  %7.3f   %7.3f   %7.3f  弛\n", 
	aver_wait, aver_turn, aver_answer);
	printf("\t戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎  \n");
	Menu();
}

// 綠摹薄 啗骯 л熱
void Nonpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// 蟾晦��
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// Щ煎撮蝶 聽 犒餌 л熱
	Copyqueue(&node, &node_head, &node_tail); 
	
	while(exit_num < process_num)
	{
		node = node_head; // node ④萄 蟾晦��

		// 喻萄陛 紫雜й 唳辦
		while(node != NULL && node -> arrive == time )
		{
			// temp 翕瞳й渡
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp Щ煎撮蝶 犒餌
			Copynode(node, temp);
			// 褒ч腎朝 Щ煎撮蝶縑 temp 瞳辨
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
		// ready 喻萄 蟾晦��
		ready_node = ready_head;

		// ready_node 奩犒
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
		// ⑷營 濛機醞檣 Щ煎撮蝶蒂 轎溘ж朝 л熱
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 蟾 欽嬪
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 蟾 欽嬪");
	// flag縑 評塭 蝶馨還葭擊 摹鷗ж朝 л熱
	printf("\n\t 除お離お 望檜 : %d\n",time);
	Result_add(flag, &ready_head);
}

// 摹薄 啗骯 л熱
void Preempt(int flag)
{	
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, exit_num = 0;
	// 蟾晦��
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// Щ煎撮蝶 聽 犒餌 л熱
	Copyqueue(&node, &node_head, &node_tail);

	while(exit_num < process_num)
	{
		node = node_head;

		while(node != NULL && node -> arrive == time )
		{
			// temp 翕瞳й渡
			temp = (process_pointer *)malloc(sizeof(process_pointer));
			// temp Щ煎撮蝶 犒餌
			Copynode(node, temp);
			// 褒ч腎朝 Щ煎撮蝶縑 temp 瞳辨
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
		// ⑷營 濛機醞檣 Щ煎撮蝶蒂 轎溘ж朝 л熱
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 蟾 欽嬪
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 蟾 欽嬪");
	// flag縑 評塭 蝶馨還葭擊 摹鷗ж朝 л熱
	printf("\n\t 除お離お 望檜 : %d\n",time);
	Result_add(flag, &ready_head);
}

// 塭遴萄 煎綴 蝶馨還葭 偃喃 掘⑷ 
void R_Rpreempt(int flag)
{
	process_pointer *node_head = NULL, *node_tail = NULL, *node, *ready_node, *temp;
	int i;
	int time =0, cpu = -1, timequantum = 0, exit_num = 0;
	// 蟾晦��
	ready_head = NULL, ready_tail = NULL;
	node = head; 

	// Щ煎撮蝶 聽 犒餌 л熱
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
				// temp 翕瞳й渡
				temp = (process_pointer *)malloc(sizeof(process_pointer));
				// temp Щ煎撮蝶 犒餌
				Copynode(ready_head, temp);
				// 褒ч腎朝 Щ煎撮蝶縑 temp 瞳辨
				Add_Queue(temp, &ready_head, &ready_tail);
				ready_head = ready_head->next;

			}
			else if(cpu == -2)
			{
				Result_add(flag, &ready_head); // flag縑 評塭 蝶馨還葭擊 摹鷗
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
		// ⑷營 濛機醞檣 Щ煎撮蝶蒂 轎溘ж朝 л熱
		State_Result_Out(time, &ready_head, &node_head, flag);

		time++;
	}
	// 蟾 欽嬪
	printf("\n\t ");
	for( i=0; i<time; i++)
	{  
		if ( i < 10)
			printf("%d   ",i);
		else if( i >= 10)
			printf("%d  ",i);
	}
	printf("<- 蟾 欽嬪");
	// flag縑 評塭 蝶馨還葭擊 摹鷗ж朝 л熱
	printf("\n\t 除お離お 望檜 : %d\n",time);
	Result_add(flag, &ready_head);
}



void bubble_sort(process arr[], int count)    // 衙偃滲熱煎 薑溺й 寡翮婁 蹂模曖 偃熱蒂 嫡擠
{
	int i,j;
    process temp;

    for (i = 1; i <= count; i++)    // 蹂模曖 偃熱虜躑 奩犒
    {
        for (j = 1; j <= count - 1; j++)   // 蹂模曖 偃熱 - 1虜躑 奩犒
        {
			if (arr[j].arrive> arr[j + 1].arrive)          // ⑷營 蹂模曖 高婁 棻擠 蹂模曖 高擊 綠掖ж罹
            {                                 // 贖 高擊
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;            // 棻擠 蹂模煎 爾鹵
            }
        }
    }
}