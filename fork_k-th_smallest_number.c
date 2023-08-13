#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// check for the correct number of parameters
	if (argc != 2) {
		printf("Error: Invalid argument count!\n");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");

	// check if foile was successfully opened
	if (file == NULL) {
		printf("Error: File could not be opened!\n");
		return 1;
	}

	// read n and k
	int n, k;
	printf("Enter a value for n:\n");
	scanf("%d", &n);

	printf("Enter a value for k:\n");
	scanf("%d", &k);

	// check if k is a valid number
	if (k > n) {
        printf("Error: k is greater than the number of integers in the file!\n");
        return 1;
    }

	int array[n];
	int i = 0;
	while (i < n && fscanf(file, "%d", &array[i]) != EOF) {
		i++;
	}

	fclose(file);

	int minim = 0;
	// find the k-th number if the array was sorted in ascending order
	for (int i = 0; i < k; i++) {
		// create a pipe for the parent to have access to the min
		int fd[2];
		if (pipe(fd) == -1) {
			printf("Error: pipe() error!\n");
			return 1;
		}

		// create 2 processes: child = min;  parent = max
		int pid = fork();
		if (pid == -1) {
			printf("Error: fork() error!\n");
			return 1;
		}

		if (pid == 0) { // child process
			int min_idx = i;
			// find the index of the min
			for (int j = i + 1; j < n; j++) {
				if (array[j] < array[min_idx]) {
					min_idx = j;
				}
			}
			// add the index to the pipe
			close(fd[0]);
			write(fd[1], &min_idx, sizeof(int));
			close(fd[1]);
			exit(0);
		} else { // parnet process
			int max_idx = 0;
			// find the index for the max
			for (int j = 0; j < n; j++) {
				if (array[j] > array[max_idx]) {
					max_idx = j;
				}
			}
			// read the min index from the pipe
			close(fd[1]);
			int min_idx;
			read(fd[0], &min_idx, sizeof(int));
			// save the current minim and replace it in the array with the max
			minim = array[min_idx];
			array[min_idx] = array[max_idx];
			close(fd[0]);
			wait(NULL);
		}
	}

	printf("The k-th number is: %d\n", minim);

	return 0;
}