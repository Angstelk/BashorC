#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>

#define NAME_LEN 100

size_t getfilelength(const char *fileName)
{
    struct stat st;
    stat(fileName, &st);
    return st.st_size;
}


void CreateExchangeFile()
{
 if(execlp("touch","touch","nowy_plik",(char*)NULL) == -1)
 {
	perror("Error- creating exchange file ");
	exit(-1);
 }

}



void child()
{
	if(execlp("display","display","-update","1","file_ex",(char*)NULL) == -1)
	{
        perror("Display error");
        exit(-5);
    	}

}

void parent(char filename[], int FD, int ex_FD, size_t file_len, void *data, int bytes)
{
	while(1)
	{
	
		do
        {
            printf("Podaj nazwę pliku do wyswietlenia (q-wyjście): \t");
            scanf("%s", filename);

            if(filename[0] == 'x') exit(1);

            FD = open(filename, O_RDONLY);
            if(FD == -1)
                printf("Nie udało się otworzyć pliku! \n");
        }
        while(FD==-1);


/*		do
		{
		 
		 printf("Podaj nazwe pliku : \t");
		 scanf("%s", filename);
		
		 if(filename[0] == 'x' ) exit(1);
			
		 printf("Nazwa pliku to :'%s' \n", filename);

		 FD = open(filename, O_RDONLY);
			
		 

		 if(FD = -1)
		 {
		  printf("Nie udało się otworzyć pliku ! %s  \n",  strerror(errno));
		 }
	 	 	 
		}while(FD == -1 );
		
		ex_FD = open( "file_ex", O_RDWR);
		
		if(ex_FD == -1)
			printf("Nie można otworzyc pliku wymiany \n");	
*/	
	
		file_len = getfilelength(filename);
	
		 if(ftruncate(ex_FD, file_len) == -1)
        	{
           	 perror("ERROR - ftruncate");
           	 exit(-4);
        	}
		 data = mmap(NULL, file_len, PROT_READ | PROT_WRITE, MAP_SHARED, ex_FD, 0);
        if(data == MAP_FAILED)
        {
            perror("Błąd mapowania danych");
            exit(-5);
        }

        do
        {
            bytes = read(FD, data, file_len);
            if(bytes == -1)
            {
                perror("Błąd wczytywania danych");
                exit(-6); 
            }
        }
        while (bytes > 0);
        
        if(msync(data, file_len, MS_SYNC)==-1)
        {
            perror("Błąd synchronizacji");
            exit(-7);
        }

        close(FD);
        close(ex_FD); 
    }

	
}

int main()
{

	char filename[NAME_LEN];
	int FD;
	size_t file_len;
	int ex_FD;
	size_t Len_file;
	int bytes;
	
	void *mapp_data = NULL;

	pid_t pid;

	//CreateExchangeFile();
	while(1){

		printf("Podaj nazwe pliku : \n");
		 scanf("%s", filename);
		
		 if(filename[0] == 'x' ) exit(1);
			
		 printf("Nazwa pliku to :'%s' \n", filename);

		 FD = open(filename, O_RDONLY);
			
		 

		 if(FD = -1)
		 {
		  printf("Nie udało się otworzyć pliku ! %s  \n",  strerror(errno));
	         }
	 
	 }
/*
	pid = fork();
	

	if(pid==-1)
	{
		perror("Błąd tworzenia procesów \n");
		exit(-2);
	}

	else if(pid==0)
	{
		child();
	}
	else
	{
		parent(filename, FD,ex_FD,file_len,mapp_data,bytes);
	}	
*/
}

