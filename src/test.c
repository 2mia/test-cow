#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define PAGESIZE 4096
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
    sleep(3);
    // sout("child set 'x'");
    // memset(buf[idx], 'x', 4096);
    // sout("child has new data");
    sout("child: freeing up");
    for (int i = 0; i < BUFS; i++){
        free(buf[i]);
    }
}
int parent(){
    sleep(1);
    for (int i = 0; i < BUFS; i++){
        free(buf[i]);
        buf[i] = NULL;
    }
}

int main(int argc, char **argv){

    buf = malloc(sizeof(char*)*BUFS);

    for (int i = 0; i < BUFS; i++){
        // buf[i] = malloc(PAGESIZE);
        posix_memalign(((void**)&(buf[i])), 16, PAGESIZE);
        // buf[i] = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (buf[i] == NULL){//MAP_FAILED
            sout("ERROR: failed to allocate");
            buf[i] = NULL;
        }else{
            buf[i][0] = 'p';
        }
    }

    for (int i = 0; i < 3; i++){
        if (fork() == 0){
            child(i);
            return 0;
        }
    }
    parent();
    int status = 0;
    while (wait(&status) > 0);
    sleep(5);
    return 0;
}
