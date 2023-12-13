#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <memory.h>


// Information about Hostname & Filename

    char hostname[128];
    char servername[128];
    char fileName[128];
    char ipAdress[128];

// Macros

#define NOT_ENOUGH_ARGS "Not enough arguments or too much arguments | Required : 3 arguments\n"
#define NO_FILE "File does not exist. Please repeat the process.\n"
#define NOT_REGULAR "Warning! File is not ordinary.\n"
#define ERROR_STAT "Status error :"

#define PORT "69"


// Files Descriptors

int terminal = STDOUT_FILENO;
struct stat sbFileInput;

// Addrinfo

struct addrinfo hints;
struct addrinfo * result = 0;
int status;


void checkFormat(int argc, char ** argv){
    if (argc!=4){
        write(terminal,NOT_ENOUGH_ARGS,sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[3],&sbFileInput) == -1){
        write(terminal,NO_FILE,sizeof(NO_FILE));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(sbFileInput.st_mode)){
        write(terminal,NOT_REGULAR,sizeof(NOT_REGULAR));
        close(terminal);
        exit(EXIT_FAILURE);
    }
}

void getInfo(char * hostname,struct addrinfo hints){

    memset(&hints,0,sizeof(hints));

    hints.ai_protocol=IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family=AF_INET;
    getaddrinfo(hostname,PORT,&hints,&result);
    // if(status = getaddrinfo(hostname,PORT,&hints,&result) != 0){
    //     write(terminal,ERROR_STAT,sizeof(ERROR_STAT));
    //     write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
    //     write(terminal,"\n",sizeof("\n"));
    //     exit(EXIT_FAILURE);
    // }
    struct addrinfo* current;
    current = result;

    while(current!=NULL){
        status = getnameinfo(current->ai_addr,current->ai_addrlen,hostname,128,servername,128,NI_NUMERICHOST | NI_NUMERICSERV);

        if(status !=0){
            write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
            write(terminal,"\n",sizeof("\n"));
        }
        write(terminal,hostname,sizeof(hostname));
        write(terminal,"\n",sizeof("\n"));
        //printf("Host : %s  Server %s \n",bufferHostName,bufferServerName);
        
        // printf("Found one answer : \t ai_family=%d \t ai_socktype=%d \t ai_protocol=%d \n",current->ai_family,current->ai_socktype,current->ai_protocol);
        

        current=current->ai_next;
    }
}


int main(int argc,char ** argv){

    checkFormat(argc,argv);

    getInfo(argv[2],hints);

    close(terminal);
    return 0;
}