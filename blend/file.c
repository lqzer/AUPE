#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>


pthread_mutex_t mutex;

void* read_file(void* file)
{
    pthread_mutex_lock(&mutex);
    FILE* fp = (FILE*)file;
    fseek(fp,0,SEEK_SET);
    char buf[1024];
    while(fgets(buf,1024,fp) != NULL)
    {
        printf("this thread id : %d, ---> %s",pthread_self(),buf);
    }

    sleep(1);
    pthread_mutex_unlock(&mutex);


}

int main(int argc, char* argv[])
{
    int i;
    FILE* fp = fopen("./test.txt","r");
    if(fp == NULL)
    {
        perror("open file failed");
        exit(EXIT_FAILURE);
    }
    fseek(fp,0,SEEK_SET);

    pthread_mutex_init(&mutex,NULL);
    pthread_t pthread[10];
    for( i = 0;i < 10;++i)
    {
        pthread_create(&pthread[i],NULL,read_file,fp);
    }
    for(i = 0;i < 10;++i)
    {
        pthread_join(pthread[i],NULL);
    }

    fclose(fp);
    pthread_mutex_destroy(&mutex);
}