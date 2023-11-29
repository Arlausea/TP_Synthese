#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> //For perror
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 256

int main(int argc, char **argv) {
    // Informational Messages
    char welcomeMessage[] = "Bienvenue dans le Shell ENSEA \nPour quitter, tapez 'exit'\n";
    char waitingPrompt[] = "enseash % ";
    char exitSucesss[] = "End of the ENSEA Shell\n Bye bye ...\n";


    // File Descriptors
    int terminal = STDOUT_FILENO; // Sending arguments to terminal
    int fd_input = STDIN_FILENO;  // Getting arguments

    int status;

    // Input variable
    char input[MAX_INPUT_SIZE];
    int bytesRead;

    // Main code
    write(terminal, welcomeMessage, sizeof(welcomeMessage)-1);

    while (1) {
        write(terminal, waitingPrompt, sizeof(waitingPrompt)-1);

        bytesRead = read(fd_input, input, sizeof(input));
        input[bytesRead-1] = '\0';

        //write(terminal,input,sizeof(input));
        
        if(strcmp(input,"exit")==0 || bytesRead==0){ //Enter in if exit or ctrl+d
            write(terminal,exitSucesss,sizeof(exitSucesss));
            exit(EXIT_SUCCESS);
        }

        pid_t pid = fork();

        if (pid <= -1) {

            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Child code
            execlp(input,input,NULL);
            perror("Command not found");
            exit(EXIT_FAILURE);
        } else {
            wait(&status);
        }
    }

    return EXIT_SUCCESS;
}
