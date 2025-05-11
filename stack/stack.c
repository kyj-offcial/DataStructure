#include <stdio.h>
#include <stdlib.h>

typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;

Stack* CreateStack(int max);
void Push(Stack* s, int x);
int Pop(Stack* s);
int Top(Stack* s);
void DeleteStack(Stack* s);
int IsEmpty(Stack* s);
int IsFull(Stack* s);
void Postfix(Stack* s, char input_str);

int main(int argc, char *argv[]){
	if(argc==1){
		printf("Please enter an inupt file.");
		return 0;
	}
	FILE* fi = fopen(argv[1], "r");

	Stack* stack = CreateStack(10);

	char c;
	printf("Top numbers: ");
	while(1){
		fscanf(fi, "%c", &c);
		if(c == '!'){
			printf("\nCalculating Done!");
			break;
		}
		Postfix(stack, c);
		printf("%d ", Top(stack));
	}
	printf("\n");
	printf("evaluation result: %d\n", Pop(stack));

	fclose(fi);
	DeleteStack(stack);
}

Stack* CreateStack(int max){
	Stack* s = (Stack*)malloc(sizeof(Stack));
	
	s->key = (int*)malloc(sizeof(int)*max);
	s->max_stack_size = max;
	s->top = -1;
	return s;
}
void Push(Stack* s, int x){
	if(IsFull(s)){
		printf("\nStack overflow!");
		exit(1);
	}
	else s->key[++s->top] = x;
}
int Pop(Stack* s){
	if(IsEmpty(s)){
		printf("\nStack underflow!");
		exit(1);
	}
	else return s->key[s->top--];
}
int Top(Stack* s){
	if(IsEmpty(s)){
		printf("\nStack underflow!");
		exit(1);
	}
	else return s->key[s->top];
}

void DeleteStack(Stack* s){
	if(s == NULL) return;
	free(s->key);
	free(s);
}

int IsEmpty(Stack* s){
	if(s->top == -1) return 1;
	return 0;
}

int IsFull(Stack* s){
	if(s->top == s->max_stack_size-1) return 1;
	return 0;
}

void Postfix(Stack* s, char input_str){
	if(input_str - '0' >= 0 && input_str - '0' < 10){
		int num = input_str - '0';
		Push(s, num);
	}
	else{
		if(IsFull(s)){
			printf("\nStack overflow!");
			exit(1);
		}
		if(s->top < 1){
			printf("\nStack underflow!");
			exit(1);
		}
		int num2 = Pop(s);
		int num1 = Pop(s);
		int x;
		switch(input_str){
			case '+':
				x = num1 + num2;
				Push(s, x);
				break;
			case '-':
				x = num1 - num2;
				Push(s, x);
				break;
			case '*':
				x = num1 * num2;
				Push(s, x);
				break;
			case '/':
				x = num1 / num2;
				Push(s, x);
				break;
			case '%':
				x = num1 % num2;
				Push(s, x);
				break;
			default:
				printf("\nInvalid operator!");
				exit(1);
		}
	}
}
