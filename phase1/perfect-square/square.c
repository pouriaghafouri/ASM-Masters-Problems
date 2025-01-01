#include <stdio.h>
#include <math.h>

int main(){
    int n;
    scanf("%d", &n);

    int flag = 1;
    for (int i = 1; i < 10001; i++){
        if (i * i == n){
            flag = 0;
            printf("YES\n");
            break;
        }
    }

    if (flag)
        printf("NO\n");

    return 0;
}
