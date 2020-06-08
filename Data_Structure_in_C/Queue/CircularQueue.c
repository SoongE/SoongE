// Circular Queue

#include <stdio.h>

typedef int ElementType;

typedef struct tagNode{
    ElementType Data;
}Node;

typedef struct tagCircularQueue
{
    int Capacity;
    int Front;
    int Rear;
    Node* Nodes;
}CircularQueue;

//생성
void CreateQueue(CircularQueue** Queue, int Capacity){
    (*Queue) = (CircularQueue*)malloc(sizeof(CircularQueue));
    (*Queue)->Nodes = (Node*)malloc(sizeof(Node)*Capacity);
    (*Queue)->Capacity = Capacity;
    (*Queue)->Front = 0;
    (*Queue)->Rear = 0;
}

//삭제
void DestroyQueue(CircularQueue* Queue){
    free(Queue->Nodes);
    free(Queue);
}

//삽입
void Enqueue(CircularQueue* Queue, ElementType Data){
    int position = 0;
    if (Queue->Rear == Queue->Capacity){
        position = Queue->Rear;
        Queue->Rear = 0;
    }
    else{
        position = Queue->Rear++;
    }

    Queue->Nodes[position].Data = Data;
}

//제거
ElementType Dequeue(CircularQueue* Queue){
    int position = Queue->Front;

    if (Queue->Front == Queue->Capacity){
        Queue->Front = 0;
    }
    else{
        Queue->Front++;
    }

    return Queue->Nodes[position].Data;
}

//공백확인
int IsEmpty(CircularQueue* Queue){
    return (Queue->Front == Queue->Rear);
}

//포화확인
int IsFull(CircularQueue* Queue){
    if (Queue->Front < Queue->Rear)
        return (Queue->Rear - Queue->Front) == Queue->Capacity;
    else
        return (Queue->Rear+1) == Queue->Front;   
}