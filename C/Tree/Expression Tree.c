/*
수식트리의 성질에 적합한 순회 방법은 후위순회
따라서 왼쪽하위->오른쪽하위->루트 순으로 순회
*/

#include <stdio.h>
#include <string.h>

typedef char ElementType;
typedef struct tagETNode
{
    struct tagETNode* Left;
    struct tagETNode* Right;
    ElementType Data;
}ETNode;

//생성
ETNode* CreatNode(ElementType NewData){
    ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;
    NewNode->Data = NewData;

    return NewNode;
}

//소멸
void DestroyNode(ETNode* Node){
    free(Node);
}

//구축하기
void BuildExpressionTree(char* PostFixExpression, ETNode** Node){
    int len = strlen(PostFixExpression);
    char Token = PostFixExpression[len-1];
    PostFixExpression[len-1] = '\0';

    switch (Token)
    {
    case '+': case '-': case '*': case '/':
        (*Node) = CreatNode(Token);
        BuildExpressionTree(PostFixExpression, &(*Node)->Right);
        BuildExpressionTree(PostFixExpression, &(*Node)->Left);
        break;
    
    default:
        (*Node) = CreatNode(Token);
        break;
    }
}


//계산하기
double Evaluate(ETNode* Tree){
    char Temp[2];

    double Left = 0;
    double Right = 0;
    double Result = 0;
    if (Tree=NULL)
        return 0;
    
    switch (Tree->Data){
    case '+': case '-': case '*': case '/':
        Left = Evaluate(Tree->Left);
        Right = Evaluate(Tree->Right);

        if (Tree->Data == '+') Result = Left + Right;
        else if (Tree->Data == '-') Result = Left - Right;
        else if (Tree->Data == '*') Result = Left * Right;
        else if (Tree->Data == '/') Result = Left / Right;

        break;
    
    default:
        memset(Temp,0,sizeof(Temp));
        Temp[0] = Tree->Data;
        Result = atof(Temp);
        break;
    }
    return Result;
}
