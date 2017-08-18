#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


void handler(int code) {
    printf("\n\nAdiós\n\n");
    printf("%d\n", code);
    exit(0);
}

int main(int argc, char *argv[]) {
    signal(SIGTSTP, handler);
    printf("%d\n", SIGTSTP);
    int i = 0;
    while (1) {
        i++;
        printf("Esperando %f segundos\n", (i / 5.0));
        sleep(i / 5.0);
    }
    return 0;
}