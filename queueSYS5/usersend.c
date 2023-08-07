#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#define MAXB 128

struct msgbuf
{
    long int mtype;
    char msg[MAXB];
};

int
main(int argc, char* argv[])
{
    key_t  key = ftok("/bufferofqueue", 1);
    int fd;
    long int msgrcv_param = 0;

    struct msgbuf mess;

    char* buf1 = "Never gonna give you up";
    if (key == -1)
    {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    fd = msgget(key, 0666 | IPC_CREAT);
 
    mess.mtype = 1;

    strcpy(mess.msg, buf1);
    if (msgsnd(fd, (void*)&mess, MAXB, 0) == -1)
    {
        perror("Send ERR");
        exit(EXIT_FAILURE);
    }
    if (msgrcv(fd, (void*)&mess, MAXB, msgrcv_param, 0) == -1)
    {
        perror("Receive ERR");
        exit(EXIT_FAILURE);
    }

    printf("msg received: %s\n", mess.msg);
    printf("program finished!!!\n");
}