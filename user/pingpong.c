#include <user/user.h>
#define BUF_SIZE 30
int main(int argc,char *argv[]){
    char message[BUF_SIZE];
    int pid;
    int pipfd[2];

    pipe(pipfd);
    pid = fork();
    if(pid == 0){
        read(pipfd[1],message,BUF_SIZE);
        printf("<%d> : recived ping\n",getpid());
        sleep(10);
        write(pipfd[0],"p",strlen("p"));
    }else{
        write(pipfd[1],"p",strlen("p"));
        read(pipfd[0],message,BUF_SIZE);
        sleep(10);
        printf("<%d> : recived pong\n",getpid());
    }
    close(pipfd[0]);
    close(pipfd[1]);
    exit(0);
}