#include <stdio.h>

char buffer[1024];
int count[26];

int main() {
    FILE *fp = fopen("input.txt", "r");
    while (fgets(buffer, 1024, fp) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if ('a' <= buffer[i] && buffer[i] <= 'z') {
                count[buffer[i] - 'a']++;
            }
        }
    }
    fclose(fp);
    fp = fopen("output.txt", "w");
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            fputc('a' + i, fp);
        }
    }
    fputc('\n', fp);
    return 0;
}
