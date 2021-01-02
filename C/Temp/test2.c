#include <stdio.h>
void main()
{
    int H, M;
    scanf("%d %d",&H,&M);
    M = M - 45;
    if(M < 0){
        H = H - 1;
        M = 60 + M;
    }
    if(H < 0){
        H = H + 24;
    }
    printf("%d %d", H, M);
}