#include <stdio.h>

char buffer[1024];
int count[26];

int main() {
    while (fgets(buffer, 1024, stdin) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if ('a' <= buffer[i] && buffer[i] <= 'z') {
                count[buffer[i] - 'a']++;
            }
        }
    }
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            putchar('a' + i);
        }
    }
    putchar('\n');
    return 0;
}
