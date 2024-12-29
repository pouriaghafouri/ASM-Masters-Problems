#include <stdio.h>
#include <string.h>

int verify_flag(const char *input) {
    char obfuscated_flag[] = {0xc4, 0xd6, 0xc8, 0xfe, 0xcc, 0xf7, 0xe4, 0xeb, 0xda, 0xe1, 0xea, 0xf7, 0xea, 0xf6, 0xf1, 0xda, 0xeb, 0xe0, 0xe8, 0xec, 0xf6, 0xed, 0xe0, 0xf8};
    char key = 0x85;

    for (int i = 0; i < strlen(obfuscated_flag); i++) {
        obfuscated_flag[i] ^= key;
    }

    if (strcmp(input, obfuscated_flag) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    char input[100];
    printf("Enter the flag: ");
    scanf("%99s", input);

    if (verify_flag(input)) {
        printf("Correct! The flag is: %s\n", input);
    } else {
        printf("Incorrect. Try again.\n");
    }

    return 0;
}
