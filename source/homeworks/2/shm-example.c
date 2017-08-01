#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
    key_t key = IPC_PRIVATE;
    size_t size = 1024; // Size of the region
    int shm_flag = IPC_CREAT | SHM_W | SHM_R; // For creating or getting a segment
    int shm_id = shmget(key, size, shm_flag);

    if(!shm_id){
        printf("Región no fue creada con éxito");
        exit(1);
    }

    char *data = shmat(shm_id, (void *)0, 0);

    if(data == (char *)(-1)){
        printf("No hay puntero a la región");
        exit(1);
    }

    printf("Shared contents: %s\n", data);

    // Detach
    if(shmdt((void *) data)){
        printf("No se pudo detach");
        exit(1);
    }

    // Delete segment
    shmctl(shm_id, IPC_RMID, NULL);
    printf("Deleted!");
    
    return 0;
}