#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdbool.h>

// Helper function to check if a number is prime
bool is_prime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int main() {
    int arr[1000];
    
    // Seed the random number generator
    srand(time(NULL));

    // Populate the array with random integers between 1 and 100
    for (int i = 0; i < 1000; i++) {
        arr[i] = (rand() % 100) + 1;
    }

    // Create the first child process
    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("First fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // --- FIRST CHILD PROCESS ---
        int prime_count = 0;
        for (int i = 0; i < 500; i++) {
            if (is_prime(arr[i])) {
                prime_count++;
            }
        }
        printf("First Child (PID: %d): Found %d prime numbers in the first 500 elements.\n", getpid(), prime_count);
        exit(0); // Exit so child doesn't execute parent code
    } else {
        // --- PARENT PROCESS ---
        // Create the second child process
        pid_t pid2 = fork();

        if (pid2 < 0) {
            perror("Second fork failed");
            exit(1);
        } else if (pid2 == 0) {
            // --- SECOND CHILD PROCESS ---
            int prime_count = 0;
            for (int i = 500; i < 1000; i++) {
                if (is_prime(arr[i])) {
                    prime_count++;
                }
            }
            printf("Second Child (PID: %d): Found %d prime numbers in the remaining 500 elements.\n", getpid(), prime_count);
            exit(0); // Exit so child doesn't execute parent code
        } else {
            // Parent must wait for both children to terminate to prevent zombie processes
            wait(NULL);
            wait(NULL);
            printf("Parent (PID: %d): Both child processes have completed successfully.\n", getpid());
        }
    }

    return 0;
}