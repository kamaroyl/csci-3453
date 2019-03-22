#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>


/*
 * GLOBALS
 ***********/
long ARG_MAX = 4096; //max length of input

// Delimiters
char spaceToken = " ";
char escapeToken = "\\";
char quoteToken = "\"";
char rightArrowToken = ">";
char leftArrowToken = "<";

// Tokens
char* exitString = "exit"


void getUserInput(char* inputPtr){
    fgets(inputPtr, ARG_MAX, stdin);
}

void printPromptTag() {
    printf("promptTag> ");
}


//null terminated argument array
void execute(){

}


/*input:
 *    char* input - first string in the input
 *output:
 *    char representation of boolean
 * Take tokenized string and check for exit command. 
 * 
 ********/
char checkUserInputForExit(char* inputPtr) {
    for(int i = 0; i < 4; i++) {
        if( inputPtr[i] != exitString[i] ) return 0;
    }
    return 1;
} 

void tokenizeUserInput(char* inputPtr, char** ) {
    char* token
    while(index != length) {
        switch(inputPtr[index]) {

        }
    }
}

int main() {
    char input[ARG_MAX];
    char running = 1;
    while (running == 1) {
        printPromptTag();
        getUserInput(input);
        tokenizeUserInput(input);
        printf("%s", input);
        running = checkUserInputForExit();
    }
    return 0; //exit successfully
}
