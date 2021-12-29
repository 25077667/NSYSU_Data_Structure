#include <stdio.h>
#include <string.h>
int main(){
    int a[5]={0}, i=1;
    a[++i] += ++i;
    printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
    i=1;
    memset(a, 0, sizeof(int)*5);
    a[++i] = a[++i] + ++i;
    printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
    return 0;
}
