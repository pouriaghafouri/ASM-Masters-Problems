#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[] = {'A','X','M','F','S','C','c','H','R','E','_','8','1','3','p','4','E','I','f','n','4','C','}',0};
char b[] = {'H','S','X','{','v','3','V','U','Z','3','Q','S','w','m','R','L','C','_','5','L','K','G',0,0};

void get_flag(char *str, unsigned long input){
    long int sum = 0xdeadbeef;
    for(int i=0;i<strlen(str);i++){
        sum += (unsigned char)str[i];
    }
    sum -= input;
    char *out = malloc(sizeof(char) * 100);
    while(1){
        if (sum % 953 == 23){
            break;
        }
        out[sum] = sum % 2 ? b[sum] : a[sum];
        sum += 1;
    }
    out[sum] = '\0';
    printf("%s\n", out);
}

int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage: %s <password>\n", argv[0]);
        exit(1);
    }
    char easy_string[] = "ASM{sup3r_s1mpl3_bu7_f4ke_fl4g}";
    // 3735931462
    get_flag(easy_string, strtoul(argv[1], NULL, 10));
}