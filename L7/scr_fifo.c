#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void CreateFifo(char* fifo_path, mode_t mode);
FILE* OpenFile(char* file_path);
int GetFilePath(char* file_path_buff);
void MoveTxt(FILE* file, int pipe_fd, char *buff);

int main(void)
{
  char file_path[256];
  char data_txt_buff[1024];
  //Utworzenie potoku nazwanego
  //CreateFifo("myfifo", 0666);
  int fifo_fd = open("/tmp/fifo_scr", O_RDWR);
  if(fifo_fd == -1)
  {
    perror("Nie udalo sie otworzyc potoku nazwanego");
    exit(EXIT_FAILURE);
  }

  int flag = 0;

  while(1)
  {
    flag = GetFilePath(file_path);
    if(flag == -2 )
      break;
    FILE* file = OpenFile(file_path);
    MoveTxt(file, fifo_fd, data_txt_buff);
  }

}



////////////////////////////////////////////////////////////////////////////////
void CreateFifo(char* fifo_path, mode_t mode)
{
  if(mkfifo(fifo_path, mode) == -1)
  {
    perror("Nie udalo sie utworzyc potoku nazwanego\n");
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
FILE* OpenFile(char* file_path)
{
    FILE* file = fopen(file_path, "r");
    if(file == NULL)
    {
      perror("Nie udalo sie otwrzyc pliku\n");
      exit(EXIT_FAILURE);
    }
    return file;
}

////////////////////////////////////////////////////////////////////////////////
int GetFilePath(char* file_path_buff)
{
  printf("Prosze podac sciezke do pliku obrazu:\n>");
  int tmp = scanf("%s", file_path_buff);
  if( (file_path_buff[0] == 's') &
      (file_path_buff[1] == 's') &
      (file_path_buff[2] == 's') )
        return -2;
  return tmp;
}

void MoveTxt(FILE* file, int pipe_fd, char *buff)
{
  size_t buff_content_size;
  printf("Zapis obrazu do potoku\n");

  while( (buff_content_size = fread(buff, sizeof(char), sizeof(buff), file)) > 0)
    write(pipe_fd, buff, buff_content_size);
}
