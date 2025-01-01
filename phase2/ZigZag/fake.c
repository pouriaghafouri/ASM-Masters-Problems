#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a[] = {'A','X','M','F','_','C','_','H','_','E','_','8','_','3','A','4','E','I','F','n','A','C','}',0};
char b[] = {'H','S','X','{','v','_','V','_','Z','_','Q','_','w','F','R','K','C','_','5','L','K','G',0,0};

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

int main(){
    char easy_string[] = "MY name IS linus TORVALDS and I am YOUR god!";
    int sum = 0;
    for(int i=0;i<strlen(easy_string);i++){
        sum += easy_string[i];
    }
    printf("Enter password: ");
    long long int password;
    scanf("%llu", &password);
    //3735932032
    get_flag(easy_string, password);
}