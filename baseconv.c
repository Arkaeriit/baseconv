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
         "* A string of ASII characters\n"
         "* A negative number in base 10\n"
         "* A 'd' followed by a positive or negative number in base 10\n"
         "* A 'h' or a 'x' followed by a number in base 16\n"
         "* A 'b' followed by a number in base 2\n"
         "The program will then print the number you entered in base 10, 16 and 2 and the ASCII equivalent of the 8 LSB of your number.\n"
         "\n"
         "To quit this program, simply enter 'exit' afer the prompt.\n"
         "To print this message, enter 'help' after the prompt or start the program with any argument.\n"
         "\n"
         "Alternatively, if you give a single argument to this program it will process it and exit immediately."
    );
}

//Fill str with user input.
char* prompt(char* str){
    printf(">");
    return fgets(str, 66, stdin);
}

//Take the number num and represent it as a C string 
char* bitToASCII(uint64_t num){
    char* ret = malloc(9);
    for(uint8_t i=0; i<8; i++) //We create a string with each byte of num
        ret[i] = (char) (num >> (i * 8));
    return ret;
}

//Print all the info we need about a positive number
void detail(uint64_t num){
    char* numCH = (char*) &num;
    char* bTA = bitToASCII(num);
    printf("ASCII : %s\n"
           "decimal : %" PRIu64 "\n"
           "hexadecimal : %" PRIx64 "\n"
           "binary : " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n"
           "----------------------------\n"
           , bTA, num, num, BYTE_TO_BINARY(numCH[7]), BYTE_TO_BINARY(numCH[6]), BYTE_TO_BINARY(numCH[5]), BYTE_TO_BINARY(numCH[4]), BYTE_TO_BINARY(numCH[3]), BYTE_TO_BINARY(numCH[2]), BYTE_TO_BINARY(numCH[1]), BYTE_TO_BINARY(numCH[0]));
    free(bTA);
}

//Print all the info we need about a negative number
void detailNeg(uint64_t numNeg){
    uint64_t num = ~numNeg + 1; //Computing two's complement
    char* numCH = (char*) &num;
    char* bTA = bitToASCII(num);
    printf("ASCII : %s\n"
           "decimal : -%" PRIu64 "\n"
           "hexadecimal : %" PRIx64 "\n"
           "binary : " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n"
           "----------------------------\n"
           , bTA, numNeg, num, BYTE_TO_BINARY(numCH[7]), BYTE_TO_BINARY(numCH[6]), BYTE_TO_BINARY(numCH[5]), BYTE_TO_BINARY(numCH[4]), BYTE_TO_BINARY(numCH[3]), BYTE_TO_BINARY(numCH[2]), BYTE_TO_BINARY(numCH[1]), BYTE_TO_BINARY(numCH[0]));
    free(bTA);
}

#define isOne(ch) (ch == '1' ? 1 : 0)

//Convert a string of '0' and '1' to a number
uint64_t binToInt(char* str){
    uint64_t ret = 0;
    size_t len = strlen(str);
    for(size_t i=0; i<len; i++){
        int n = isOne(str[len - i - 1]);
        ret |= (n & 1) << i;
    }
    return ret;
}

#define min(a,b) ( a > b ? b : a)

//Convert the 8 first bits of str as if they were a 64 bit number
uint64_t strToBitStream(char* str){
    uint64_t ret = 0;
    memcpy(&ret, str, strnlen(str, sizeof(uint64_t)));
    return ret;
}

void processString(char* str){
    if(str[strlen(str)-1] == '\n')
        str[strlen(str)-1] = 0; //Removing the \n at the end of the string return by prompt
    if(!strcmp(str,"help") || !strcmp(str,"--help") || !strcmp(str,"-h"))
        manual();
    else if(str[0] == 'x' || str[0] == 'h'){ //An exa number
        uint64_t num;
        sscanf(str+1,"%" PRIx64 ,&num);
        detail(num);
    }else if(str[0] == 'd'){ //A decimal number
        if(str[1] == '-') { //A negative decimal number
            uint64_t num;
            sscanf(str+2,"%" PRIu64 ,&num);
            detailNeg(num);
         }else{ //A positive decimal number
            uint64_t num;
            sscanf(str+1,"%" PRIu64 ,&num);
            detail(num);
         }
    }else if(str[0] == '-'){ //A negative decimal number
        uint64_t num;
        sscanf(str+1,"%" PRIu64 ,&num);
        detailNeg(num);
    }else if(str[0] == 'b'){ //A binary number
        uint64_t num = binToInt(str+1);
        detail(num);
    }else{ //A string
        uint64_t num = strToBitStream(str);
        detail(num);
    }
}

void mainLoop(){
    char* str = malloc(128);
    char* cmp = prompt(str); //Comp is str or NULL depending on the success of fget
    if(cmp == NULL)
        return;
    while(strcmp(str,"exit\n") && strcmp(str,":q\n") && strcmp(str,"")){
        processString(str);
        cmp = prompt(str);
        if(cmp == NULL)
            return;
    }
}

int main(int argc, char** argv){
    if(argc == 1)
        mainLoop();
    else if(argc == 2)
        processString(argv[1]);
    else
        manual();
    return 0;
}


