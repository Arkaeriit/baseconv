#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0') 

char * prompt(char* str){
    printf(">");
    return fgets(str, 66, stdin);
}

void detail(uint64_t num){
    char* numCH = (char*) &num;
    printf("ASCII : %c\n"
           "decimal : %" PRIu64 "\n"
           "hexadecimal : %" PRIx64 "\n"
           "binary : " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n"
           "----------------------------\n"
           ,(char) num, num, num, BYTE_TO_BINARY(numCH[7]), BYTE_TO_BINARY(numCH[6]), BYTE_TO_BINARY(numCH[5]), BYTE_TO_BINARY(numCH[4]), BYTE_TO_BINARY(numCH[3]), BYTE_TO_BINARY(numCH[2]), BYTE_TO_BINARY(numCH[1]), BYTE_TO_BINARY(numCH[0]));
}

#define isOne(ch) (ch == '1' ? 1 : 0)

uint64_t binToInt(char* str){
    uint64_t ret = 0;
    size_t len = strlen(str);
    for(size_t i=0; i<len; i++){
        int n = isOne(str[len - i - 1]);
        ret |= (n & 1) << i;
    }
    return ret;
}

int mainLoop(){
    char* str = malloc(128);
    char* cmp = prompt(str);
    if(cmp == NULL)
        return 1;
    while(strcmp(str,"exit\n") && strcmp(str,":q\n") && strcmp(str,"")){
        if(strlen(str) == 2)
            detail(str[0]);
        else if(str[0] == 'x' || str[0] == 'h'){
            uint64_t nmb;
            sscanf(str+1,"%" PRIx64 "\n",&nmb);
            detail(nmb);
        }else if(str[0] == 'd'){
            uint64_t nmb;
            sscanf(str+1,"%" PRIu64 "\n",&nmb);
            detail(nmb);
        }else if(str[0] == 'b'){
            str[strlen(str)-1] = 0;
            uint64_t nmb = binToInt(str+1);
            detail(nmb);
        }else{
            uint64_t nmb;
            sscanf(str,"%" PRIu64 "\n",&nmb);
            detail(nmb);
        }
        cmp = prompt(str);
        if(cmp == NULL)
            return 1;
    }
    return 0;
}

int main(){
    return mainLoop();
}

