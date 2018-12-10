#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void batter(int sig);

int main(int argc, char* argv[]){
	// create a child process
	int cpid = fork();
	if (cpid == 0) {
		// setup our signal handler
		signal(SIGUSR1, batter);
		while(1);
	} else {
		sleep(1);
		// send 9 pitches
		for (int i = 0; i < 10; i++) {
			sleep(1);
			kill(cpid, SIGUSR1);
		}
	}
	sleep(1);
	// End the child process
	kill(cpid, SIGINT);
	sleep(1);
	return 0;
}

void batter(int sig) {
	static int numPitches = 0;
	numPitches += 1;
	if (num == 4) num = 1;
	printf("Strike %d\n", numPitches);
}

