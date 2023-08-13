#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        printf("Error: fork.\n");
        return 1;
    }
    
    if (pid == 0) {
		char filename[100];
        printf("Enter the file name:\n");
        scanf("%s", filename);

        exit(0);
    } else {
        wait(NULL);
		
        FILE *file = fopen(filename, "r");

        if (file == NULL) {
            printf("Unable to open the file.\n");
            return 1;
        }

        char ch;
        int count = 0;
        while ((ch = fgetc(file)) != EOF) {
            if (ch == '\n') {
                count++;
            }
        }

        fclose(file);

        printf("Number of lines: %d\n", count);
    }

    return 0;
}
