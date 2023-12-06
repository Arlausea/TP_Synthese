#include <unistd.h> //For EXIT_SUCCESS/FAILURE
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //For strlen
#include <fcntl.h> //For open/creat
#include <sys/wait.h>
#include <time.h> //To get command for clock_gettime




#define NANO_TO_MILLI(N) ((N)/ 1000000);
#define MAX_INPUT_SIZE 256

// File Descriptors
int terminal = STDOUT_FILENO; // Sending arguments to terminal
int fd_input = STDIN_FILENO;  // Getting arguments

int status;

// Input variable
char input[MAX_INPUT_SIZE];
int bytesRead;

char waitingPrompt[MAX_INPUT_SIZE] = "";
char exitSucesss[] = "\nEnd of ShellENSEA\nBye bye...\n";


struct timespec starttime, endtime;

int exit_signal_status;
double time_elapsed;



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
        execlp(input, input, NULL);
        exit(EXIT_SUCCESS);

    } else {
        wait(&status);
        

    }
}

void return_code(void){

    int sprintfvalue;
    time_elapsed = (endtime.tv_nsec-starttime.tv_nsec)/1e6;
    
    if (WIFEXITED(status)){
        exit_signal_status = WEXITSTATUS(status);
        sprintfvalue = sprintf(waitingPrompt, "enseash [exit:%d|%.0f ms] %% ",exit_signal_status,time_elapsed);
    }
    else if(WIFSIGNALED(status)){
        exit_signal_status = WTERMSIG(status);
        sprintfvalue = sprintf(waitingPrompt, "enseash [sign:%d|%.0f ms] %% ",exit_signal_status, time_elapsed);
    }
    
}

int main(int argc, char **argv) {

    shellDisplay();

    while (1) {

        return_code();
        write(terminal, waitingPrompt, sizeof(waitingPrompt)-1);

        bytesRead = read(fd_input, input, sizeof(input));
        input[bytesRead-1] = '\0'; //Removing the '\n' at the end
        clock_gettime(CLOCK_MONOTONIC, &starttime);
        command(input, bytesRead);
        clock_gettime(CLOCK_MONOTONIC, &endtime);

    }

    close(fd_input);
    close(terminal);
    return EXIT_SUCCESS;
}
