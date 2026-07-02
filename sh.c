#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{

    char input_buffer[128];
    char *my_argv[64];

    while (1) {
        printf("myshell>");
        fflush(stdout);

        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL) // fgets reads \n too
            break;

        input_buffer[strcspn(input_buffer, "\n")] = '\0'; // replace \n with \0 to combat fgets 

        char *split_words = strtok(input_buffer, " ");
        
        int my_argv_assigner = 0;
        while (split_words != NULL) {
            *(my_argv + my_argv_assigner) = split_words;
            my_argv_assigner++;
            split_words = strtok(NULL, " "); /* have to do it again bc *split_words outside loop first time 
                                                        pass NULL to keep it going through input_buffer*/
        }

        *(my_argv + my_argv_assigner) = NULL;
    }
    return 0;
}
