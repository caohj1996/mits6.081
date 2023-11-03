#include <kernel/param.h>
#include "user/user.h"
#define BUF_SIZE 30
#define MAXARG 32
int main(int argc, char *argv[])
{
    struct args
    {
        char *args[MAXARG];
        int size;
    } arg;
    arg.size = 0;
    for (int i = 0; i < argc - 1; ++i)
    {
        arg.args[i] = malloc(14 * sizeof(char));
        strcpy(arg.args[i], argv[i + 1]);
        arg.size++;
    }
    int fd;
    char buf[BUF_SIZE];
    int size = 0;
    char *p = buf;
    char *q = buf;
    int origin_size = arg.size;
    int str_len;
    while (1)
    {
        str_len = read(0, &buf[size], 1);
        if(!str_len){
            for(int i = 0; i < arg.size; ++i){
                    free(arg.args[i]);
                }
            break;
        }
        if (buf[size] == '\n')
        {
            q = &buf[size - 1];
            arg.args[arg.size] = malloc(14 * sizeof(char));
            int i;
            for (i = 0; p <= q; p++, i++)
            {
                arg.args[arg.size][i] = *p;
            }
            i++;
            arg.args[arg.size][i] = '\0';
            arg.size++;
            arg.args[arg.size] = malloc(1 * sizeof(char));
            strcpy(arg.args[arg.size],"");
            arg.size++;
            // for(int i = 0; i < arg.size; ++i){
            //     printf("%d,%s\n",i,arg.args[i]);
            // }
            // printf("------------------------------\n");
            fd = fork();
            if (fd == -1)
            {
                fprintf(2, "fd sibila\n");
            }
            if (fd == 0)
            {
                exec(arg.args[0], arg.args);
                exit(0);
            }
            else
            {
                wait(&fd);
                for(int j = origin_size; j < arg.size;j++){
                    free(arg.args[j]);
                }
            }
            
            arg.size = origin_size;
            size = -1;
            p = buf;
            q = buf;
        }
        else if (buf[size] == ' ')
        {
            q = &buf[size];
            arg.args[arg.size] = malloc(14 * sizeof(char));
            int i;
            for (i = 0; p < q; p++, i++)
            {
                arg.args[arg.size][i] = *p;
            }
            p++;
            arg.args[arg.size][i] = '\0';
            arg.size++;
        }
        size++;
    }

    exit(0);
}
