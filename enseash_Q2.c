#include <unistd.h> //For EXIT_SUCCESS/FAILURE
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //For strlen
#include <fcntl.h> //For open/creat
#include <sys/wait.h>


void main(int argc,char** argv){

    //Informational Messages

    char welcomeMessage[] = "Bienvenue dans le Shell ENSEA \nPour quitter, tapez 'exit'\n";
    char waitingPrompt[] = "enseash % ";


    //Variables

    //Files Descriptors
    int terminal = STDOUT_FILENO; //Send arguments to terminal
    int fd_input = STDIN_FILENO; //Get arguments

    //For fork
    int pid;
    int intputSize;
    int status;

    //Input variable
    char input[] = {0};
    char inputArgs[] = {0};

    //Main code
    write(terminal,welcomeMessage,strlen(welcomeMessage));
    write(terminal,waitingPrompt,strlen(waitingPrompt));

    pid = fork();
    if (pid == 0){ // Child code
        
        intputSize=read(fd_input,input,sizeof(input));
        while (strcmp(input,"\n")!=0){
            read(fd_input,input,sizeof(input));
        }
        execvp(input,NULL);
        exit(EXIT_FAILURE);
    }
    else{
        wait(&status);
        write(terminal,waitingPrompt,strlen(waitingPrompt));
    }


    exit(EXIT_SUCCESS);

}