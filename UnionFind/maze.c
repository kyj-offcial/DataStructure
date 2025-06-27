#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _DisjointSet{
	int size;
	int* ptr_arr;
} DisjointSets;

typedef struct _PrintDisjointSet{
	int size;
	int* ptr_arr;
} PrintDisjointSets;

void init(DisjointSets *sets, PrintDisjointSets *maze, int n);
int find(DisjointSets *sets, int x);
void union_(DisjointSets *sets, int i, int j);
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n);
void printMaze(PrintDisjointSets *maze, int n);
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze);

int main(int argc, char* argv[]){
	int num;
	FILE *fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &num);
	fclose(fi);

	DisjointSets *sets;
	PrintDisjointSets *maze;
	sets = (DisjointSets*)malloc(sizeof(DisjointSets));
	maze = (PrintDisjointSets*)malloc(sizeof(PrintDisjointSets));

	init(sets, maze, num);
	createMaze(sets, maze, num);

	printMaze(maze, num);
	freeMaze(sets, maze);

	return 0;
}

void init(DisjointSets *sets, PrintDisjointSets *maze, int n){
	int countSets = n*n+1;
	int countMaze = 2*n*n+1;
	sets->size = countSets;
	maze->size = countMaze;

	sets->ptr_arr = (int*)malloc(sizeof(int)*countSets);
	maze->ptr_arr = (int*)malloc(sizeof(int)*countMaze);

	for(int i=0; i<countSets; i++) sets->ptr_arr[i] = -1;
	for(int i=0; i<countMaze; i++) maze->ptr_arr[i] = 1;
	maze->ptr_arr[0] = 0;
	maze->ptr_arr[n*n] = 0;
}

int find(DisjointSets *sets, int x){
	if(sets->ptr_arr[x] < 0) return x;
	return find(sets, sets->ptr_arr[x]);
}

void union_(DisjointSets *sets, int i, int j){
	int first = find(sets, i);
	int second = find(sets, j);
	if(first == second) return;

	if(sets->ptr_arr[second] < sets->ptr_arr[first]){
		sets->ptr_arr[second] += sets->ptr_arr[first];
		sets->ptr_arr[first] = second;
	}
	else{
		if(sets->ptr_arr[second] == sets->ptr_arr[first]) sets->ptr_arr[first]--;
		sets->ptr_arr[first] += sets->ptr_arr[second];
		sets->ptr_arr[second] = first;
	}
}
void createMaze(DisjointSets *sets, PrintDisjointSets *maze, int n){
	srand(time(NULL));
	int left, right;
	while(find(sets, 1) != find(sets, n*n)){
		int num = rand() % maze->size;
		if(num <= n*n){
			if(num % n == 0) continue;
			left = num;
			right = num+1;
		}
		else {
			if(num>2*n*n-n) continue;
			left = num%(n*n);
			right = num%(n*n)+n;
		}
		
		if(find(sets, left) != find(sets, right)){
			union_(sets, left, right);
			maze->ptr_arr[num] = 0;
		}
	}
}
void printMaze(PrintDisjointSets *maze, int n){
	for(int i=0; i<n; i++) printf("*-");
	printf("*\n");

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(maze->ptr_arr[i*n+j] == 1){
				printf("| ");
			}
			else{
				printf("  ");
			}
		}
		if(i == n-1) break;
		else printf("|\n");
		for(int j=0; j<n; j++){
			if(maze->ptr_arr[n*n+i*n+j+1] == 1){
				printf("*-");
			}
			else{
				printf("* ");
			}
		}
		printf("*\n");
	}
	printf(" \n");
	for(int i=0; i<n; i++){
		printf("*-");
	}
	printf("*");
}
void freeMaze(DisjointSets *sets, PrintDisjointSets *maze){
	free(sets->ptr_arr);
	free(sets);
	free(maze->ptr_arr);
	free(maze);
}
