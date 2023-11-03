#include <user/user.h>
int main(int argc, char* argv[]){
    printf("primes: 2\n");
    int num = 2;
    int pid;
    int newpipe[2];
    pipe(newpipe);
    //close(pipefds[1]);
    pid = fork();
    if(pid == 0){
        read(newpipe[0],(void *)&num,sizeof(num));
        printf("primes:%d\n",num);
        while(1){
            //int newpipe[2];
            int leftfd = newpipe[0];
            int writefd = newpipe[1];
            pipe(newpipe);
            pid = fork();
            //printf("pid = %d\n",pid);
            if(pid == 0){
                close(writefd);
                close(leftfd);
                read(newpipe[0],(void *)&num,sizeof(num));
                sleep(10);
                printf("primes:%d\n",num);
            }else{
                close(writefd);
                //printf("pid = %d\n",pid);
                //close(newpipe[0]);
                int data;
                int ret;
                while(1){
                    ret = read(leftfd,(void*)&data,sizeof(data));
                    if(ret == 0){
                        //close(newpipe[0]);
                        break;
                    }
                    if(data % num == 0){
                        continue;
                    }else{
                        write(newpipe[1],(void*)&data,sizeof(data));
                    }
                }
                break;
            }

        }
    }else{
        close(newpipe[0]);
        for(int i = 3; i<36; ++i){
            if(i % num == 0)
                continue;
            else{
                write(newpipe[1],(void*)&i,sizeof(i));
            }
        }
        close(newpipe[1]);
    }
    exit(0);
}
