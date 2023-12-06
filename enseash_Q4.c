#include <unistd.h> //For EXIT_SUCCESS/FAILURE
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //For strlen
#include <fcntl.h> //For open/creat
#include <sys/wait.h>

#define MAX_INPUT_SIZE 256

// File Descriptors
int terminal = STDOUT_FILENO; // Sending arguments to terminal
int fd_input = STDIN_FILENO;  // Getting arguments

int status;


// Input variable
char input[MAX_INPUT_SIZE];
int bytesRead;

char waitingPrompt[] = "enseash % ";
char exitSucesss[] = "End of ShellENSEA\nBye bye...\n";
char codeExit1[] = "[exit:";
char codeExit2[] = "]";
char SignalExit[] = "[sign";
char SignalExit2[] = "]";

void shellDisplay(void) {
    //Informational Messages
    char welcomeMessage[] = "Welcome to ShellENSEA! \nType 'exit' to quit\n";
    
    //Displaying
    write(terminal,welcomeMessage,strlen(welcomeMessage));

}

void command(char input[], int bytesRead){
    if(strcmp(input,"exit") == 0 || bytesRead == 0){   //Enter in if exit or ctrl+d
        write(terminal,exitSucesss,sizeof(exitSucesss));
        exit(EXIT_SUCCESS);

    }

    pid_t pid = fork();

    if (pid <= -1) {

        exit(EXIT_FAILURE);

    } else if (pid == 0) { // Child code
        execlp(input,input,NULL);   
        exit(EXIT_SUCCESS);

    } else {
        wait(&status);


    }
}



int main(int argc, char **argv) {

    shellDisplay();

    while (1) {

        write(terminal, waitingPrompt, sizeof(waitingPrompt)-1);

        bytesRead = read(fd_input, input, sizeof(input));
        input[bytesRead-1] = '\0'; //Removing the '\n' at the end

        command(input, bytesRead);

        if (WIFEXITED(status)){
            //write(terminal,codeExit1,sizeof(codeExit1));
            write(terminal,(int)WEXITSTATUS(status),sizeof(WEXITSTATUS(status)));
            //write(terminal,codeExit2,sizeof(codeExit2));
        }
        else if(WIFSIGNALED(status)){
            write(terminal,(int)WTERMSIG(status),sizeof(WTERMSIG(status)));
        }

    }

    close(fd_input);
    close(terminal);
    return EXIT_SUCCESS;
}
