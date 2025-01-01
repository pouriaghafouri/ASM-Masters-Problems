#include <math.h>
#include <stdio.h>
int main() {
    float x1, x2, y1, y2, r1, r2;
    scanf("%f%f%f%f%f%f", &x1, &y1, &r1, &x2, &y2, &r2);

    float d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    d = sqrtf(d);
    float del = r1 - r2;
    if (del < 0)
        del = -del;
    float sum = r1 + r2;

    if (d < del)
        printf("inside\n");
    else if (d > sum)
        printf("outside\n");
    else
        printf("touch\n");
}
