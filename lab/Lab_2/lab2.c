#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
/*
 *  Benjamin Straub
 *  csci 3453
 *  04/05/2019
 * 
 */


/*
 * GLOBALS
 ***********/
extern char **environ;
char** PATH = NULL;
int* PATH_LENGTH = NULL;
char OVERRIDE_IN = 0; //bool should redirect stdin
char* IN_PATH = NULL;
char OVERRIDE_OUT = 0; //bool should redirect stdout
char* OUT_PATH = NULL;
long ARG_MAX = 4096; //max length of input
int PATH_MAX = 512; // max length of path

// Delimiters
char colonToken = ':';
char spaceToken = ' ';
char escapeToken = '\\';
char quoteToken = '"';
char rightArrowToken = '>';
char leftArrowToken = '<';
char NUL = '\0';

// Tokens
char* exitString = "exit";


// Utils

/*
 *    strtok mangles the input string. Instead of copying to a new string and mangling that string
 *    lets copy the values to a new array. 
 *    return will need to be freed
 *    Used to parse the path and throw it into a global variable
 */
char** stringToArray(char delim, char* stringToTokenize, int* length) {
    int numberOfSubstrings = 1;
    int i = 0;
    int j = 0;
    int start = 0;
    char** tokenizedString;
    
    while(stringToTokenize[i] != NUL) {
        if(stringToTokenize[i] == delim) numberOfSubstrings++;
        i++;
    }

    tokenizedString = (char**) malloc((numberOfSubstrings + 1) * sizeof(char*));

    for(i = 0; i < numberOfSubstrings; i++) {
        int tmp = 0;
        while(stringToTokenize[j] != delim && stringToTokenize[j] != NUL) {
            j++;
            tmp++;
        }

        tokenizedString[i] = (char*) malloc((tmp + 2) * sizeof(char));

        for(int k = 0; k < tmp; k++) {
            tokenizedString[i][k] = stringToTokenize[start + k];
        }
        tokenizedString[i][tmp + 1] = NUL;
        j++;
        start = j;
    }
    
    *length = numberOfSubstrings;
    return tokenizedString;    
}

/*
 *   Frees the entries of array (char*s) but not the array (char**) or the length (int*)
 */
void freeStringArray(char** stringArray, int* length) {
    for(int i = 0; i < *length; i++) {
        free(stringArray[i]);
    }
}
//

void getUserInput(char* inputPtr){
    char tmpInput[ARG_MAX];
    char* tmpInputPtr = tmpInput;
    fgets(tmpInputPtr, ARG_MAX, stdin);
    int length = strlen(tmpInputPtr);
    int i = 0;
    int j = 0;
    while(tmpInput[i] == ' ' || tmpInput[i] == '	') i++;
    for(; j < length - i - 1; j++) {
        inputPtr[j] = tmpInputPtr[j + i];
    }
    inputPtr[j] = '\0';
}

void printPromptTag() {
    printf("promptTag> ");
}

void savePath() {
    char* pathEnv = getenv("PATH");
    PATH_LENGTH = malloc(sizeof(int));
    PATH = stringToArray(colonToken, pathEnv, PATH_LENGTH);
} 

void freePath() {
    freeStringArray(PATH, PATH_LENGTH);
    free(PATH_LENGTH);
    free(PATH);
}

char* makeFullFilePath(char* programName) {
    char* fullFilePath = NULL;
    
    //strncpy had weird behavor, just implement it for ease sake.
    for(int j = 0; j < *PATH_LENGTH; j++) {
        int subpathLength = strlen(PATH[j]);

        //length of path part + length path char + lenth of program name + length null terminator
        int fullPathLength = subpathLength + 1 + strlen(programName) + 1;
        fullFilePath = malloc(fullPathLength);
        int i = 0;
        //copy subPath to fullPath
        for(; i < subpathLength; i++) {
            fullFilePath[i] = PATH[j][i];
        } 

        //copy file delim to full file Path
        fullFilePath[i] = '/';
        i++;


        // Copy program Name onto full file Path
        int j = 0;
        for(; i < fullPathLength; i++) {
            fullFilePath[i] = programName[j];
            j++;
        }
        
        if(access(fullFilePath, X_OK) != -1) {
            break;
        } else {
           // printf("%s is not an executable file\n", fullFilePath);
            free(fullFilePath);
            fullFilePath = NULL;
        }
    }

    if( fullFilePath == NULL ) {
        printf("no executable found!\n");
    }

    return fullFilePath;
}


/*
 *Input:
 *    program - name of the program to execute
 *    arguments - the arguments to the program to be executed
 *
 *Output:
 *    pid int - the pid of the process that is executing
 *
 *Description:
 *    this function spins off a new process and executes the binary specified by program with arguments
 ********/
