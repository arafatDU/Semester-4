#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int pid = fork();

    if (pid == 0) {
        int sum = 0;
        for (int i = 1; i <= n; i += 2) {
            sum += i;
        }
        printf("Child process (PID: %d) - Sum of odd numbers up to %d: %d\n", getpid(), n, sum);
    } else if (pid > 0) {
        int sum = 0;
        for (int i = 2; i <= n; i += 2) {
            sum += i;
        }
        printf("Parent process (PID: %d) - Sum of even numbers up to %d: %d\n", getpid(), n, sum);
    } else {
        fprintf(stderr, "Fork failed\n");
        return 1;
    }

    return 0;
}
