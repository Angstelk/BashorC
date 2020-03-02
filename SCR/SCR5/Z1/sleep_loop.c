#include <stdio.h>
#include <time.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>


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
while(1){
				
	msleep(&ms);
	i++;
}}

