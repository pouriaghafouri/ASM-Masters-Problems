#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool mod7_check(const char *param_1)
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
        sum += param_1[i];
    return sum % 7 == 0;
}

int PersonalProductKeyCheck(char *param_1)
{
    char digits[4] = {0};

    memcpy(digits, param_1, 2);
    int iVar1 = atoi(digits);
    if ((((iVar1 == 333) || (iVar1 == 444)) || (iVar1 == 555)) ||
        (((iVar1 == 666 || (iVar1 == 777)) || ((iVar1 == 888 || (iVar1 == 999))))))
    {
        return 0;
    }
    else
    {
        return mod7_check(param_1 + 4);
    }
}

int main()
{
    char serial[128];
    printf("Enter the serial number: ");
    fgets(serial, sizeof(serial), stdin);
    serial[strcspn(serial, "\n")] = 0;
    if (PersonalProductKeyCheck(serial))
        puts("Product activated!");
    else
        puts("Invalid activation code!");
    return 0;
}