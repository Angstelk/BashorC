#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const int CHILD_PID = 0;
const int WRITING_END = 1;
const int READING_END = 0;


void CreatePipe(int* pipe_fd);
pid_t ForkProcess(void);
void ExecImgReader(int* pipe_fd);
void ExecImgWriter(int* pipe_fd);
void CloseFd(int fd);
void DuplicateFd(int old_fd, int new_fd);
void DisplayImg(void);
void MoveImg(FILE* file, int pipe_fd, char* buff);
FILE* OpenFile(char* file_path);



int main(void)
{
  //Utworzenie potoku
  int pipe_fd[2];
  CreatePipe(pipe_fd);

  //Utworzenie nowego procesu
  pid_t new_proc_id =  ForkProcess();

  //Proces nadrzędny
  if(new_proc_id > CHILD_PID)
  {
    ExecImgWriter(pipe_fd);
  //Proces podrzędny
  }
  else
  {
    ExecImgReader(pipe_fd);
  }

  return 0;
}


////////////////////////////////////////////////////////////////////////////////
void CreatePipe(int *pipe_fd)
{
  if(pipe(pipe_fd) == -1)
  {
    perror("Nie udalo sie utworzyc potoku\n");
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
pid_t ForkProcess(void)
{
  pid_t new_proc_id = fork();
  if(new_proc_id < 0)
  {
   perror("Nie udalo sie utworzyc procesu\n");
   exit(EXIT_FAILURE);
  }
  return new_proc_id;
}

////////////////////////////////////////////////////////////////////////////////
void DuplicateFd(int old_fd, int new_fd)
{
  if(dup2(old_fd, new_fd) == -1)
  {
    perror("Nie udalo sie zduplkiowac ucwytu pliku\n");
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
void CloseFd(int fd)
{
  if(close(fd) == -1)
  {
    perror("Nie udało sie zamknac pliku");
    exit(EXIT_FAILURE);
  }
}

////////////////////////////////////////////////////////////////////////////////
void DisplayImg(void)
{
  //printf("Wyswietlanie obrazu:\n");
  execlp("display", "display", NULL);

  perror("Nie udało sie wyswietlic obrazu\n");
  exit(EXIT_FAILURE);
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
  return tmp;
}

void MoveImg(FILE* file, int pipe_fd, char *buff)
{
  size_t buff_content_size;
  printf("Zapis obrazu do potoku\n");

  while( (buff_content_size = fread(buff, sizeof(char), sizeof(buff), file)) > 0)
    write(pipe_fd, buff, buff_content_size);
}


////////////////////////////////////////////////////////////////////////////////
void ExecImgReader(int* pipe_fd)
{
  //Zamknięcie pipe_fd[WRITING_END]
  CloseFd(pipe_fd[WRITING_END]);
  //Przekierowanie STDIN -> pipe_fd[READING_END]
  DuplicateFd(pipe_fd[READING_END], STDIN_FILENO);

  DisplayImg();
}

////////////////////////////////////////////////////////////////////////////////
void ExecImgWriter(int* pipe_fd)
{
  CloseFd(pipe_fd[READING_END]);
  char file_path[1024];
  char data_img_buff[1024];
  GetFilePath(file_path);
  printf("Sciezka to: %s\n", file_path); //testowo
  FILE* file = OpenFile(file_path);
  MoveImg(file, pipe_fd[WRITING_END], data_img_buff);
  sleep(10); //Obraz wyświetla się dopiero po zamknięciu potoku 
  CloseFd(pipe_fd[WRITING_END]);

}
