#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h> 
#include <memory.h>
#include <errno.h>

// Macros
#define NOT_ENOUGH_ARGS "Not enough arguments or too many arguments | Required: 3 arguments\n"
#define NO_FILE "File does not exist. Please repeat the process.\n"
#define NOT_REGULAR "Warning! File is not ordinary.\n"
#define ERROR_STAT "Status error:"

#define IP_SHOW "Communication with: "
#define PORT_SHOW ":"
#define PORT "69"
#define MAX_CHAR_SIZE 128

#define ERROR_SOCKET "Error creating socket: "
#define ERROR_CONNECTION "Error connecting to the socket: "

// Information about Hostname & Filename
char bufferServerName[MAX_CHAR_SIZE];
char fileName[MAX_CHAR_SIZE];
char ipAdress[MAX_CHAR_SIZE];

// Files Descriptors
int terminal = STDOUT_FILENO;
struct stat sbFileInput;
int socketDescriptor;

// Addrinfo
struct addrinfo hints;
struct addrinfo *result = NULL;
int status;

void checkFormat(int argc, char **argv) {
    if (argc != 4) {
        write(terminal, NOT_ENOUGH_ARGS, sizeof(NOT_ENOUGH_ARGS));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (stat(argv[3], &sbFileInput) == -1) {
        write(terminal, NO_FILE, sizeof(NO_FILE));
        close(terminal);
        exit(EXIT_FAILURE);
    }

    if (!S_ISREG(sbFileInput.st_mode)) {
        write(terminal, NOT_REGULAR, sizeof(NOT_REGULAR));
        close(terminal);
        exit(EXIT_FAILURE);
    }
}

void getInfo(char *hostname, struct addrinfo hints) {
    memset(&hints, 0, sizeof(hints));
    hints.ai_protocol = IPPROTO_UDP;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_family = AF_INET;

    // Call getaddrinfo to obtain the server's address
    if ((status = getaddrinfo(hostname, PORT, &hints, &result)) != 0) {
        write(terminal, ERROR_STAT, sizeof(ERROR_STAT));
        write(terminal, gai_strerror(status), sizeof(gai_strerror(status)));
        write(terminal, "\n", sizeof("\n"));
        exit(EXIT_FAILURE);
    }

    status = getnameinfo(result->ai_addr, result->ai_addrlen, ipAdress, MAX_CHAR_SIZE, bufferServerName, MAX_CHAR_SIZE, NI_NUMERICHOST | NI_NUMERICSERV);

    if (status != 0) {
        write(terminal, gai_strerror(status), sizeof(gai_strerror(status)));
        write(terminal, "\n", sizeof("\n"));
    }

    // Show the result
    write(terminal, IP_SHOW, sizeof(IP_SHOW));
    write(terminal, ipAdress, strlen(ipAdress));
    write(terminal, PORT_SHOW, sizeof(PORT_SHOW));
    write(terminal, bufferServerName, strlen(bufferServerName));
    write(terminal, "\n", sizeof("\n"));
}

void reservSocket(struct addrinfo *res) {
    socketDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (socketDescriptor == -1) {
        write(terminal, ERROR_SOCKET, sizeof(ERROR_SOCKET));
        perror("socket error:");
        close(socketDescriptor);  //In case of failure
        exit(EXIT_FAILURE);
    }

    if ((connect(socketDescriptor, res->ai_addr, res->ai_addrlen)) < 0) {
        write(terminal, ERROR_CONNECTION, sizeof(ERROR_CONNECTION));
        perror("connect error:");
        close(socketDescriptor);  
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv) {
    checkFormat(argc, argv);

    getInfo(argv[2], hints);
    reservSocket(result);

    freeaddrinfo(result);
    close(socketDescriptor);
    close(terminal);
    return 0;
}
