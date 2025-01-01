#include <cstdint>
#include "testlib.h"
#include <cstdbool>
#include <cstring>
#include <string>

using namespace std;

bool mod7_check(const char *param_1)
{
    int sum = 0;
    for (int i = 0; i < 7; i++)
        sum += param_1[i];
    return sum % 7 == 0;
}

int PersonalProductKeyCheck(const char *param_1)
{
    char digits[4] = {0};

    if (strlen(param_1) != 11)
        return 0;

    memcpy(digits, param_1, 3);
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

int main(int argc, char *argv[]) {
    registerChecker("checker-test", argc, argv);
    string s = ouf.readLine();
    if (PersonalProductKeyCheck(s.c_str())) {
        quit(_ok, "shash");
    } else {
        quit(_wa, "sham");
    }
}