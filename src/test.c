 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 int main(int argc, char **argv){
    int SIZE_MB = 50*1024*1024;
    char buf_stack[2*1024*1024] = {0,};
    printf("alloc\n");fflush(stdout);
    char *buf = malloc(SIZE_MB);
    
    if (fork() == 0){   // Child
        sleep(1);
        printf("child set 'x'\n");fflush(stdout);
        memset(buf, 'x', SIZE_MB);
        printf("child has new data\n");fflush(stdout);

    }else{              // Parent
        printf("parent set 'y'\n");fflush(stdout);
        memset(buf, 'y', SIZE_MB);
        printf("parent has new data\n");fflush(stdout);
        free(buf); buf = NULL;
        sleep(1);
    }

    sleep(9);

    printf("freeing up\n");fflush(stdout);
    free(buf);
    return 0;
 }
