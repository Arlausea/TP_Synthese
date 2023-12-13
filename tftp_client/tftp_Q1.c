#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> 


// Information about Hostname & Filename

    char * hostname;
    char * fileName;
    char * ipAdress;

// Defined messages

#define NOT_ENOUGH_ARGS "Not enough arguments or too much arguments | Required : 2 arguments\n"
#define NO_FILE "File does not exist. Please repeat the process.\n"
#define NOT_REGULAR "Warning! File is not ordinary.\n"
#define NOT_HOST "Hostname not reachable. Please provide a new one"

// Files Descriptors

int terminal = STDOUT_FILENO;
struct stat sbFileInput;


void checkFormat(int argc, char ** argv){
    if (argc!=3){
        write(terminal,NOT_ENOUGH_ARGS,sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[2],&sbFileInput) == -1){
        write(terminal,NO_FILE,sizeof(NO_FILE));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(sbFileInput.st_mode)){
        write(terminal,NOT_REGULAR,sizeof(NOT_REGULAR));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    // Don't work for now I think
    if (execlp("ping",argv[1],"-c","1",NULL) != 2){
        write(terminal,NOT_HOST,sizeof(NOT_HOST));
        exit(EXIT_FAILURE);
    }


}

int main(int argc,char ** argv){

    checkFormat(argc,argv);




    close(terminal);
    return 0;
}