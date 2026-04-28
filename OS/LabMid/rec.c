/* Simple receiver: attaches to shared memory and reads message */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 12345
#define BUFSIZE 256

int main() {
    int shmid;         /* shared memory ID */
    char *shm;         /* pointer to shared memory */

    /* Get existing shared memory segment */
    shmid = shmget(SHM_KEY, BUFSIZE, 0666);
    if (shmid < 0) { perror("shmget"); exit(1); }

    /* Attach to shared memory */
    shm = shmat(shmid, 0, 0);
    if (shm == (char*)-1) { perror("shmat"); exit(1); }

    /* Print message from shared memory */
    printf("Receiver read: %s\\n", shm);

    /* Detach */
    shmdt(shm);

    return 0;
}

