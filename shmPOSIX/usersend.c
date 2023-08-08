#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAXB 100
#define err -1
#define pathmsg "/shmem"
#define permissions 0666

int
main(int argc, char* argv[])
{
	char* resoult = (char*)malloc(32);
	int shm = shm_open(pathmsg, O_RDWR | O_CREAT, 0666);

	if (-1 == write(shm, "Never gonna give you up", 32)) {
		perror("didnt write");
		exit(EXIT_FAILURE);
	}
	printf("Never gonna give you up\n");
	while (!strcmp(resoult, "")) {
		read(shm, resoult, 32);
	}
	printf("%s\n", resoult);
	//shmdt(resoult);                  // detach
	shmctl(shm, IPC_RMID, NULL); // destroy

	exit(EXIT_SUCCESS);
}