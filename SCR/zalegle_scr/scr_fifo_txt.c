#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>


void SendData(FILE* file, int pipe_fd, char *buff);
FILE* file_opn(char* f_path);
int GetPath(char* f_path_buff);

int main(void)
{
  
  int tmp = 0;
  char f_path[256];
  char data_buff[1024];
  
  if(mkfifo("fifo_scr", 0666) == -1)
  {
    perror("tworzenie fifo :\n");
    exit(EXIT_FAILURE);
  }

  int fifo_fd = open("fifo_scr", O_RDWR);
 
  if(fifo_fd == -1)
  {
    perror("otwieranie potoku nazwanego");

    exit(EXIT_FAILURE);
  }


  while(1)
  {
    tmp = GetPath(f_path);
    if(tmp == -1 )
      break;
    FILE* file = fopen(f_path, "r");
    if(file == NULL)
      exit(EXIT_FAILURE);
    
    file_opn(f_path);
    
    SendData(file, fifo_fd, data_buff);
  }

}

FILE* file_opn(char* f_path)
{
    FILE* file = fopen(f_path, "r");
    if(file == NULL)
      exit(EXIT_FAILURE);
    return file;
}

int GetPath(char* f_path_buff)
{
  printf("podaj sciezke do pliku :\n>");
  int tmp = scanf("%s", f_path_buff);
  if( (f_path_buff[0] == 'x'))
        return -1;
  return tmp;
}

void SendData(FILE* file, int pipe_fd, char *buff)
{
  size_t buff_content_size;

  while( (buff_content_size = fread(buff, sizeof(char), sizeof(buff), file)) > 0)
    write(pipe_fd, buff, buff_content_size);// dopisac
  printf("zapisano \n ");
}
