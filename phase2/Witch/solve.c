#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(0)/5);
    printf("%lld\n", rand() % 0xdeadbeef);
}