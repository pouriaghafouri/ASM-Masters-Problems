#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

char keys[20] = {0xb8,0x30,0xb0,0xe6,0xf4,0x4f,0x1a,0x64,0x81,0x4c,0x74,0xa,0x60,0x2,0x3d,0x99,0x49,0xd,0xdf,0xf4};

int get_number(int a){
    if (a >= 216){
        return a - 216;
    }else if(a >= 0 && a < 216){
        return a;
    }else{
        return a-1;
    }
}

char doxor(char a, int b){
    char c;
    if (b % 2 == 0){
        c = a ^ b;
    }else{
        c = a ^ (b-1);
    }
    return c;
}

char *get_keys(){
    char *out = malloc(sizeof(char) * 100);
    for(int i=0;i<100;i++){
        out[i]='\0';
    }
    char keys_2[20];
    for(int i=0;i<20;i++){
        int number = get_number(i*i);
        keys_2[i] = doxor(keys[i], number);
    }
    for(int i=0;i<20;i++){
        sprintf(out, "%s%x", out, (unsigned char) keys_2[i]);
    }
    return out;
}

char *calculate(const char *input) {
    char *out = (char*) malloc(sizeof(char)*100);
    for(int i=0;i<100;i++){
        out[i]='\0';
    }
    char *result = (char*) malloc(sizeof(char)*100);
    SHA1((unsigned char*)input, strlen(input), (unsigned char*)result);
    for(int i=0;i<SHA_DIGEST_LENGTH;i++){
        sprintf(out, "%s%x", out, (unsigned char) result[i]);
    }
    return out;
}

int diff_checker(char *a, char *b){
    int ptr1 = 0;
    int ptr2 = 0;
    int out = 0;
    while(a[ptr1] != '\0' && b[ptr2] != '\0'){
        if(a[ptr1] != b[ptr2]){
            out++;
        }
        ptr1++;
        ptr2++;
    }
    if (ptr1 != ptr2){
        out++;
    }
    return out;
}

int main() {
    char input_string[256];

    // Get input from the user
    printf("Enter the password: ");
    fgets(input_string, sizeof(input_string), stdin);
    input_string[strcspn(input_string, "\n")] = 0;
    char *keys = get_keys();
    char *user = calculate(input_string);
    int diff = diff_checker(keys, user);
    if (diff == 0){
        printf("The flag is: ASM{%s}\n", input_string);
    } else{
        printf("7ry Ag@1n!\n");
    }
    return 0;
}
