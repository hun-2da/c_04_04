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
		fprintf(stderr, "stack full\n");
		e->capacity = e->capacity * 2;
		e->stack_m = realloc(e->stack_m, e->capacity * sizeof(int));
		return;
	}
	else e->stack_m[++e->top] = item;
}
int pop(element* e) {
	if (is_empty(e)) {
		fprintf(stderr, "stack empty\n");
		return -1;
	}
	else return e->stack_m[e->top--];
}
int eval(element *e,char exp[]) {

	int op1, op2;
	
	int len = strlen(exp);
	char ch = NULL; 
	int value;
	
	e ->top = -1;
	
	for (int i = 0; i < len; i++) {
		if (ch >= '0' && ch <= '9') {
			value = ch - '0';
			push(e, value);
		}
		else {
			op2 = pop(e);
			op1 = pop(e);

			switch (ch) {
			case '+': push(e, op2 + op1); break;
			case '-': push(e, op2 - op1); break;
			case '*': push(e, op2 * op1); break;
			case '/': push(e, op2 / op1); break;
			default:
				printf(" 숫자가 아닌 다른 문자\n잘못된 입력값을 입력하였습니다.\n");
			}
		}
	}
	return pop(e);

}
int main() {
	printf("값을 입력해주십시오 : ");
	char s[200] = {0};
	scanf_s("%s\n", &s);

	element* m = malloc(sizeof(element));
	//m->top = -1;
	m->capacity = 10;
	m->stack_m = malloc(m->capacity * sizeof(int));

	int result;
	result = eval(m,s);
	//e = m;
	printf("결과 값은 %d \n", result);

	free(m->stack_m);
	free(m);

	system("pause");
}