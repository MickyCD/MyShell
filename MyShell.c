#include <stdio.h>
#include <stdlib.h>

int main() 
{
    char *input = NULL; // Pointer to hold input
    size_t len = 0; //size of input buffer
    ssize_t read;

    while(1)
    {
        printf("MyShell> ");
        fflush(stdout); // Flush the output buffer to ensure prompt is displayed

        read = getline(&input, &len, stdin); 
        if (read == -1) 
        {
            // Handle error or EOF
            printf("\n");
            break;
        }
    }
    free(input);
    return 0;
}