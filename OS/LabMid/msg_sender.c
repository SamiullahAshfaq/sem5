#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// Message structure for System V message queue
struct msgbuf {
    long mtype;          // Message type (must be > 0)
    char mtext[100];     // Word data
};

#define MSG_KEY 1234    // Key for message queue

int main() {
    int msgid;
    struct msgbuf msg;
    
    // Create or get message queue
    msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget sender");
        exit(1);
    }
    
    printf("Sender: Sending 5 words (starting with A or S)...\n");
    
    // Send 5 words
    char *words[] = {"Apple", "Sky", "Ant", "Sun", "Arrow"};
    for (int i = 0; i < 5; i++) {
        msg.mtype = 1;  // Same type for all messages
        strcpy(msg.mtext, words[i]);
        
        if (msgsnd(msgid, &msg, strlen(msg.mtext) + 1, 0) == -1) {
            perror("msgsnd");
            exit(1);
        }
        printf("Sent: %s\n", msg.mtext);
        sleep(1);  // Delay between sends
    }
    
    printf("Sender: All 5 words sent.\n");
    
    // Optional: remove queue after sending (but let receiver read first)
    // msgctl(msgid, IPC_RMID, NULL);
    
    return 0;
}
