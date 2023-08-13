#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char filename[100];

    if (pipe(pipefd) == -1) {
        printf("Error: Pipe failed.\n");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        printf("Error: Fork failed.\n");
        exit(1);
    }
	
	if (pid == 0) { // Child process
        close(pipefd[0]);

        printf("Enter a filename: ");
        scanf("%s", filename);

        write(pipefd[1], filename, sizeof(filename));
        close(pipefd[1]);

        exit(0);
    }
	
	// Parent process
	close(pipefd[1]);

	wait(NULL);

	char received_filename[100];
	read(pipefd[0], received_filename, sizeof(received_filename));
	close(pipefd[0]);

	// Check if the file exists in the current directory
	struct stat st;
	if (stat(received_filename, &st) == 0) {
		// Get the file extension
		char *file_extension = strrchr(received_filename, '.');
		printf("File extension: %s\n", file_extension + 1);
	} else {
		printf("File does not exist in the current directory.\n");
	}

    return 0;
}
