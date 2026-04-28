/* Simple producer: creates shared memory, writes message, waits for consumer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  /* for sleep */
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h> /* actually not used, but kept for future */

#define SHM_KEY 12345
#define BUFSIZE 256

int main() {
    int shmid;         /* shared memory ID */
    char *shm;         /* pointer to shared memory */

    /* Get shared memory segment (create if not exists) */
    shmid = shmget(SHM_KEY, BUFSIZE, IPC_CREAT | 0666);
    if (shmid < 0) { perror("shmget"); exit(1); }

    /* Attach to shared memory */
    shm = shmat(shmid, 0, 0);
    if (shm == (char*)-1) { perror("shmat"); exit(1); }

    /* Copy message to shared memory */
    strcpy(shm, "Hello from sender!");

    /* Print confirmation */
    printf("Sender wrote: %s\\n", shm);

    /* Wait for receiver to read (manual timing) */
    sleep(3);

    /* Detach */
    shmdt(shm);

    /* Remove shared memory */
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}

