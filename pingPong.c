#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void ping(int sig);
void pong(int sig);
int cpid;

int main(int argc, char* argv[]){
	// create a child process
	cpid = fork();
	if (cpid == 0) {
		// setup our signal handler
		signal(SIGUSR1, ping);
		while(1);
	} else {
		sleep(1);
		signal(SIGUSR2, pong);
		kill(cpid, SIGUSR1);
		while(1);
	}
	sleep(1);
	// End the child process
	kill(cpid, SIGINT);
	sleep(1);
	return 0;
}

void ping(int sig) {
	printf("Ping!\n");
	sleep(1);
	kill(getppid(), SIGUSR2);
}

void pong(int sig) {
	printf("Pong!\n");
	sleep(1);
	kill(cpid, SIGUSR1);
}
