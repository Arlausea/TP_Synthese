#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> 


//Macros 

#define NOT_ENOUGH_ARGS "Not enough arguments or too much arguments | Required : 3 arguments\n"
#define NO_FILE "File does not exist. Please repeat the process.\n"
#define NOT_REGULAR "Warning! File is not ordinary.\n"
#define NOT_HOST "Hostname not reachable. Please provide a new one"

//Files Descriptors

int terminal = STDOUT_FILENO;

struct stat sbFileInput;

void checkFormat(int argc, char ** argv){
    if (argc!=4){
        write(terminal,NOT_ENOUGH_ARGS,sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }


    //Theses points are verified only if we made a "put" request
    if (stat(argv[3], &sbFileInput) == -1 && strcmp(argv[1],"put") == 0){
        write(terminal,NO_FILE,sizeof(NO_FILE));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(sbFileInput.st_mode) && strcmp(argv[1],"put") == 0){
        write(terminal,NOT_REGULAR,sizeof(NOT_REGULAR));
        close(terminal);
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char ** argv){

    checkFormat(argc,argv);

    close(terminal);
    return 0;
}