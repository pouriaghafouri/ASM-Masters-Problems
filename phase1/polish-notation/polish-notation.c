#include <stdio.h>
#include <stdlib.h>

char buffer[12];

int readExpression() {
    scanf("%s", buffer);
    if (buffer[0] == '+') {
        return readExpression() + readExpression();
    } else if (buffer[0] == '-') {
        return readExpression() - readExpression();
    } else if (buffer[0] == '*') {
        return readExpression() * readExpression();
    } else if (buffer[0] == '/') {
        return readExpression() / readExpression();
    } else {
        return atoi(buffer);
    }
}

int main() {
    printf("%d\n", readExpression());
    return 0;
}
