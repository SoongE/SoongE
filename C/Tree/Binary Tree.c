#include <stdio.h>

typedef char ElementType;
typedef struct tagSBTNode
{
    struct tagSBTNode* Left;
    struct tagSBTNode* Right;
    ElementType Data;
}SBTNode;

//생성
SBTNode* CreatNode(ElementType NewData){
    SBTNode* NewNode = (SBTNode*)malloc(sizeof(SBTNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

//소멸
void DestroyNode(SBTNode* Node){
    free(Node);
}

//전위 순회
void PreorderPrintTree(SBTNode* Node){
    if (Node ==NULL)
        return;
    //루트 노드 출력
    printf('%c', Node->Data);
    PreorderPrintTree(Node->Left);
    PreorderPrintTree(Node->Right);
}

//중위 순회
void InorderPrintTree(SBTNode* Node){
    if (Node=NULL)
        return;
    InorderPrintTree(Node->Left);
    printf('%c', Node->Data);
    InorderPrintTree(Node->Right);
}

//후위 순회
void PostorderPrintTree(SBTNode* Node){
    if (Node=NULL)
        return;
    PostorderPrintTree(Node->Left);
    PostorderPrintTree(Node->Right);
    printf('%c', Node->Data);
}

//소멸 "트리를 소멸할 때에는 반드시 잎 노드부터 자유저장소에서 제거해야한다."
void DestroyTree(SBTNode* Root){
    if (Root == NULL)
        return;
    DestroyTree(Root->Left);
    DestroyTree(Root->Right);
    DestroyTree(Root);
}









