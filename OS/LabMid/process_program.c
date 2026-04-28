#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main() {
    pid_t pid1, pid2;
    int a, b, sum;
    char dir[50];

    printf("Parent PID: %d\n", getpid());

    // Child 1 - arithmetic
    pid1 = fork();
    if (pid1 == 0) {
        printf("\nChild 1 PID: %d - Arithmetic\n", getpid());
        printf("Enter 2 numbers: ");
        scanf("%d %d", &a, &b);
        sum = a + b;
        printf("Sum = %d\n", sum);
        exit(0);
    }

    wait(NULL);  // Wait for child1 to complete before child2

    // Child 2 - mkdir  
    pid2 = fork();
    if (pid2 == 0) {
        printf("\nChild 2 PID: %d - Directory\n", getpid());
        printf("Enter dir name: ");
        scanf("%s", dir);
        mkdir(dir, 0755);
        printf("Created: %s\n", dir);
        exit(0);
    }

    wait(NULL);  // Wait for child2

    printf("\nParent summary:\n");
    printf("Child1 PID %d: addition\n", pid1);
    printf("Child2 PID %d: mkdir\n", pid2);

    return 0;
}
