#include "protocol.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/shm.h>        
#include <fcntl.h>          
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>

int main(){
    int fd = shm_open(NAME,O_RDONLY,0666);
    void *ptr;
    if (fd<0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    ptr = mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    shmg
munmap(ptr,SIZE);
close(fd);
shm_unlink(NAME);
return EXIT_SUCCESS;
}