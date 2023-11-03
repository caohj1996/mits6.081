#include <user/user.h>
int main(int argc, char* argv[]){
    //char message[BUF_SIZE];
    int time;
    if(argc <2){
        printf("Usage: %s <time>\n",argv[0]);
        exit(1);
    }
    time = atoi(argv[1]);
    printf("%d\n",time);
    sleep(time);
    exit(0);
}