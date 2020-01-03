#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100     // MAX���� 100���� ����

int stack[MAX];     // ����
int top;            // ������ ���

// ���� �ʱ�ȭ
void init_stack(void)
{
    top = -1;
}
// ������ ����ִ��� �˻�
int is_stack_empty(void)
{
    return (top < 0);
}
// ���� Push
int push(int t)
{
    if (top >= MAX - 1){ // ������ ����� MAXġ�� �Ѿ ��(����ʰ�)
        printf("���� ��� �ʰ�\n");
        return -1;
    }
    stack[++top] = t; // ���ù迭��[++top]���� �÷��־� t���� ����(push)
    return t;         // �� ���� 
}
// ���� Pop
int pop()
{
    if (top < 0){ // ������ ����� 0���� ���� ���(�������)
        printf("������ �������.\n");
        return 0;
    }
    return stack[top--]; // ���û�� �����͸� �����ϸ� top--���� ��ĭ ������(pop)
}
// ���� Peek
int get_stack_top(void)
{
    return (top < 0) ? -1 : stack[top]; // ������ TOP�� ���� ����
}
// k �� ���������� �Ǵ��Ѵ�.
int is_operator(int k)
{
    return (k == '+' || k == '-' || k == '*' || k == '/');
}
// �������� �켱������ ��ġ�� ��ȯ���ش�.
int precedence(int op)
{
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    else return 3;
}
// ����ǥ����� ����ǥ������� ��ȯ
// dst : ����ǥ������� copy�� ���ڿ�
// src : ����ǥ��� ���ڿ�
void postfix(char *dst, char *src)
{    
    init_stack(); // �����ʱ�ȭ

    while (*src)
	{
        if (*src == '('){ // '(' �ϰ��
            push(*src);   // src�� Ǫ��
            src++;        // ��������
        }
        else if (*src == ')'){ // ')' �ϰ��
            while (get_stack_top() != '('){ // ���ÿ��� '('�� ���ö�����
                *dst++ = pop(); // dst�� pop�� �� ����
				*dst++ = ' ';
			}
            pop(); // pop
            src++; // src����
        }
        else if (is_operator(*src)){ // src�� �������� ���
			// ������ ������ �ƴҰ�� && ������ �켱���� ��( ���û�� >= src������ �켱���� )
            while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src)){
                *dst++ = pop(); // dst���� �� pop()<<src��
				*dst++ = ' ';
			}
            push(*src); // src�� Ǫ��
            src++;      // src����
        }
        else if (*src >= '0' && *src <= '9'){ // src�� ������ ���
            do{
                *dst++ = *src++; // dst�� �״�� src�� ���ڸ� ����
            } while (*src >= '0' && *src <= '9'); // ������ ��츸
			*dst++ = ' ';
        }
        else{
            src++;
        }
    }

    while (!is_stack_empty()){ // ������ ������� ���
        *dst++ = pop();
        *dst++ = ' ';
    }
    dst--;    // dst����
    *dst = 0; // dst�ʱ�ȭ
}

// ����ǥ��� ������ �����Ѱ� üũ
int is_legal(char *s)
{
    int f = 0;

    while (*s){
        // ó�� ���� �Ѿ��(����ǥ��� ����-�������� ����)
        while (*s == ' '){
            s++;
        }

        if (is_operator(*s)){ // s�� �������� ���
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

// ����ǥ����� ����Ѵ�.
int calc(char *p)
{
    int i;

    init_stack(); // �����ʱ�ȭ

    while (*p){
        if (*p >= '0' && *p <= '9'){ // ������ ���
            i = 0; // i�� �ʱ�ȭ
            do{
                i = i * 10 + *p - '0'; // i�� ����(10�� �ڸ���) + *p(1�� �ڸ���)
                p++;
            } while (*p >= '0' && *p <= '9');
            push(i); // i�� Ǫ��(��������)
        }
		// ��Ģ����
        else if (*p == '+'){
            push(pop() + pop()); // pop�� �̿��� ������� push
            p++; // ����p���� ���� ����
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
            p++;  // p�������� �̵�
        }
    }
    return pop(); // ����� ����
}

int main()
{
    int value,count=0;  // �����,���ϵ����� ��
    char exp[256];      // ����ǥ���
    char copy[256];     // ����ǥ���
	// data1.txt���� �б��������� ����
	FILE *fp = fopen("data1.txt","r");
	if(fp==NULL) // ������
	{
		printf("���� ����\n");
		exit(1);
	}
	// ���� ������ ���� üũ
	while(!feof(fp)){
		fscanf(fp,"%s",&copy);
		count++;
	}
	// ���������� �ʱ�ȭ
	rewind(fp);
	// display ( ���� ������ ����ŭ �ݺ� )
	do{
		// ���� �����Ͱ� �����Ҷ�����
		while(!feof(fp)) 
		{
			fscanf(fp,"%s",exp); // ���ڿ��� exp�� �о����

			postfix(copy, exp); // ����ǥ���(exp)->����ǥ���(copy)�� ����
			printf("����ǥ��� : %s\n", copy);

			if (!is_legal(copy)){ // copy(����ǥ���)�� �����Ǵ�
				printf("�߸��� �����Դϴ�.\n");
				continue;
			}

			printf("����ǥ��� : %s\n", exp);

			value = calc(copy); // ����ǥ��� �������� value�� ����
			printf("��      �� : %d\n\n", value);
		}
		count--; // ī���� ( �����ͼ���ŭ �ݺ��Ҷ����� �ϳ��� ���� )

	}while(count==0);

	fclose(fp); // ������ �ݾ��ش�
	return 0;   
}