#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>


void main_fork(char *shared, const int len);

int main(int argc, char **argv){
    int shared_bytes = 256;

    char *shared = mmap(NULL, shared_bytes, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    for(int i = 0; i < shared_bytes - 1; i++){
        shared[i] += 10;
    }
    printf("Contenido: %s\n", shared);

    for(int i = 0; i < 50; i++){
        if(!fork()){
            main_fork(shared, shared_bytes);
        }
    }

    printf("Parent waiting...\n");

    for(int i = 0; i < 50; i++){
        int exit_code;
        waitpid(-1, &exit_code, 0);
    }

    printf("Contenido: %s\n", shared);

    munmap(shared, shared_bytes);
    return 0;
}


void main_fork(char *shared, const int len){
    printf("Hello, I'm the fork\n");
    for(int i = 0; i < len - 1; i++){
        shared[i] += 2;
    //    usleep(9300);
    }
    printf("Fork ended\n");
    exit(0);
}