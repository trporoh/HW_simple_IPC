#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXB 100
#define err -1
#define pathmsg "/shmem"
#define permissions 0666

int
main(int argc, char* argv[])
{

	key_t key;

	key = ftok(pathmsg, 15);
	int msg_shm = shmget(key, MAXB, permissions | IPC_CREAT);
	char* resoult;
	resoult = shmat(msg_shm, NULL, 0);
	printf("%s\n", resoult);
	strcpy(resoult, "Never gonna let you down");
	shmdt(resoult);                  // detach
	shmctl(msg_shm, IPC_RMID, NULL); // destroy
}