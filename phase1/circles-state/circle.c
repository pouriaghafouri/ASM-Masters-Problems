#include <stdio.h>

int main(){
    int x1, y1, r1, x2, y2, r2;
    scanf("%d %d %d %d %d %d", &x1, &y1, &r1, &x2, &y2, &r2);

    int distance = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);

    if (distance < (r1 - r2) * (r1 - r2))
        printf("inside\n");
    else if (distance > (r1 + r2) * (r1 + r2))
        printf("outside\n");
    else
        printf("touch\n");
  
    return 0; 
}
