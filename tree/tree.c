#include <stdio.h>
#include <stdlib.h>

struct TreeStruct{
	int size;
	int numOfNode;
	int* element;
};

typedef struct TreeStruct* Tree;

Tree CreateTree(int size);
void Insert(Tree tree, int value);
void PrintTree(Tree tree);
void PrintPreorder(Tree tree, int index);
void PrintInorder(Tree tree, int index);
void PrintPostorder(Tree tree, int index);
void DeleteTree(Tree tree);

int main(int argc, char* argv[]){
	FILE* fi;
	Tree tree;
	int treeSize;
	int tmpNum;

	fi = fopen(argv[1], "r");
	fscanf(fi, "%d", &treeSize);

	tree = CreateTree(treeSize);

	while(fscanf(fi, "%d", &tmpNum) == 1){
		Insert(tree, tmpNum);
	}

	PrintTree(tree);
	DeleteTree(tree);

	return 0;
}

Tree CreateTree(int size){
	int* arr = (int*)malloc(sizeof(int)*size);
	Tree t = (Tree)malloc(sizeof(struct TreeStruct));
	t->size = size;
	t->numOfNode = 0;
	t->element = arr;
	return t;
}

void Insert(Tree tree, int value){
	if(tree->numOfNode >= tree->size){
		printf("Error with node %d! Tree is already full so we cannot insert any node in the tree!\n", value);
		return;
	}
	tree->element[tree->numOfNode++] = value;
}

void PrintTree(Tree tree){
	printf("Preorder: ");
	PrintPreorder(tree, 0);
	printf("\nInorder: ");
	PrintInorder(tree, 0);
	printf("\nPostorder: ");
	PrintPostorder(tree, 0);
	printf("\n");
}

void PrintPreorder(Tree tree, int value){
	if(value >= tree->numOfNode) return;
	printf("%d ", tree->element[value]);
	PrintPreorder(tree, 2*value + 1);
	PrintPreorder(tree, 2*value + 2);
}

void PrintInorder(Tree tree, int value){
	if(value >= tree->numOfNode) return;
	PrintInorder(tree, 2*value + 1);
	printf("%d ", tree->element[value]);
	PrintInorder(tree, 2*value + 2);
}

void PrintPostorder(Tree tree, int value){
	if(value >= tree->numOfNode) return;
	PrintPostorder(tree, 2*value + 1);
	PrintPostorder(tree, 2*value + 2);
	printf("%d ", tree->element[value]);
}

void DeleteTree(Tree tree){
	free(tree->element);
	free(tree);
}
