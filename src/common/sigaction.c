#include <sys/types.h>
#include <sys/wait.h>

#include <signal.h>

#include <stdlib.h>
#include <stdio.h>

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#include <string.h>

void
sigchild_handler(int sig, siginfo_t *sip, void __attribute__((unused))*extra)
{
	pid_t child = sip->si_pid;
	int status;

	if (sig != SIGCHLD) {
		fprintf(stderr,"sigchild_handler() ble calt med noe som ikke var SIGCHLD (%d), men sig %d\n",SIGCHLD,sig);
		fprintf(stderr,"signal stacken m� ha blirr korypt. Exiter.\n");
		exit(-1);
	}

	if (sip->si_code == CLD_EXITED) {
		printf("Got signal '%d', si_code %d"
				" for child %d\n",
				(sip->si_signo), sip->si_code, child);
		if (waitpid(-1, &status, 0) == -1) {
			perror("waitpid()");
		}
	} else {
		printf("Got signal '%d', si_code %d"
				" for child %d: ",
				sip->si_signo, sip->si_code, child);
		if (waitpid(-1, &status, 0) == -1) {
			perror("waitpid()");
		} else {
			if (WIFEXITED(status)) {
				printf("Exited normally\n");
			} else if (WIFSIGNALED(status)) {
				printf("Child was signaled: %d(%d)\n", WTERMSIG(status), WTERMSIG(status));
			} else {
				printf("Unknown exit\n");
			}
		}
	}
}

