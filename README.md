# LAB - ENSEA in the Shell

## Objective

The primary goal of this practical work is to create a micro shell for launching commands and displaying information about their execution.

### Step 1 - Displaying a welcome message, followed by a simple prompt

To display a message on the terminal, we use a file descriptor:
```c
int terminal = STDOUT_FILENO;
```
We then use the 'write()' function, taking the file descriptor and the string we want to display.
```c
write(terminal,welcomeMessage,strlen(welcomeMessage));
```
Don't forget to close the file descriptors.
```c
close(terminal);
```

### Step 2 - Execution of the entered command and return to the prompt

#### 2.a Reading the entered command.
To read entered commands from the prompt, we use the 'read()' function, taking the file descriptor based on inputs:
```c
bytesRead = read(fd_input, input, sizeof(input));
```
The input accounts for the line break, which needs removal in the input buffer to allow command execution.
```c
input[bytesRead-1] = '\0';
```

#### 2.b Execution of a simple command (without arguments).

The 'command()' function uses the fork process to execute commands. The execution and return to the prompt are managed by 'execlp()'.


#### 2.c Returning to the prompt "enseash %" and waiting for the next command.
The infinite loop allows the shell to display "enseash %" and wait for another prompt each time a command is executed.

### Step 3 - Handling the shell exit with the "exit" command or "Ctrl+d"
Within the 'command()' function, we add a condition allowing us to exit the program when either "exit" or "Ctrl+d" is used.
```c
if(strcmp(input,"exit") == 0 || bytesRead == 0){   
        write(terminal,exitSucesss,sizeof(exitSucesss));
        exit(EXIT_SUCCESS);

    };
```
"exit" is managed by a string comparison (strcmp), while the "Ctrl+d" management is based on the size of the buffer.

### Step 4 - Displaying the return code (or signal) of the previous command in the prompt
We use the 'sprintf()' function, formatting a string with the value of our exit code (similarly for the signal code).
```c
if (WIFEXITED(status)){
    exit_signal_status = WEXITSTATUS(status);
    sprintfvalue = sprintf(waitingPrompt, "enseash [exit:%d] %% ",exit_signal_status);
}
```
### Step 5 - Measurement of the command execution time using the call clock_gettime
We can enhance the previous code by displaying the elapsed time using the "clock_gettime" function from the time library. This function serves as a timestamp to calculate $\Delta t$.
```c
    if (WIFEXITED(status)){
        exit_signal_status = WEXITSTATUS(status);
        sprintfvalue = sprintf(waitingPrompt, "enseash [exit:%d|%.0f ms] %% ",exit_signal_status,time_elapsed);
    }
```
time_elapsed in milliseconds is calculated by using this formula :
$\Delta t_{ms} = \Delta t_s+\frac{\Delta t_{ns}}{1\times10^{6}}$
### Step 6 - Execution of a complex command (with arguments)
To provide multiple arguments to our terminal, we use the 'strtok()' function inside the child code to split our input into words according to spaces:
```c
char *token = strtok(input, " ");
```
We then store these words in an array 'args', and append a null pointer at the end of the array to prepare for command execution by replacing the 'execlp' function with the 'execvp' function.
### Step 7 - Management of redirections to stdin and stdout with ’<’ and ’>’ 
Coming soon...