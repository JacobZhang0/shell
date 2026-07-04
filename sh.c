#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

void handle_sigint(int);

int main(int argc, char *argv[]) 
{

    char input_buffer[128];
    char *my_argv[64];

    struct sigaction act;

    act.sa_flags = SA_RESTART; // once func is done running restart fgets
    act.sa_handler = handle_sigint; 
    sigemptyset(&act.sa_mask); // clear other signals while ctr-c is running
    sigaction(SIGINT, &act, NULL);

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

        if (my_argv_assigner == 0) {
            continue;
        }

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

        char *input_file = NULL;
        char *output_file = NULL;

        for (int i = 0; *(my_argv + i) != NULL; i++) {
            if (strcmp(*(my_argv + i), "<") == 0) {
                input_file = *(my_argv + i + 1);
                *(my_argv + i) = NULL;
            }
            else if (strcmp(*(my_argv + i), ">") == 0) {
                output_file = *(my_argv + i + 1); 
                *(my_argv + i) = NULL; // override current index with NULL to stop execvp
            }
        }

        int pid = fork();

        if (pid == 0) { // basically if its the child class run this
            if (output_file != NULL) {
                int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644); // third arg is standard permission settings
                dup2(fd,1); // 1 is monitor screen. copies channel 3 and forces it onto channel 1
            }
            if (input_file != NULL) {
                int fd = open(input_file, O_RDONLY);
                dup2(fd, 0);
            }
            execvp(*my_argv, my_argv); 
        }
        else {
            wait(NULL); // parent waits for the child
        }



    }
    return 0;
}

void handle_sigint(int sig)
{
    printf("\nmyshell>");
    fflush(stdout);
}
