#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) 
{
    char *input = NULL; // Pointer to hold input
    size_t len = 0; //size of input buffer
    ssize_t read;

    while(1)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s> ", cwd); // Display current working directory as prompt
        }

        fflush(stdout); // Flush the output buffer to ensure prompt is displayed

        nread = getline(&input, &len, stdin); 
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
    }
    free(input);
    return 0;
}