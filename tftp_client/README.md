# LAB - TFTP Client

## Objective

The main objective of this practical work is to create a client program capable of exchanging files using the Trivial File Transfer
Protocol (TFTP).

### Step 0 - Server Testing

We test the server connection by entering the following command in a terminal: 

```shell
tftp srvtpinfo1.ensea.fr
``` 

Afterwards, we can verify if the connection was successful by retrieving a test file stored on the server.
```
tftp> get test.txt
```

![](img/package.png)

We got the sequence:
```
00 01 74 65 73 74 6e 74 78 74 00 6e 65 74 61 73 63 69 69 00"
```
![](img/doc.png)

According to the documentation, our structure provides the following informations:

* Opcode: 00 01 (Read request - RRQ)
* Filename: 74 65 73 74 6e 74 78 74 00 (ASCII representation of "test.txt" followed by a null terminator)
* 0: Null byte as a separator
* Mode: 6e 65 74 61 73 63 69 69 00 (ASCII representation of "netascii" followed by a null terminator)

### Step 1 - Using command-line arguments for the gettftp and puttftp programs to obtain request information (server and file).

We begin by checking that the entered command lines are in the correct format : 

* We verify that the number of arguments is the expected value.
* We check if the file exists.
* We confirm that the file is a regular file.

### Step 2 - Calling getaddrinfo to obtain the server’s address.



### Step 3 - Reserve a connection socket to the server.


### Step 4 - Gettftp management


#### 4.a Build a properly formed Read Request (RRQ) and send it to the server


#### 4.b Receive a file consisting of a single Data (DAT) packet and its acknowledgment (ACK).


#### 4.c Receive a file consisting of multiple Data (DAT) packets and their respective acknowledgments (ACK).


### Step 5 - Puttftp management


#### 5.a Build a properly formed Write Request (WRQ) and send it to the server


#### 5.b Receive a file consisting of a single Data (DAT) packet and its acknowledgment (ACK).


#### 5.c Receive a file consisting of multiple Data (DAT) packets and their respective acknowledgments (ACK).
