#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

void prompt(char* str){
    printf(">");
    fgets(str, 1000, stdin);
}

void detail(uint64_t num){
    printf("ASCII : %c\n"
           "décimal : %i\n"
           "héxadécimal : %x\n"
           "----------------------------\n"
           ,(char) num, num, num);
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

