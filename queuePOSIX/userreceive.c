#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>

mqd_t queue;

int main(int argc, char** argv) {

	struct mq_attr attr;

	char* string = "Hi";
	char* received = (char*)malloc(32);

	queue = mq_open("/bufforqueue", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, NULL);
	do {
		mq_receive(queue, received, attr.mq_msgsize, NULL);
	} while (!strcmp(received , ""));

	printf("messeged received:  %s", received);

	//wait(1);
	getchar();

	mq_send(queue, string, strlen(string), 1);

	//mq_unlink(queue);

	exit(EXIT_SUCCESS);
}