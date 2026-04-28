#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Same message structure
struct msgbuf {
    long mtype;
    char mtext[100];
};

#define MSG_KEY 1234

int main() {
    int msgid;
    struct msgbuf msg;
    
    // Get existing message queue
    msgid = msgget(MSG_KEY, 0666);
    if (msgid == -1) {
        perror("msgget receiver");
        exit(1);
    }
    
    printf("Receiver: Waiting for 5 messages...\n");
    
    // Receive all 5 messages
    for (int i = 0; i < 5; i++) {
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        
        printf("Received: %s", msg.mtext);
        // Print only if starts with 'S'
        if (msg.mtext[0] == 'S') {
            printf(" (PRINTED - starts with S)\n");
        } else {
            printf(" (ignored - starts with A)\n");
        }
    }
    
    // Clean up queue
    msgctl(msgid, IPC_RMID, NULL);
    printf("Receiver: All messages processed. Queue removed.\n");
    
    return 0;
}
