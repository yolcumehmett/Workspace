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
#include <sys/ipc.h>       
#include <fcntl.h>          
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1);
}

int main(){
    int fd = shm_open(NAME,O_CREAT|O_RDWR,0666);
    void *ptr;
    if (fd<0){
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    ftruncate(fd,SIZE);
    ptr= mmap(NULL,SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if ((caddr_t) -1  == ptr) report_and_exit("Can't get segment...");
    printf("sender mapped address: %p\n",ptr);
    

    json_object *jobj = json_object_new_object();
    json_object *yas = json_object_new_int(22);
    json_object *numara= json_object_new_int(42);
    json_object_object_add(jobj,"Yas",yas);
    json_object_object_add(jobj,"Numara",numara);
    printf("The json object created: %s",json_object_to_json_string(jobj));
     
    strcpy(ptr,json_object_to_json_string(jobj));
    

    
    munmap(ptr,SIZE);
    close(fd);
    json_object_put(jobj);

return EXIT_SUCCESS;
}