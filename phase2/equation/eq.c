#include <stdio.h>
#include <string.h>

int eq1(char *flag) {
    return (flag[15] - flag[21] == -26);
}

int eq2(char *flag) {
    return ((flag[22] | flag[20]) == 127);
}

int eq3(char *flag) {
    return ((flag[15] & flag[13]) == 78);
}

int eq4(char *flag) {
    return ((flag[4] + flag[8]) == 224);
}

int eq5(char *flag) {
    return ((flag[26] & flag[1]) == 80);
}

int eq6(char *flag) {
    return ((flag[6] | flag[24]) == 127);
}

int eq7(char *flag) {
    return ((flag[7] | flag[23]) == 119);
}


int eq8(char *flag) {
    return ((flag[5] % flag[18]) == 51);
}

int eq9(char *flag) {
    return ((flag[15] * flag[22]) == 4560);
}

int eq10(char *flag) {
    return ((flag[4] + flag[13]) == 220);
}

int eq11(char *flag) {
    return ((flag[21] - flag[2]) == 44);
}

int eq12(char *flag) {
    return ((flag[19] + flag[6]) == 169);
}

int eq13(char *flag) {
    return ((flag[21] + flag[25]) == 238);
}

int eq14(char *flag) {
    return ((flag[12] & flag[4]) == 110);
}

int eq15(char *flag) {
    return ((flag[12] & flag[18]) == 102);
}

int eq16(char *flag) {
    return ((flag[7] % flag[5]) == 0);
}

int eq17(char *flag) {
    return ((flag[8] | flag[3]) == 123);
}

int eq18(char *flag) {
    return ((flag[16] % flag[24]) == 54);
}

int eq19(char *flag) {
    return ((flag[5] | flag[20]) == 127);
}

int eq20(char *flag) {
    return ((flag[26] + flag[17]) == 161);
}

int main() {
    char input[100];
    char flag[100];

    printf("Enter input: ");
    scanf("%99s", input);

    snprintf(flag, sizeof(flag), "ASM{%s}", input);

    if (eq1(flag) & eq2(flag) & eq3(flag) & eq4(flag) & eq5(flag) & eq6(flag) & eq7(flag) & eq8(flag) & eq9(flag) &
        eq10(flag) & eq11(flag) & eq12(flag) & eq13(flag) & eq14(flag) & eq15(flag) & eq16(flag) & eq17(flag) &
        eq18(flag) & eq19(flag) & eq20(flag)) {
        printf("Well done\n");
    } else {
        printf("Try again\n");
    }

    return 0;
}
