#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int num1, temp, multiply=0;
    char* num2 = malloc(sizeof(char)*10);
    int* result = malloc(sizeof(int)*10);

    scanf("%d",&num1);
    scanf("%s",num2);
    
    for(int i=strlen(num2)-1; i>=0; i--){
        temp = (num2[i]-'0')*num1;
        printf("%d\n",temp);
        result[i] = temp * pow(10,strlen(num2)-1-i);
    }

    for(int i=0; i<strlen(num2);i++){
        multiply += result[i];
    }
    printf("%d",multiply);

    free(result);
    free(num2);

    return 0;
}