/**
 * TODO
 * 1. 노드 생성/소멸
 * 2. 노드 추가
 * 3. 노드 탐색
 * 4. 노드 삭제
 * 5. 노드 삽입
 **/


#include <stdio.h>

typedef struct tagNode
{
    int Data;
    struct tagNode* NextNode;
} Node;

// 노드생성
Node* SLL_CreateNode(int Newdata){
    Node* NewNode = (Node*)malloc(sizeof(Newdata));

    NewNode->Data = Newdata;
    NewNode->NextNode = NULL;

    return NewNode;
} 

// 노드소멸
void SLL_DistroyNode(Node* Node){
    free(Node);
}

// 노드추가
Node* SLL_AppendNode(Node** Head, Node* NewNode){
    if ((*Head)==NULL){
        *Head = NewNode;
    }
    else{
        Node* Tail = *Head;
        while(Tail->NextNode != NULL){
            Tail = Tail->NextNode;
        }
        Tail->NextNode = NewNode;
    }
}

// 노드탐색
Node* SLL_GetNodeAt(Node* Head, int Location){
    Node* Current = Head;
    while(Current!=NULL && (--Location) >= 0){
        Current = Current->NextNode;
    }

    return Current;
}

// 노드 삭제
void SLL_RemoveNode(Node** Head, Node* Remove){
    if (*Head == Remove){
        *Head = Remove->NextNode;
    }
    else{
        Node* Current = *Head;
        while (Current != NULL && Current->NextNode != Remove)
        {
            Current = Current->NextNode;
        }
        if (Current != NULL){
            Current->NextNode = Remove->NextNode;
        }
    }
}

// 노드 삽입
void SLL_InsertNode(Node* Current, Node* NewNode){
    NewNode->NextNode = Current->NextNode;
    Current->NextNode = NewNode;
}

// 노드 수 세기
int SLL_GetCountNode(Node* Head){
    int cnt = 0;
    Node* Current = Head;
    while (Current != NULL)
    {
        Current = Current->NextNode;
        cnt++;
    }
    return cnt;
}

int main() {
    Node MyNode;

    return 0;
}