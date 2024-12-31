#include <stdio.h>
#include <string.h>

struct data {
    char* name;
    char* password;
};

int main() {
    struct data val[4] = {
        { "A", "ASM{passwd}" },
        { "B", "ASM{salam}" },
        { "C", "ASM{dutchman}" },
        { "D", "ASM{random}" }
    };

    char input[64];

    printf("Enter the password: ");
    scanf("%63s", input);

    if (strcmp(input, val[0].password) == 0) {
        printf("Correct!\n");
    }else{
        printf("Incorrect password!\n");
    }

    return 1;
}