int execute(char* program, char** arguments){
    int status;
    int pid = fork();
    int errorOccurred = 0;
    if(pid < 0) {
        printf("failed to create process\n");
    } else if(pid == 0) {
        /* CHILD */
        //https:/stackoverflow.com/questions/11515399/implementing-shell-in-c-and-need-help-handling-input-output-redirection//
        if(OVERRIDE_IN) {
            int fdIn = open(IN_PATH, O_RDONLY);
            int tmperr = errno;
            if(fdIn < 0) { 
                fprintf(stderr,  "failed to open fd: %s error: %d\n", IN_PATH, tmperr);
                errorOccurred = 1;
            } else {
                dup2(fdIn, STDIN_FILENO);
                close(fdIn);
            }
          
                OVERRIDE_IN = 0;
        }
        
        if(OVERRIDE_OUT) {
            int fdOut = creat(OUT_PATH, 0664);
            int tmperr = errno;
            if(fdOut < 0) fprintf(stderr, "failed to creat path: %s error %d", OUT_PATH, tmperr);
            dup2(fdOut, STDOUT_FILENO);
            close(fdOut);
            OVERRIDE_OUT = 0;
        }
        if(errorOccurred == 0) {
            execve(program, arguments, environ);
        } else {
            exit(1);
        }
    } else {
        /* PARENT */
        wait(&status);
        if(status != 0) printf("Child process failed\nStatusCode: %d\n", status);
    }
    return pid;
}

/*input:
 *    char* path - string representing the full path
 *
 *output: 
 *    void
 *
 *description:
 *    Changes the current working directory and sets the PWD path variable 
 *********/
void changeDir(char* path) {
    struct stat statStruct;
    
    if(stat(path, &statStruct) == 0 && S_ISDIR(statStruct.st_mode)) {
        //printf("Confirmed path is a directory\n");
        int status = chdir(path);
        setenv("PWD", path, 1);
        if(status != 0) {
            printf("Could not change directory\n");
        }
    } else {
        printf("No Such directory: %s\n", path);
    }
}


/*
 *Input:
 *    a pointer to the path we're moving to. Can be empty
 *
 *Output:
 *    a pointer to the absolute path in a malloc'd string.
 *
 *Description:
 *    gets the appropriate absolute path for a path. The return _must_ be freed
 *    handles relative pathing as well as absolute pathing and an empty string.
 */
char* getAbsolutePath(char* path) {

    char* absolutePath; // always return a malloc'd string so we can manage memory (always free)

    int pathLength = strlen(path);
    if(pathLength == 0) { //Empty Path - go to home

        char* home = getenv("HOME");
        pathLength = strlen(home);
        absolutePath = malloc(sizeof(char) * pathLength);
        for(int i = 0; i < pathLength; i++) absolutePath[i] = home[i];

    } else if(path[0] == '/') { //we're using a absolute path

        absolutePath = malloc(sizeof(char) * pathLength);
        for(int i = 0; i < pathLength; i++) absolutePath[i] = path[i];

    } else { //relative path

        char cwdBuffer[PATH_MAX];
        getcwd(cwdBuffer, PATH_MAX);
        int cwdLength = strlen(cwdBuffer);
  
        if(path[0] == '.' && path[1] == '.') { //go up one directory

            pathLength -= 2; //removed dots
            while(cwdBuffer[cwdLength] != '/') cwdLength--; //back up to the previous path
            absolutePath = malloc(sizeof(char) * (cwdLength + 1 + pathLength)); // current Working dir + / + path - ..
            for(int j = 0; j < cwdLength; j++) {
                absolutePath[j] = cwdBuffer[j];
            }
            
            if(pathLength - 2 > 0) {
                absolutePath[cwdLength] = '/';
                for(int j = 0; j < pathLength; j++) absolutePath[j + cwdLength + 1] = path[j];
            }

        } else {

            absolutePath = malloc(sizeof(char) * (cwdLength + 1 + pathLength)); // current working dir + / + path
            for(int j = 0; j < cwdLength; j++) absolutePath[j] = cwdBuffer[j];
            absolutePath[cwdLength] = '/';
            for(int j = 0; j < pathLength; j++) absolutePath[j + cwdLength + 1] = path[j];

        }
    }
    return absolutePath;
}

/*
 */
void cd(char* path) {
    char* absolutePath = getAbsolutePath(path);
    changeDir(absolutePath);
    free(absolutePath);
}

/*
 *Check if input is a change directory call
 */
char commandIsCD(char* command) {
    if(command[0] == 'c' && command[1] == 'd') return 1;
    return 0;
}

void checkUserInputForRedirectIn(char* inputPtr) {
    int length = strlen(inputPtr);
    int i = 0;
    int j = 0;

    while(inputPtr[i] != NUL) {
        if(inputPtr[i] == '<') {
            OVERRIDE_IN = 1;
            inputPtr[i] = NUL;
            int k = i - 1;
            while(inputPtr[k] == ' ' || inputPtr[k] == '	') {
                inputPtr[k] = NUL; //stop from running into an error where command is being passed empty string
                k--;
            }
            i++;
            break;
        }
        i++;
    }
    while(inputPtr[i] == ' ' || inputPtr[i] == '	') i++; //strip spaces so we don't get a strange string for fd opening
    IN_PATH = malloc((length - i) * sizeof(char));
    for(; i < length; i++) {
        if(inputPtr[i] == ' ' || inputPtr[i] == '	') {
            IN_PATH[j] = NUL;
            break;
        }
        IN_PATH[j] = inputPtr[i];
        j++;
    }
}

