#include <stdio.h>
#include <stdlib.h>

struct CircularQueueStruct{
	int* key;
	int front;
	int rear;
	int size;
	int max_queue_size;
};

typedef struct CircularQueueStruct* CircularQueue;

CircularQueue MakeEmpty(int max);
int IsEmpty(CircularQueue Q);
int IsFull(CircularQueue Q);
void Dequeue(CircularQueue Q);
void Enqueue(CircularQueue Q, int x);
void PrintFirst(CircularQueue Q);
void PrintRear(CircularQueue Q);
void DeleteQueue(CircularQueue Q);

int main(int argc, char* argv[]){
	char command;
	FILE* input;
	CircularQueue queue;
	int queueSize;
	int tmpNum;

	input = fopen(argv[1], "r");

	while(1){
		command = fgetc(input);
		if(feof(input)) break;
		switch(command){
			case 'n':
				fscanf(input, "%d", &queueSize);
				queue = MakeEmpty(queueSize);
				break;
			case 'e':
				fscanf(input, "%d", &tmpNum);
				Enqueue(queue, tmpNum);
				break;
			case 'd':
				Dequeue(queue);
				break;
			case 'f':
				PrintFirst(queue);
				break;
			case 'r':
				PrintRear(queue);
				break;
			default:
				break;
		}
	}
	DeleteQueue(queue);
}

CircularQueue MakeEmpty(int max){
	CircularQueue q = (CircularQueue)malloc(sizeof(struct CircularQueueStruct));
	q->max_queue_size = max;
	q->key = (int*)malloc(max*sizeof(int));
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	return q;
}

int IsEmpty(CircularQueue Q){
	if(Q->size == 0) return 1;
	return 0;
}

int IsFull(CircularQueue Q){
	if(Q->size == Q->max_queue_size) return 1;
	return 0;	
}

void Dequeue(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Dequeue failed : Queue is Empty!\n");
		return;
	}
	Q->front %= Q->max_queue_size;
	printf("Dequeue %d\n", Q->key[Q->front++]);
	Q->size--;
}

void Enqueue(CircularQueue Q, int x){
	if(IsFull(Q)){
		printf("Enqueue failed : Queue is Full!\n");
		return;
	}
	Q->rear %= Q->max_queue_size;
	Q->key[++Q->rear] = x;
	printf("Enqueue %d\n", x);
	Q->size++;
}

void PrintFirst(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Queue is Empty!\n");
		return;
	}
	printf("Element in the front : %d\n", Q->key[Q->front]);
}

void PrintRear(CircularQueue Q){
	if(IsEmpty(Q)){
		printf("Queue is Empty!\n");
		return;
	}
	printf("Element in the rear : %d\n", Q->key[Q->rear]);
}

void DeleteQueue(CircularQueue Q){
	free(Q->key);
	free(Q);
}
