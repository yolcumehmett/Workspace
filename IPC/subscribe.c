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
#include <fcntl.h>          
#include <unistd.h>
#include <semaphore.h>
#include "protocol.h"



    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *yas_json;
    struct json_object *num_json;


    void *memptr;
    void *semptr;
    
    int ByteSize;

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1);
}
void on_connect(struct mosquitto *mosq, void *obj, int rc)
{

    printf("ID: %d\n", *(int *)obj);

    if (rc)
    {
        printf("Error with the result code: %d\n", rc);
        exit(-1);
    }
    mosquitto_subscribe(mosq, NULL, "test/t2", 0);
    
}

    void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{

    
    
    veri mesaj = {0};

     printf("New message with topic %s: %s\n",msg->topic,(char*)msg->payload);
    
    if (strcmp("test/t1",msg->topic) == 0){

        parsed_json = json_tokener_parse(msg->payload);

        json_object_object_get_ex(parsed_json, "Name", &name);

        printf("Name: %s\n", json_object_get_string(name));
        printf("mesaj uzunluğu: %d\n", msg->payloadlen);
        printf("isim uzunluğu: %d\n", json_object_get_string_len((name)));
    } 
     else if(strcmp("test/t2",msg->topic) == 0){
        
        parsed_json = json_tokener_parse(msg->payload);
        json_object_object_get_ex(parsed_json,"Yas",&yas_json);
        json_object_object_get_ex(parsed_json,"Numara",&num_json);
        printf("yas_json %d\n",json_object_get_int(yas_json));
        printf("mesaj->yas %d\n", mesaj.yas);
        mesaj.yas=json_object_get_int(yas_json);
        mesaj.numara=json_object_get_int(num_json);
        printf("mesaj->yas %d\n", mesaj.yas);

        int fd = shm_open(BackingFile,      /* name from smem.h */
		    O_RDWR | O_CREAT | O_EXCL, /* read/write, create if needed */
		    AccessPerms);     

        
        if (fd < 0) report_and_exit("Can't open shared mem segment...");
        ByteSize=sizeof(mesaj);
        ftruncate(fd, ByteSize); /* get the bytes */
        if (ftruncate(fd,ByteSize)==-1) report_and_exit("ftruncate");
        memptr = mmap(NULL,       /* let system pick where to put segment */
                    ByteSize,   /* how many bytes */
                    PROT_READ | PROT_WRITE, /* access protections */
                    MAP_SHARED, /* mapping visible to other processes */
                    fd,         /* file descriptor */
                    0);         /* offset: start at 1st byte */
        //if ((caddr_t) -1  == memptr) report_and_exit("Can't get segment...");
        
        fprintf(stderr, "shared mem address: %p [0..%d]\n", memptr, ByteSize - 1);
        fprintf(stderr, "backing file:       /dev/shm%s\n", BackingFile );

        /* semahore code to lock the shared mem */
        semptr = sem_open(SemaphoreName, /* name */
                    O_CREAT,       /* create the semaphore */
                    AccessPerms,   /* protection perms */
                    0);            /* initial value */
        if (semptr == (void*) -1) report_and_exit("sem_open");
        
        memcpy(&memptr,&mesaj,ByteSize); /* copy some ASCII bytes to the segment */
        //printf("content:d\n",(char*)yas_json);
        
        /* increment the semaphore so that memreader can read */
        if (sem_post(semptr) < 0) report_and_exit("sem_post");

        sleep(12); /* give reader a chance */
        
        /* clean up */
        munmap(memptr, ByteSize); /* unmap the storage */
        close(fd);
        sem_close(semptr);
        shm_unlink(BackingFile); /* unlink from the backing file */
       

        
    }
    else{
        printf("RESERVED TOPIC: \n");

        }

}
int main()
{   
   
    int rc, id = 12;
    mosquitto_lib_init();

    struct mosquitto *mosq;

    mosq = mosquitto_new("subscribe-test", true, &id);
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    rc = mosquitto_connect(mosq, "localhost", 1883, 10);



    if (rc)
    {
        printf("Could not connect to Broker with return code %d\n", rc);
        return -1;
    }
    mosquitto_loop_start(mosq);
    printf("Press enter to quit...\n");
    getchar();
    mosquitto_loop_stop(mosq, true);

    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
