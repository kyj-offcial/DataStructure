#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;

struct Node{
        ElementType element;
        Position next;
};

List MakeEmptyList(){
        List l = (List)malloc(sizeof(List));
        l->element = -1;
        l->next = NULL;
        return l;
}

int isLast(Position p){
    	return p->next == NULL;
}

Position FindPrevious(ElementType x, List l){
    	Position p = l;
    	while (p->next != NULL && p->next->element != x)
        	p = p->next;
    	return p;
}

Position Find(ElementType x, List l){
	Position p = l;
    	while (p != NULL && p->element != x)
        	p = p->next;
    	return p;
}

void Insert(ElementType x, Position p, List l){
	if (p == NULL) {
		printf("Insertion(%d) Failed: cannot find the location to be inserted.\n", x);
        	return;
   	}
    	List newNode = (List)malloc(sizeof(List));
    	newNode->element = x;
    	newNode->next = p->next;
	p->next = newNode;
}

void Delete(ElementType x, List l){
	Position p = FindPrevious(x, l);
	if(p->next == NULL){
		printf("Deletion Failed: element %d is not in the list.\n", x);
		return;
	}
	Position tmp = p->next;
	p->next = tmp->next;
	free(tmp);	
}

void DeleteList(List l){
	Position p = l->next;
    	Position tmp;
    	while (p != NULL) {
        	tmp = p;
        	p = p->next;
        	free(tmp);
    	}
    	l->next = NULL;
    	free(l);
}
void PrintList(List l){
        PtrToNode tmp = NULL;
        tmp = l->next;
        if(tmp==NULL){
                printf("your list is empty!\n");
                return;
        }
        while(tmp!=NULL){
                printf("key: %d  ", tmp->element);
                tmp = tmp->next;
        }
        printf("\n");
}
int main(int argc, char* argv[]){
        char command;
        int key1, key2;
        FILE *input, *output;
        Position header = NULL, tmp = NULL;

        if(argc <= 1){
                printf("please enter an input file.");
                return 0;
        }
        else input = fopen(argv[1], "r");
        header = MakeEmptyList();
        while(1){
                command = fgetc(input);
                if(feof(input)) break;

                switch(command){
                        case 'i':
                                fscanf(input, "%d %d", &key1, &key2);
                                tmp = Find(key2, header);
                                Insert(key1, tmp, header);
                                break;
                        case 'd':
                                fscanf(input, "%d", &key1);
                                Delete(key1, header);
                                break;
                        case 'f':
                                fscanf(input, "%d", &key1);
                                tmp = FindPrevious(key1, header);
                                if(isLast(tmp)) printf("Could not find %d in the list.\n", key1);
                                else if(tmp->element > 0) printf("Key of the previous node of %d is %d.\n", key1, tmp->element);
                                else printf("Key of the previous node of %d is header.\n", key1);
                                break;
                        case 'p':
                                PrintList(header);
                                break; 
                        default:
                                ;
                }
        }
}
