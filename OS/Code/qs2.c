#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n;
    
    // Read 'n' silently because the question specifies "no other print statement"
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Generic loop for n forks
    for (int i = 0; i < n; i++) {
        if (fork() < 0) {
            // In case fork fails, terminate to avoid broken process trees
            exit(1);
        }
    }

    // Print PID and PPID. This will be executed by 2^n processes.
    printf("PID: %d, PPID: %d\n", getpid(), getppid());

    // Wait for all child processes to ensure no process becomes an orphan or zombie.
    // wait(NULL) returns -1 when a process has no more children left to wait for.
    while (wait(NULL) > 0);

    return 0;
}