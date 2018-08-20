#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>

#define PAGESIE 4096
#define BUFS 512*1024
char **buf = NULL;

int sout(const char *format, ...){
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsprintf(dest, format, argptr);
    va_end(argptr);
    printf("%s\n", dest);
    fflush(stdout);
}

int child(int idx){
    sleep(1);
    sout("child set 'x'");
    memset(buf[idx], 'x', 4096);
    // sout("child has new data");
    sout("child: freeing up");
    for (int i = 0; i < BUFS; i++){
        free(buf[i]);
    }
    sleep(5);
}

int main(int argc, char **argv){

    buf = malloc(sizeof(char*)*BUFS);

    for (int i = 0; i < BUFS; i++){
        buf[i] = malloc(PAGESIE);
        if (!buf[i])
            sout("ERROR: failed to allocate");
    }

    for (int i = 0; i < 3; i++){
        if (fork() == 0){
            child(i);
            return 0;
        }
    }
    int status = 0;
    while (wait(&status) > 0);
    return 0;
}
