#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int flaga=1;
int flaga_sig=1;
void sig_handler(int signo){
	if(flaga_sig==1){
	if (signo == SIGUSR1){
	flaga=0;		
	printf("\n otrzymano SIGUSR1 koncze program \n");}
	if (signo == SIGUSR2){

	printf("\n otrzymano SIGUSR2 kontynuuje program \n");}
	if (signo == SIGTERM){
	int z=100;
	flaga_sig=0;
	while(z){
		z--;}
	flaga_sig=1;
	printf(" \n otrzymano SIGTERM wstrzymuje na 1000 iteracji \n ");
	}
	if (signo == SIGALRM){}

	}
}
void ign(int signum){}
void wait_loop(int signum){
}
void msleep(int *milliseconds){
	int ms_remaining = (*milliseconds) % 1000;
	long usec = ms_remaining * 1000;
	struct timespec ts_sleep;
	ts_sleep.tv_sec = (*milliseconds) / 1000;
	ts_sleep.tv_nsec = 1000*usec;
	nanosleep(&ts_sleep, NULL);
}
int main(){

int i;
int ms=1000;
 
	
signal(SIGTERM,sig_handler);//term
signal(14,sig_handler);//alrm
signal(10,sig_handler);//usr1
signal(12,sig_handler);//usr2
	
	while(flaga){
	
		msleep(&ms);
		i++;
	
	}
}
