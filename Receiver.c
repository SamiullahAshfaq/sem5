#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 12345

int main() {
    int shmid;
    char *shmaddr;

    // Create or attach to the shared memory segment
    shmid = shmget(SHM_KEY, sizeof(char) * 100, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Read data from the shared memory
    printf("Data read from shared memory: %s\n", shmaddr);

    // Detach from the shared memory segment
    shmdt(shmaddr);

    return 0;
}
