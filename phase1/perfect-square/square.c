#include <stdio.h>
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);

    int root = sqrt(n);
    if (n == root * root)
        printf("YES");
    else
        printf("NO");
}
