#include <unistd.h>
#include <fcntl.h>

char buffer[1024];
int count[26];

int main() {
    int fd = open("input.txt", O_RDONLY);
    while (read(fd, buffer, 1024) > 0) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if ('a' <= buffer[i] && buffer[i] <= 'z') {
                count[buffer[i] - 'a']++;
            }
        }
    }
    close(fd);
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < count[i]; j++) {
            buffer[0] = 'a' + i;
            write(fd, buffer, 1);
        }
    }
    write(fd, "\n", 1);
    return 0;
}
