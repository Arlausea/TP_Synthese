#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <memory.h>
#include <errno.h>


// Information about Hostname & Filename

    char bufferServerName[128];
    char fileName[128];
    char ipAdress[128];

    char * errorMessage;

// Macros

#define NOT_ENOUGH_ARGS "Not enough arguments or too much arguments | Required : 3 arguments\n"
#define NO_FILE "File does not exist. Please repeat the process.\n"
#define NOT_REGULAR "Warning! File is not ordinary.\n"
#define ERROR_STAT "Status error :"

#define IP_SHOW "Communication with : "
#define PORT_SHOW ":"
#define PORT "69"

#define ERROR_SOCKET "Error socket : "
#define ERROR_CONNECTION "Error connection with the socket : "

// Files Descriptors

int terminal = STDOUT_FILENO;
struct stat sbFileInput;
int socketDescriptor;

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
    if(status = getaddrinfo(hostname,PORT,&hints,&result) != 0){
        write(terminal,ERROR_STAT,sizeof(ERROR_STAT));
        write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
        write(terminal,"\n",sizeof("\n"));
        exit(EXIT_FAILURE);
    }
    status = getnameinfo(result->ai_addr,result->ai_addrlen,ipAdress,128,bufferServerName,128,NI_NUMERICHOST | NI_NUMERICSERV);

    if(status !=0){
        write(terminal,gai_strerror(status),sizeof(gai_strerror(status)));
        write(terminal,"\n",sizeof("\n"));
    }

    // Show the result
    write(terminal,IP_SHOW,sizeof(IP_SHOW));
    write(terminal,ipAdress,strlen(ipAdress));
    write(terminal,PORT_SHOW,sizeof(PORT_SHOW));
    write(terminal,bufferServerName,strlen(bufferServerName));
    write(terminal,"\n",sizeof("\n"));
}


void reservSocket(struct addrinfo * res){

    if (socketDescriptor = socket(res->ai_family,res->ai_socktype,res->ai_protocol) == -1 ){
        write(terminal,ERROR_SOCKET,sizeof(ERROR_SOCKET));
        errorMessage = strerror(errno);
        write(terminal,errorMessage,strlen(errorMessage));
        write(terminal,"\n",sizeof("\n"));
        exit(EXIT_FAILURE);
    } 
    if(connect(socketDescriptor,res->ai_addr,res->ai_addrlen) == -1){
        write(terminal,ERROR_CONNECTION,sizeof(ERROR_CONNECTION));
        errorMessage = strerror(errno);
        write(terminal,errorMessage,strlen(errorMessage));
        write(terminal,"\n",sizeof("\n"));
        exit(EXIT_FAILURE);
    }
}


int main(int argc,char ** argv){

    checkFormat(argc,argv);

    getInfo(argv[2],hints);
    reservSocket(result);

    freeaddrinfo(result);
    close(socketDescriptor);
    close(terminal);
    return 0;
}