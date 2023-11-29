#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
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

void shellDisplay(void) {
    //Informational Messages
    char welcomeMessage[] = "Welcome to ShellENSEA! \nType 'exit' to quit\n";
    
    //Displaying
    write(terminal,welcomeMessage,strlen(welcomeMessage));

}

void command(char input[]){
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

        command(input);

    }

    return EXIT_SUCCESS;
}
