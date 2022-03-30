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

int main(){

    int rc;
    struct mosquitto *mosq1;

    mosquitto_lib_init();

    mosq1 = mosquitto_new("publisher-test2",true,NULL);
    
    rc = mosquitto_connect(mosq1,"localhost",1883,60);
    
    json_object *jobj = json_object_new_object();
    json_object *jstring = json_object_new_string("Mehmet Yolcu");
    json_object_object_add(jobj,"Name",jstring);
    printf("The json object created: %s",json_object_to_json_string(jobj));

 
    if(rc!=0){
        printf("Client could not connect to broker! Error Code: %d\n",rc);
        mosquitto_destroy(mosq1);
        return -1;
    } 
    printf("We are now connected to the broker \n");
        
 mosquitto_publish(mosq1, NULL, "test/t2", strlen(json_object_to_json_string(jobj)),json_object_to_json_string(jobj),0,false);
 json_object_put(jobj);


mosquitto_disconnect(mosq1);
mosquitto_destroy(mosq1);

mosquitto_lib_cleanup();


//sleep(10);
return 0;
}  








    