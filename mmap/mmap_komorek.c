#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>

#define FILE_NAME_LENGTH 100

size_t getFileLength(const char *fileName)
{
    struct stat st;
    stat(fileName, &st);
    return st.st_size;
}

int fileExist(const char *fileName)
{
    struct stat st;
    if(stat(fileName, &st) == 0)
        return 1;
    else
        return 0;
}

void childProcess()
{
    if(execlp("display","display","-update","1","plik_wym",(char*)NULL) == -1)
    {
        perror("ERROR - execlp");
        exit(-2);
    }
}

void parentProcess(char fileName[], int fileDescriptor, int exchangedFD, size_t fileLength, void *data, int bytes)
{
    while (1)
    {
        // open file to effect
        do
        {
            printf("Podaj nazwę pliku do wyswietlenia (q-wyjście): \t");
            scanf("%s", fileName);

            if(fileName[0] == 'q') exit(1);

            fileDescriptor = open(fileName, O_RDONLY);
            if(fileDescriptor == -1)
                printf("Nie udało się otworzyć pliku! \n");
        }
        while(fileDescriptor==-1);

        // open exchange file
        exchangedFD = open("plik_wym", O_RDWR);
        if(exchangedFD == -1)
        {
            perror("ERROR - nie udało się otworzyć pliku wymiany");
            exit(-3);
        }

        // get file length
        fileLength = getFileLength(fileName);
        
        // change langth of exchanged file - cleaning image 
        if(ftruncate(exchangedFD, fileLength) == -1)
        {
            perror("ERROR - ftruncate");
            exit(-4);
        }

        // map data
        data = mmap(NULL, fileLength, PROT_READ | PROT_WRITE, MAP_SHARED, exchangedFD, 0);
        if(data == MAP_FAILED)
        {
            perror("ERROR - mapowanie danych");
            exit(-5);
        }

        // copy image to mmaped_data
        do
        {
            bytes = read(fileDescriptor, data, fileLength);
            if(bytes == -1)
            {
                perror("ERROR - wczytywanie danych");
                exit(-6); 
            }
        }
        while (bytes > 0);
        
        // synchronize file with mapped_data
        if(msync(data, fileLength, MS_SYNC)==-1)
        {
            perror("ERROR - synchronizacja");
            exit(-7);
        }

        // close files
        close(fileDescriptor);
        close(exchangedFD); 
    }
    
}

int main()
{
    pid_t pid;
    int fileDescriptor;
    int bytes;
    char fileName[FILE_NAME_LENGTH];
    size_t fileLength;

    int exchangedFD;
    void *mapped_data = NULL;

    if(fileExist("plik_wym")==0)
    {
        perror("ERROR - brak pliku wymiany \n");
        exit(0);
    }

    pid=fork();
    if(pid==-1)
    {
        perror("ERROR - błąd tworzenia procesu \n");
        exit(-1);
    }
    else if(pid==0)
    
        childProcess();
    }
    else
    {
        parentProcess(fileName, fileDescriptor, exchangedFD, fileLength, mapped_data, bytes);
    }

    return 0;
}
