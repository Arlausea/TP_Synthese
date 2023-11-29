#include <unistd.h> //For EXIT_SUCCESS/FAILURE
#include <stdlib.h>
#include <stdio.h>
#include <string.h> //For strlen
#include <fcntl.h> //For open/creat


void main(int argc,char** argv){

    //Informational Messages
    char welcomeMessage[] = "Bienvenue dans le Shell ENSEA \nPour quitter, tapez 'exit'\n";
    char waitingPrompt[] = "enseash %\n";


    //Variables

    //Files descriptors
    int terminal = STDOUT_FILENO; //Sending arguments to terminal


    //Displaying
    write(terminal,welcomeMessage,strlen(welcomeMessage));
    write(terminal,waitingPrompt,strlen(waitingPrompt));

    exit(EXIT_SUCCESS);

}