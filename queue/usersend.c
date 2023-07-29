#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>

mqd_t queue;

int main(int argc, char** argv) {

	struct mq_attr attr;
	unsigned int prio2 = 2;
	unsigned int prio1 = 1;

	char* string = "Hello";
	char* received = (char*)malloc(32);

	queue = mq_open("/bufforqueue", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
	mq_send(queue, string, strlen(string), prio1);

	//wait(1);
	getchar();

	do {
		mq_receive(queue, received, attr.mq_msgsize, NULL);
	} while (!strcmp(received, ""));
	printf("messeged received:  %s", received);

	//mq_unlink(queue);
	mq_close(queue);

	exit(EXIT_SUCCESS);
}