#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#define BUF_SIZE 14
void find(char *dir,char *path);
char *cutoff(char *path);
int main(int argc, char *argv[]){
    if(argc < 2){
        exit(-1);
    }
    char path[BUF_SIZE];
    //char * path = (char *)malloc(BUF_SIZE*sizeof(char));
    char dir[BUF_SIZE];
    strcpy(dir,argv[1]);
    strcpy(path,argv[2]);
    find(dir,path);
    free(path);
    exit(0);
}

void find(char *dir, char *path){
    int fd;
    struct dirent de;
    struct stat st;
    fd = open(dir,0);
    if(fd < 0){
        fprintf(2,"open error\n");
        return;
    }

    if(fstat(fd,&st)<0){
        fprintf(2,"stat error\n");
        close(fd);
        exit(1);
    }
    char *p;
    int str_len;
    switch(st.type){
        case T_FILE:
            p = cutoff(dir);
            if(!strcmp(p,path)){
                printf("%s%s",dir,path);
            }
            break;

        case T_DIR:
            p = dir+strlen(dir);
            *p++ = '/';
            while((str_len = read(fd,(void *)&de,sizeof(de))) == sizeof(de)){
                if(str_len == 0)
                    return;
                if(de.inum == 0)
                    continue;
                if(!strcmp(de.name,".")||!strcmp(de.name,"..")){
                    continue;
                }
                memmove(p,de.name,strlen(de.name)+1);

                if(!strcmp(de.name,path)){
                    printf("%s\n",dir);
                }
                //printf("dir %s\n",dir);
                stat(dir,&st);
                if(st.type == 1){
                    find(dir,path);
                }
            }
            break;
    }
}
char *cutoff(char *path){
    char *p;
    for(p = path+strlen(path);p >= path &&*p != '/';p--);
    p++;
    return p;
}