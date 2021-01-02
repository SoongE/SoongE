//Stack, FILO(First In Last Out) or LIFO(Last In First Out)
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
} Node;

typedef struct tagArrayStack
{
    int Capacity;
    int Top;
    Node* Nodes;
} ArrayStack;

void CreatStack(ArrayStack** Stack, int Capacity){
    /* creat stack at free memory */
    (*Stack) = (ArrayStack*)malloc(sizeof(ArrayStack));
    (*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);

    (*Stack)->Capacity = Capacity;
    (*Stack)->Top = 0;
}

void DestroyStack(ArrayStack* Stack){
    free(Stack->Nodes);
    free(Stack);
}

void Push(ArrayStack* Stack, ElementType Data){
    int Position = Stack->Top;

    Stack->Nodes[Position].Data = Data;
    Stack->Top++;
}

ElementType Top(ArrayStack* Stack){
    int Position = Stack->Top -1;
    return Stack->Nodes[Position].Data;
}

ElementType Pop(ArrayStack* Stack){
    int Position = --(Stack->Top);
    return Stack->Nodes[Position].Data;
}

int GetSize(ArrayStack* Stack){
    return Stack->Top;
}

int IsEmpty(ArrayStack* Stack){
    return (Stack->Top == 0);
}

int main() {

    ArrayStack* Stack = NULL;

    CreatStack(&Stack, 10);
    Push(Stack,35);
    Push(Stack,34);
    Push(Stack,33);
    Push(Stack,32);
    Push(Stack,31);

    printf("Capacity: %d, Size: %d, Top: %d\n\n", Stack->Capacity, GetSize(Stack), Top(Stack));

    for (int i = 0; i<10; i++){
        if (IsEmpty(Stack)){
            break;
        }
        printf("Popped: %d , ", Pop(Stack));
        if (!IsEmpty(Stack)){
            printf("Current Top: %d\n", Top(Stack));
        }
        else{
            printf("Stack is empty!");
        }
    }

    DestroyStack(Stack);

    return 0;
}
