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

void prompt(char* str){
    printf(">");
    fgets(str, 1000, stdin);
}

void detail(uint64_t num){
    char* numCH = &num;
    printf("ASCII : %c\n"
           "décimal : %i\n"
           "héxadécimal : %x\n"
           "binaire : " BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN BYTE_TO_BINARY_PATTERN "\n"
           "----------------------------\n"
           ,(char) num, num, num, BYTE_TO_BINARY(numCH[7]), BYTE_TO_BINARY(numCH[6]), BYTE_TO_BINARY(numCH[5]), BYTE_TO_BINARY(numCH[4]), BYTE_TO_BINARY(numCH[3]), BYTE_TO_BINARY(numCH[2]), BYTE_TO_BINARY(numCH[1]), BYTE_TO_BINARY(numCH[0]));
}

void mainLoop(){
    char* str = malloc(1024);
    prompt(str);
    while(strcmp(str,"exit\n") && strcmp(str,":q\n")){
        if(strlen(str) == 2)
            detail(str[0]);
        else if(str[0] == 'x' || str[0] == 'h'){
            uint64_t nmb;
            sscanf(str+1,"%x\n",&nmb);
            detail(nmb);
        }else if(str[0] == 'd'){
            uint64_t nmb;
            sscanf(str+1,"%i\n",&nmb);
            detail(nmb);
        }else{
            uint64_t nmb;
            sscanf(str,"%i\n",&nmb);
            detail(nmb);
        }
        prompt(str);
    }
}

int main(){
    mainLoop();
    return 0;
}

