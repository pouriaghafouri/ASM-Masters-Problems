#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define disable_buffering(_fd) setvbuf(_fd, NULL, _IONBF, 0)

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

int main(){
    disable_buffering(stdin);
    disable_buffering(stdout);
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
