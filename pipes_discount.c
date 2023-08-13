#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    float discount, price;

    if (pipe(pipefd) == -1) {
        printf("Error: pipe failed.\n");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        printf("Error: fork failed.\n");
        return 1;
    }

    if (pid == 0) {
        close(pipefd[0]);

        printf("Enter discount: ");
        scanf("%f", &discount);

        if (discount < 0 || discount > 100) {
            printf("Error: invalid discount.\n");
            return 1;
        }

        write(pipefd[1], &discount, sizeof(discount));

        printf("Enter price: ");
        scanf("%f", &price);
        write(pipefd[1], &price, sizeof(price));

        close(pipefd[1]);

        exit(0);
    }

    close(pipefd[1]);

    wait(NULL);

    read(pipefd[0], &discount, sizeof(discount));
    read(pipefd[0], &price, sizeof(price));
    close(pipefd[0]);

    price = price - discount / 100 * price;

    printf("Final %.2f\n", price);

    return 0;
}