#include <stdio.h>
#include <time.h>

void msleep(int* milliseconds)
{
	int ms_remaining = (*milliseconds) % 1000;
	long usec = ms_remaining * 1000;
	struct timespec ts_sleep;
	ts_sleep.tv_sec = (*milliseconds)/ 1000;
	ts_sleep.tv_nsec = 1000*usec;
	nanosleep(&ts_sleep, NULL);
}

int main(void)
{
	int i = 0;
	int ms_stop = 1000;
	while(1)
	{
		i++;
		msleep(&ms_stop); 

	}
	


}
