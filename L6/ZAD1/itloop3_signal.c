#include <stdio.h>
#include <time.h>
#include <signal.h>

int running;

void signal_handler(int sig_num)
{
	switch(sig_num)
	{
		case(SIGALRM):
		{
			printf("a) Otrzymano sygnał SIGALRM - Wyświetelnie komunikatu i zakończenie programu\n");
			running = 0;
		}
		break;

		case(SIGTERM):
		{
			printf("b) Otrzymano sygnał SIGTERM - Wyświetlenie komunikatu i powrót do wykonywania programu\n");
		}
		break;

		case(SIGUSR1):
		{
			printf("c) Otrzymano sygnał SIGUSR1 - Wstrzymanie odebrania sygnału na 1000 iteracji w pętli i wznowienie odebrania sygnału \n" );
			for(int i = 0; i <1000; i++);
		}
		break;
		
		case(SIGUSR2):
		{
		}
		break;

				

	}
}


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
	running = 1;
	int i = 0;
	int ms_stop = 1000;
	
	signal(SIGALRM, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);

	while(running)
	{
		i++;
		msleep(&ms_stop); 

	}

}

