#include <stdio.h>
#include <stdlib.h>
char* getBin(unsigned int num){
    char* s = malloc(sizeof(char)*32);
    for(int i = 0; i < 32; i++){
        int bit = num%2;
        num/=2;
        s[31-i] = bit+'0';
        //printf("%d", bit);
    }
    return s;
}

int main(){
    for(int i = 2147483640;; i++){
        if(i == -2147483640)
            break;
            printf("%d\t%s\n",i, getBin(i));
    }
    return 0;
}
