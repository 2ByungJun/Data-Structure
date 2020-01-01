#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100     // MAX값을 100으로 정의

int stack[MAX];     // 스택
int top;            // 스택의 상단

// 스택 초기화
void init_stack(void)
{
    top = -1;
}
// 스택이 비어있는지 검사
int is_stack_empty(void)
{
    return (top < 0);
}
// 스택 Push
int push(int t)
{
    if (top >= MAX - 1){ // 스택의 상단이 MAX치를 넘어갈 시(허용초과)
        printf("스택 허용 초과\n");
        return -1;
    }
    stack[++top] = t; // 스택배열의[++top]으로 올려주어 t값을 대입(push)
    return t;         // 값 리턴 
}
// 스택 Pop
int pop()
{
    if (top < 0){ // 스택의 상단이 0보다 밑일 경우(비어있음)
        printf("스택이 비어있음.\n");
        return 0;
    }
    return stack[top--]; // 스택상단 데이터를 리턴하며 top--으로 한칸 내려짐(pop)
}
// 스택 Peek
int get_stack_top(void)
{
    return (top < 0) ? -1 : stack[top]; // 스택의 TOP의 값을 리턴
}
// k 가 연산자인지 판단한다.
int is_operator(int k)
{
    return (k == '+' || k == '-' || k == '*' || k == '/');
}
// 연산자의 우선순위를 수치로 변환해준다.
int precedence(int op)
{
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}
// 중위표기법을 후위표기법으로 변환
// dst : 후위표기식으로 copy할 문자열
// src : 중위표기식 문자열
void postfix(char *dst, char *src)
{    
    init_stack(); // 스택초기화

    while (*src)
	{
        if (*src == '('){ // '(' 일경우
            push(*src);   // src에 푸시
            src++;        // 다음으로
        }
        else if (*src == ')'){ // ')' 일경우
            while (get_stack_top() != '('){ // 스택에서 '('가 나올때까지
                *dst++ = pop(); // dst에 pop한 후 증가
				*dst++ = ' ';
			}
            pop(); // pop
            src++; // src증가
        }
        else if (is_operator(*src)){ // src가 연산자일 경우
			// 스택이 공백이 아닐경우 && 연산자 우선순위 비교( 스택상단 >= src연산자 우선순위 )
            while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src)){
                *dst++ = pop(); // dst증가 후 pop()<<src를
				*dst++ = ' ';
			}
            push(*src); // src에 푸시
            src++;      // src증가
        }
        else if (*src >= '0' && *src <= '9'){ // src가 숫자일 경우
            do{
                *dst++ = *src++; // dst에 그대로 src의 숫자를 대입
            } while (*src >= '0' && *src <= '9'); // 숫자일 경우만
			*dst++ = ' ';
        }
        else{
            src++;
        }
    }

    while (!is_stack_empty()){ // 스택이 비어있을 경우
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;    // dst감소
    *dst = 0; // dst초기화
}

// 후위표기법 수식이 적접한가 체크
int is_legal(char *s)
{
    int f = 0;

    while (*s){
        // 처음 공백 넘어가기(후위표기식 공백-가독성을 위함)
        while (*s == ' '){
            s++;
        }

        if (is_operator(*s)){ // s가 연산자일 경우
            f--;
        }
        else{
            f++;
            while (*s != ' '){
                s++;
            }
        }
        if (f < 1) break;
        s++;
    }
    return (f == 1);
}

// 후위표기법을 계산한다.
int calc(char *p)
{
    int i;

    init_stack(); // 스택초기화

    while (*p){
        if (*p >= '0' && *p <= '9'){ // 숫자일 경우
            i = 0; // i값 초기화
            do{
                i = i * 10 + *p - '0'; // i값 누적(10의 자리수) + *p(1의 자리수)
                p++;
            } while (*p >= '0' && *p <= '9');
            push(i); // i를 푸시(연산결과값)
        }
		// 사칙연산
        else if (*p == '+'){
            push(pop() + pop()); // pop을 이용해 결과값을 push
            p++; // 다음p값을 위한 증가
        }
        else if (*p == '*'){
            push(pop() * pop());
            p++;
        }
        else if (*p == '-'){
            i = pop();
            push(pop() - i);
            p++;
        }
        else if (*p == '/'){
            i = pop();
            push(pop() / i);
            p++;
        }
        else{
            p++;  // p값증가로 이동
        }
    }
    return pop(); // 결과값 리턴
}

int main()
{
    int value,count=0;  // 결과값,파일데이터 수
    char exp[256];      // 중위표기식
    char copy[256];     // 후위표기식
	// data1.txt파일 읽기형식으로 오픈
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL) // 에러시
	{
		printf("파일 에러\n");
		exit(1);
	}
	// 파일 데이터 수를 체크
	while(!feof(fp)){
		fscanf(fp,"%s",&copy);
		count++;
	}
	// 파일포인터 초기화
	rewind(fp);
	// display ( 파일 데이터 수만큼 반복 )
	do{
		// 파일 포인터가 도달할때까지
		while(!feof(fp)) 
		{
			fscanf(fp,"%s",exp); // 문자열을 exp에 읽어오기

			postfix(copy, exp); // 전위표기식(exp)->후위표기식(copy)로 변경
			printf("후위표기식 : %s\n", copy);

			if (!is_legal(copy)){ // copy(후위표기식)의 수식판단
				printf("잘못된 수식입니다.\n");
				continue;
			}

			printf("중위표기식 : %s\n", exp);

			value = calc(copy); // 후위표기식 연산결과를 value에 대입
			printf("결      과 : %d\n\n", value);
		}
		count--; // 카운팅 ( 데이터수만큼 반복할때마다 하나씩 감소 )

	}while(count==0);

	fclose(fp); // 파일을 닫아준다
	return 0;   
}