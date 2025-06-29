#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue{
    int size;
    int *key;
    int front;
    int rear;
} Queue;

Queue *CreateQueue(int X);

void Enqueue(Queue *Q, int item);

int Dequeue(Queue* Q);

typedef struct _Graph{
    int size;
    int *vertex;
    int **edge;
} Graph;

Graph *CreateGraph(int X);

void InsertEdge(Graph *G, int u, int v);

void Topsort(Graph *G);

int main(int argc, char *argv[]){
    FILE *fi = fopen(argv[1], "r");
    int X, u, v;

    fscanf(fi, "%d", &X);

    Graph *G = CreateGraph(X);

    for(int i=0; i<X; i++){
        fscanf(fi, "%d", &G->vertex[i]);
    }

    while(fscanf(fi, "%d %d", &u, &v) != EOF){
        InsertEdge(G, u, v);
    }

    Topsort(G);

    return 0;
}

Queue *CreateQueue(int X){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->size = 0;
    q->front = 0;
    q->rear = -1;
    q->key = (int*)malloc(sizeof(int)*X);
    return q;
}
void Enqueue(Queue *Q, int item){
    Q->key[++Q->rear] = item;
    Q->size++;
}
int Dequeue(Queue* Q){
    Q->size--;
    return Q->key[Q->front++];
}
Graph *CreateGraph(int X){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->size = X;
    g->vertex = (int*)malloc(sizeof(int)*X);
    g->edge = (int**)malloc(sizeof(int*)*X);
    for(int i=0; i<X; i++){
        g->edge[i] = (int*)malloc(sizeof(int)*X);
        for(int j=0; j<X; j++) g->edge[i][j] = 0;
    }
    return g;
}
void InsertEdge(Graph *G, int u, int v){
    int i, j;
    for(i=0; i<G->size; i++)
        if(G->vertex[i] == u) break;
    for(j=0; j<G->size; j++)
        if(G->vertex[j] == v) break;
    G->edge[i][j] = 1;
}
void Topsort(Graph *G){
    int indegree[G->size];
    for(int i=0; i<G->size; i++) indegree[i] = 0;
    
    for(int i=0; i<G->size; i++)
        for(int j=0; j<G->size; j++)
            if(G->edge[i][j]) indegree[j]++;

    Queue* q = CreateQueue(G->size);

    for(int i=0; i<G->size; i++)
        if(indegree[i] == 0) Enqueue(q, i);

    while(q->front <= q->rear){
        int num = Dequeue(q);
        printf("%d ", G->vertex[num]);

        for(int i=0; i<G->size; i++)
            if(G->edge[num][i]){
                indegree[i]--;
                if(!indegree[i]) Enqueue(q, i);
            }
    }
    printf("\n");
}
