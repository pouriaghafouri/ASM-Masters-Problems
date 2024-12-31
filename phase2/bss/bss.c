#include <stdio.h>
#include <string.h>

char flag[64] = "ASM{do_you_know_what_is_bss}";

void initialize_flag() {
    volatile char *dummy = flag;
    (void)dummy;
}

int main() {
    printf("Welcome to the BSS challenge! (Dutchman is here Niggers!)\n");
    printf("Your task is to find the hidden flag using gdb.\n");
    printf("Good luck!\n");

    printf("The flag is: %p\n", (void*)flag);
    for (int i = 0; i < 5; i++) {
        printf("Running...\n");
    }

    return 0;
}
