#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>





int get_size(char* path);

int pid_child = 0;

int main(void)
{

  //Utworzenie procesu potomnego
  pid_t PID = fork(); 
  struct stat file_status;
  char path[256];
  int file_size;  
  int FH;
  int fd_shared;
  void * addres;
  if(PID > pid_child)
  {
    int tmp = 1;
    while(tmp > 0)
    {

      //Pobranie ściezki do przetwarzanego pliku (1)
    	printf("Podaj sciezke : (x wyjscie):\n>");
        tmp = scanf("%s", path);
        if( (path[0] == 'x')) tmp=-1;

     FH = open(path, O_RDWR);
                                    // otwieranie obrazka
  stat(path, &file_status);
  file_size=file_status.st_size;

  truncate("/home/apeiron/Dokumenty/zalegle_scr/lena.png", file_size); // zmiana rozmiaru pliku wymiany 
  
  fd_shared = open("/home/apeiron/Dokumenty/zalegle_scr/lena.png", O_RDWR);// otwieranie pliku wymiany 
  
  addres = mmap(0, file_size, PROT_READ|PROT_WRITE,MAP_SHARED,fd_shared,0 );
	 // odwzorowanie obrazka do pliku wymiany
  
  read(FH,addres,file_size); // czytanie i przepisywanie obrazka do pliku wmiany  
  
  msync(addres,file_size, MS_SYNC); // synchronize file with memory map 
  
  close(FH);//zamknecie pliku obrazu

  munmap(addres, file_size);//sprzatanie 

  close(fd_shared);
  //zamkniecie pliku wymiany
   }
  }
  else
  {
  execlp("display","display","-update","1","/home/apeiron/Dokumenty/zalegle_scr/lena.png",NULL);
  }
}

