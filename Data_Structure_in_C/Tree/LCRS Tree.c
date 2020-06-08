#include <stdio.h>

typedef char ElementType;

typedef struct tagLCRSNode
{
    struct tagLCRSNode* LeftChild;
    struct tagLCRSNode* RightSibling;
    ElementType Data;
}LCRSNode;

//트리 생성
LCRSNode* CreatNode(ElementType NewData){
    LCRSNode* NewNode = (LCRSNode*)malloc(sizeof(LCRSNode));
    NewNode->Data = NewData;
    NewNode->LeftChild = NULL;
    NewNode->RightSibling = NULL;

    return NewNode;
}
//트리 소멸
void DestroyNode(LCRSNode* Node){
    free(Node);
}
//트리 추가
void AddChildNode(LCRSNode* Parent, LCRSNode *Child){
    if(Parent->LeftChild ==NULL){
        Parent->LeftChild = Child;
    }
    else{
        LCRSNode* Temp = Parent->LeftChild;
        while (Temp->RightSibling != NULL)
        {
            Temp = Temp->RightSibling;
        }
        Temp->RightSibling = Child;
    }
}

//트리 출력
void PrintTree(LCRSNode* Node, int Depth){
    for(int i=0; i<Depth; i++){
        printf("");
    }
    printf("%c\n", Node->Data);

    if(Node->LeftChild != NULL){
        PrintTree(Node->LeftChild,Depth+1);
    }
    if(Node->RightSibling != NULL){
        PrintTree(Node->RightSibling,Depth+1);
    }
}
