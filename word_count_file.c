#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char** argv) {
	// check if the parameter count is correct
	if (argc != 2) {
		printf("Error: Insufficient number of arguments.\n");
		return 1;
	}

	// open file with read only
	int file = open(argv[1], O_RDONLY);

	// check if file was opened
	if (file == -1) {
		printf("Error: file could not be opened.\n");
		return 1;
	}

	int wordCount = 0;
	int wordLength = 0;
	int lineCount = 1;
	char buffer[256];
	int bytesRead = read(file, buffer, 256);

	// check if file was read successfully
	if (bytesRead == -1) {
		printf("Error: could not read from file\n");
		return 1;
	}

	// traverse the entire text
	for (int i = 0; i < bytesRead; i++) {
		if (buffer[i] != ' ' && buffer[i] != '\n') {
			wordLength++;
		}

		if (buffer[i] == ' ' || buffer[i] == '\n') {
			// found end of word
			// prevent empty lines to count as words
			if (wordLength > 0) {
				wordCount++;
			}
			wordLength = 0;
		}

		if (buffer[i] == '\n') {
			// found end of line
			printf("Line %d contains %d words.\n", lineCount, wordCount);
			wordCount = 0;
			lineCount++;
		}
	}

	close(file);

	printf("Done!\n");

	return 0;
}
