#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

        if (strcmp(*my_argv, "exit") == 0)
            break;
        else if (strcmp(*my_argv, "cd") == 0) {
            if (*(my_argv + 1) == NULL) { // if only cd is typed return to user home
                chdir(getenv("HOME"));
                continue;
            }
            chdir(*(my_argv + 1));
            continue;
        }

        int pid = fork();

        if (pid == 0) { // basically if its the child class run this
            execvp(my_argv[0], my_argv);
        }
        else {
            wait(NULL); // parent waits for the child
        }



    }
    return 0;
}
