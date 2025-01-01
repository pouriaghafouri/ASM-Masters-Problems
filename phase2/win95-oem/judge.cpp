#include <cstdint>
#include "testlib.h"
#include <cstdbool>
#include <cstring>
#include <string>

using namespace std;

#define MIN(x, y) ((x) < (y) ? (x) : (y))

bool mod7_check(const char *param_1)
{
    int IndexCounter;
    int SUM;
    char character;

    IndexCounter = 0;
    SUM = 0;
    while (true)
    {
        character = *param_1;
        if ((character < '0') || ('9' < character))
            break;
        /* Convert Char to Int ?? */
        SUM = SUM + character + -48;
        IndexCounter = IndexCounter + 1;
        param_1 = param_1 + 1;
        if (6 < IndexCounter)
        {
            return SUM % 7 == 0;
        }
    }
    return false;
}

int check_oem_key(const char *key, int len)

{
    int key_length;
    int is_oem;
    int first_3_digits_int;
    int second_2_digits_int;
    int i;
    int i_;
    char first_three_digits[4];
    char second_two_digits[3];
    char kc;

    key_length = strlen(key);
    if ((((key_length == 0x17) && (key[5] == '-')) && (key[9] == '-')) &&
        ((key[0x11] == '-' && (is_oem = memcmp(key + 6, "OEM", 3), is_oem == 0))))
    {
        /* Check first 5 digits, must be numeric */
        i = 0;
        do
        {
            kc = key[i];
            if (kc < '0')
            {
                return 0;
            }
            if ('9' < kc)
            {
                return 0;
            }
            i = i + 1;
        } while (i < 5);
        /*  */
        memcpy(first_three_digits, key, MIN(3, len));
        first_three_digits[3] = '\0';
        first_3_digits_int = atoi(first_three_digits);
        if ((first_3_digits_int != 0) &&
            (first_3_digits_int < 367
             /* check if between 1 and 366 */))
        {
            memcpy(second_two_digits, key + 3, MIN(2, len));
            second_two_digits[2] = '\0';
            second_2_digits_int = atoi(second_two_digits);
            if (((second_2_digits_int < 3) || (94 < second_2_digits_int)) &&
                (((key[10] == '0' && ('0' < key[0x10])) && (key[0x10] < '8'))))
            {
                i_ = 0x12;
                while ((kc = key[i_], '/' < kc && (kc < ':')))
                {
                    i_ = i_ + 1;
                    if (0x16 < i_)
                    {
                        /* jump to part after oem- */
                        return mod7_check(key + 10);
                    }
                }
            }
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    registerChecker("checker-test", argc, argv);
    string s = ouf.readLine();
    if (check_oem_key(s.c_str())) {
        quit(_ok, "shash");
    } else {
        quit(_wa, "sham");
    }
}