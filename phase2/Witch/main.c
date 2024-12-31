#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_flag(){
    char flag[] = "ASM{C0ng7@tu1@ti#n5_N30}";
    printf("%s\n", flag);
}

long long int get_number(){
    long long int out = rand();
    return out % 0xdeadbeef;
}

int main(){
    srand(time(0) / 5);
    printf("Enter to password: ");
    long long int number = get_number();
    long long int input;
    scanf("%lld", &input);
    if (input == number){
        print_flag();
    }else{
        printf("Go away and come ontime!\n");
    }
}