void checkUserInputForRedirectOut(char* inputPtr) {
    int length = strlen(inputPtr);
    int i = 0;
    int j = 0;
    while(inputPtr[i] != NUL) {
        if(inputPtr[i] == '>') {
            OVERRIDE_OUT = 1;
            inputPtr[i] = NUL;
            int k = i - 1;
            while(inputPtr[k] == ' ' || inputPtr[k] == '	') {
                inputPtr[k] = NUL;
                k--;
            }
            i++;
            break;
        }
        i++;
    }
    while(inputPtr[i] == ' ' || inputPtr[i] == '	') i++;
    OUT_PATH = malloc((length - i) * sizeof(char));
    for(; i < length; i++) {
        if(inputPtr[i] == ' ' || inputPtr[i] == '	') {
            OUT_PATH[j] = NUL;
            break;
        }
        OUT_PATH[j] = inputPtr[i];
        j++;
    }
}

void freeRedirects() {
    if(IN_PATH != NULL) { 
        free(IN_PATH);
        IN_PATH = NULL;
    }

    if(OUT_PATH != NULL) {
        free(OUT_PATH);
        OUT_PATH = NULL;
    }
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
        if( inputPtr[i] != exitString[i] ) {
            return 0;
        }
    }
    return 1;
} 

/*
 * 
 *Check if the input string contains no characters or is only whitespace
 *****************/
char userInputIsEmpty(char* input) {
    if(strlen(input) == 0) return 1;
    return 0;
}

/*
 *Input:
 *    User input string, and a pointer to a length
 *Output:
 *    a malloc'd array of char* 
 * Ran into too many issues using strtok, instead parse string into array yourself
 */
char** s2a(char* stringVal, int* len) {
    char** stringArray;
    char delim = ' ';
    int numberOfSubstrings = 1;
    int i = 0;
    int j = 0;
    int start = 0;
    
    while(stringVal[i] != '\0') {
        if(stringVal[i] == delim) {
            if(stringVal[i + 1] != delim) numberOfSubstrings++;
        }
        i++;
    }
    
    stringArray = (char**) malloc((numberOfSubstrings + 2) * sizeof(char*));

    for(i = 0; i < numberOfSubstrings; i++) {
        int tmp = 0;
        while(stringVal[j] != delim && stringVal[j] != '\0') {
            j++;
            tmp++;
        }
        stringArray[i] = (char*) malloc((tmp + 1) * sizeof(char));
        for(int k = 0; k < tmp; k++) { 
            stringArray[i][k] = stringVal[start + k];
        }
        stringArray[i][tmp] = '\0';
        j++;
        start = j; 
    }
    //stringArray[numberOfSubstrings + 1] = malloc(sizeof(NULL));
    stringArray[numberOfSubstrings + 1] = NULL;
    *len = numberOfSubstrings;
    return stringArray;
}


/*
 *Input:
 *    length - number of initialized strings
 *    tokenizedInput - the array of strings
 *
 *Output:
 *    void
 *
 *Description:
 *    utility function to free the memory allocated for the string array
 */
void freeTokenizedInput(int length, char** tokenizedInput) {
    int index = 0;
    for(; index <= length; index++) {
        free(tokenizedInput[index]);
    }
}

int main() {
    if(getpid() > 0) { // if main process
        savePath();
        char input[ARG_MAX];
        char* inputPtr = input;
        int tokenizedInputLength;
        int usedTokenizedInputLength;
        char** tokenizedInput;
        char running = 1;

        while(1) {
            printPromptTag();
            getUserInput(inputPtr);
            
            //if User  input is empty, print new line and start loop again
            if(userInputIsEmpty(inputPtr)) {
                printf("\n");
                continue;
            }

            //check if we should exit
            if(checkUserInputForExit(inputPtr)) {
                break;
            }
            
            // Check and set redirect in/out - out before in < >
            checkUserInputForRedirectOut(inputPtr);
            checkUserInputForRedirectIn(inputPtr);

            int* tokenArrayLength = malloc(sizeof(int*));

            tokenizedInput = s2a(inputPtr, tokenArrayLength);
            if(commandIsCD(inputPtr)) {
                cd(tokenizedInput[1]);
            } else {
                char* fullFilePath = makeFullFilePath(tokenizedInput[0]); 
                if(execute(fullFilePath, tokenizedInput) == 0){
                    return 0;
                }
                free(fullFilePath);    
            }
        
            //Free all used memory!!!!
            freeRedirects();
            freeTokenizedInput(*tokenArrayLength, tokenizedInput);
            free(tokenizedInput); 
            free(tokenArrayLength);
            memset(input, 0, ARG_MAX);     
        }
        printf("exiting\n");
        freePath();
    }
    
    return 0; //exit successfully
}
