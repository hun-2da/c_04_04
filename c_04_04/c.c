#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int* stack_m;
	int top;
	int capacity;
}element;
int is_empty(element* e) {
	return (e->top == -1);
}
int is_full(element* e) {
	return (e->top == (e->capacity - 1));
}
void push(element* e, int item) {
	if (is_full(e)) {
		//fprintf(stderr, "stack full\n");
		e->capacity = e->capacity * 2;
		e->stack_m = realloc(e->stack_m, e->capacity * sizeof(int));
		return;
	}
	else e->stack_m[++e->top] = item;
}
int pop(element* e) {
	if (is_empty(e)) {
		fprintf(stderr, "피연산자가 부족합니다. \n");
		exit(1);
	}
	else return e->stack_m[e->top--];
}
int eval(element *e,char exp[]) {
	int op1, op2,value;
	int len = strlen(exp);
	
	e ->top = -1;
	
	for (int i = 0; i < len; i++) {
		int op = 0;
		char ch = exp[i];
		if ('0' <= ch && ch <= '9') /*ch가 숫자일 경우*/ {
			value = ch - '0';
			push(e, value);
			printf("push : %d\n", value);
		}else /*숫자가 아닐경우*/ {
			if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
				fprintf(stderr, "잘못된 입력값이 포함되어 있습니다.\n");
				exit(1);
			}
			op2 = pop(e);
			op1 = pop(e);

			printf("%d\t%d\t\t%c\n", op1, op2, ch);

			switch (ch) {
			case '+': op = op1 + op2; break;
			case '-': op = op1 - op2; break;
			case '*': op = op1 * op2; break;
			case '/': op = op1 / op2; break;
			}
			push(e, op);
			printf("push : %d\n", op);
		}
	}
	if (e->top != 0) {
		for(;e->top > 0;)
			fprintf(stderr,"연산자가 부족하여 피연산자 %d 값이 남습니다.\n",pop(e));
	}
	return pop(e);
}
void main() {
	printf("값을 입력해주십시오 : ");
	//char input_array[100];
	//scanf_s("%s", input_array,100);
	int n = 100;
	char* input_array = malloc(n*sizeof(char));
	if (input_array == NULL) {
		fprintf(stderr, "입력 문자 저장공간이 NULL");
		return;
	}
	scanf_s("%s", input_array,n);

	element* s_s = malloc(sizeof(element));
	if (s_s == NULL ) {
		fprintf(stderr, "구조체가 NULL");
		return;
	}
	s_s -> capacity = 10;
	s_s -> stack_m = malloc(s_s->capacity * sizeof(int));
	if (s_s->stack_m == NULL) {
		fprintf(stderr, "스택이 NULL");
		return;
	}
	int result = eval(s_s,input_array);

	printf("결과 값은 %d \n", result);

	free(s_s->stack_m);
	free(s_s);
	free(input_array);

	system("pause");
}
