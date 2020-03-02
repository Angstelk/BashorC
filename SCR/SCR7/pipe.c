#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFF_IMG 1024

void rmNL(const char *filename){
char *newline =strchr(filename, '\n');
	if(newline != NULL) 
	 *newline='\0';
}


char *read_filename(){

char *filename =NULL;
size_t len=0;
	
	if(getline(&filename,&len,stdin)==-1){
		perror("Failed reading filename");
		exit(1);
	}
 rmNL(filename);
 return filename;	
}

FILE *openfile(char *filename){
	//printf("%s",filename);
	FILE *file =fopen(filename,"r");
	if(file == NULL){
	printf("Opening file error \n ");
	}
return file;
}

int Openfile(char *filename){
	int FD=open(filename, O_RDONLY);
	if(FD==-1) 
	{printf("Opening filed \n");}
	return FD;

}

int read_img(int fd, char * img){
	if(read(fd,img,100)==-1) printf("Error reading image! \n");
	else printf("Reading image complete. \n");
	return 1;
}

void SendIm(FILE * file, int pipe_fd,char *buffer)
{
	size_t size;
	while(size=fread(buffer,sizeof(buffer),sizeof(buffer),file)>0)
		write(pipe_fd,buffer,size);

	//printf("Zapis %d   %d   %d   %d  \n", size,file,pipe_fd,buffer);
}

int main(){

int fd[2];
pipe(fd);
fd[0]; // for read end
fd[1]; // for write end

pid_t pid; 
	
	pid=fork();

	if (pipe(fd)==-1){ 
 	fprintf(stderr, "Pipe Failed" ); 
 	return -1 ;} 

	if(pid>0)
	{

	char img[BUFF_IMG];
	// parent	
	if(close(fd[0])==-1)
		printf("Nie udało się zamknąć pliku \n");

	printf("Podaj nazwe pliku : ");
	
	char *name=read_filename();
	printf("%s \n",name);
	
	FILE * file=openfile(name);
	
	SendIm(file,fd[1],img);
	
	sleep(10);
	
	if(close(fd[1])==-1)printf("Nie udało się zamkąć pliku \n");
	
	}
	//child
	else 
	{
	
	if(close(fd[1])==-1) printf("Nie udalo się zamknąć pliku\n");

	if(dup2(fd[0],STDIN_FILENO)==-1)printf("BLAD DUP");

	execlp("display","display",NULL);
	perror("Błąd wyświetlania obrazu\n");	
	
	}

}
