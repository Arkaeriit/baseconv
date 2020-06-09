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

void manual(){
    puts("When starting this program with no arguments, you are presented a prompt. After it you should enter either:\n"
         "* A single ASII character\n"
         "* A 'd' followed by a number in base 10\n"
         "* A 'h' or a 'x' followed by a number in base 16\n"
         "* A 'b' followed by a number in base 2\n"
         "The program will then print the number you entered in base 10, 16 and 2 and the ASCII equivalent of the 8 LSB of your number.\n"
         "\n"
         "To quit this program, simply enter 'exit' afer the prompt.\n"
         "To print this message, enter 'help' after the prompt or start the program with any argument.");
}

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

void mainLoop(){
    char* str = malloc(128);
    char* cmp = prompt(str);
    if(cmp == NULL)
        return;
    while(strcmp(str,"exit\n") && strcmp(str,":q\n") && strcmp(str,"")){
        if(!strcmp(str,"help\n"))
            manual();
        else if(strlen(str) == 2)
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
            return;
    }
}

int main(int argc, char** argv){
    if(argc == 1)
        mainLoop();
    else
        manual();
    return 0;
}


