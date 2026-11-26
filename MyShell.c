#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) 
{
    char *input = NULL; // Pointer to hold input
    size_t len = 0; //size of input buffer

    while(1)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s> ", cwd); // Display current working directory as prompt
        }

        fflush(stdout); // Flush the output buffer to ensure prompt is displayed

        ssize_t nread = getline(&input, &len, stdin); 
        if (nread == -1) 
        {
            // Handle error or EOF
            printf("\n");
            break;
        }
        char *command[64] = {0}; // Array to hold command and arguments
        char *word = strtok(input, " \t\n"); // Tokenize input to get command
        int i = 0;
        while (word != NULL && i < 63)
        {
            command[i++] = word;
            word = strtok(NULL, " \t\n");
        }
        command[i] = NULL; // Null-terminate the array
        if (command[0] == NULL)
        {
            continue; // No command entered, continue to next
        }

        if(strcmp(command[0], "exit") == 0)
        {
            break; // Exit the shell if command is "exit"
        }
        if(strcmp(command[0], "cd") == 0)
        {
            if (command[1] == NULL)
            {
                fprintf(stderr, "expected: cd [destination]\n"); // Error if no directory is provided
            }
            else
            {
                if (chdir(command[1]) != 0)
                {
                    perror("cd failed"); // Print error if chdir fails
                }
            }
            continue; // Continue to next loop after handling cd
        }
        // ex. instance 1: Real pid = 2111, pid = 2112, instance 2: Real pid = 2112, pid = 0
        pid_t pid = fork(); // Create a new process
        if (pid == 0)
        {
            // Child process
            if (execvp(command[0], command) == -1)
            {
                perror(command[0]); // Print error if execvp fails
                exit(1); // Exit child process with failure
            }
        }
        else if (pid < 0)
        {
            // Fork failed
            perror("fork failed"); // Print error if fork fails
        }
        else
        {
            // Parent process
            waitpid(pid, NULL, 0); // Wait for child process to finish
        }

    }
    free(input);
    return 0;
}