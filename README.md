# LAB - ENSEA in the Shell

## Objective

The main objective of this practical work is to create a micro shell, used to launch commands and display information about their execution.

### Step 1 - Displaying a welcome message, followed by a simple prompt

To display a message on our terminal, we are using a file descriptor:
```
int terminal = STDOUT_FILENO;
```
Then we are using the 'write()' function, which takes our file descriptor and the string we want to display.
```
write(terminal,welcomeMessage,strlen(welcomeMessage));
```
We do not forget to close the file descriptors.
```
close(terminal);
```

### Step 2 - Execution of the entered command and return to the prompt

#### 2.a Reading the entered command.
In order to read the commands entered on the prompt we are using the 'read()' function, which will take the file descriptor based on inputs :
```
bytesRead = read(fd_input, input, sizeof(input));
```
The input takes into account the line break, which needs to be removed in the input buffer to allow our command to execute.
```
input[bytesRead-1] = '\0';
```

#### 2.b Execution of a simple command (without arguments).

The 'command()' function use fork process to execute commands. The excecution and the return to the prompt are managed by 'excelp()'.


#### 2.c Returning to the prompt "enseash %" and waiting for the next command.
The infinite loop allows the shell to display "enseash %" and waiting another prompts each time a command is executed.

### Step 3 - Handling the shell exit with the "exit" command or "Ctrl+d"
Within the 'command()' function, we add a condition that allows us to exit the program when either "exit" or "Ctrl+d" is used.
```
if(strcmp(input,"exit") == 0 || bytesRead == 0){   
        write(terminal,exitSucesss,sizeof(exitSucesss));
        exit(EXIT_SUCCESS);

    };
```
"exit" is managed by a string comparison (strcmp), where the "Ctrl+d" management is made with the size of the buffer.

### Step 4 - Displaying the return code (or signal) of the previous command in the prompt
We are using the 'sprintf()' functions, the principle of which is to format a string with the value of our exit code (the same thing is made for the signal code).
```
if (WIFEXITED(status)){
    exit_signal_status = WEXITSTATUS(status);
    sprintfvalue = sprintf(waitingPrompt, "enseash [exit:%d] %% ",exit_signal_status);
}
```
### Step 5 - Measurement of the command execution time using the call clock_gettime

### Step 6 - Execution of a complex command (with arguments)

### Step 7 - Management of redirections to stdin and stdout with ’<’ and ’>’ 

### Step 8 - Management of pipe redirection with ‘|’

### Step 9 - Return to the prompt immediately with ‘&’ (execution of programs in the background)