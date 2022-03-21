#include <stddef.h>
#include <stdio.h>
#include <mosquitto.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>


int main(){

    int rc;
    struct mosquitto *mosq1;

    mosquitto_lib_init();

    mosq1 = mosquitto_new("publisher-test2",true,NULL);
    
    rc = mosquitto_connect(mosq1,"localhost",1883,60);
    



  
    while(1){
   sleep(0.2);
    int lower = 10000, upper = 99999, num;
    num = (rand() %
           (upper - lower + 1)) + lower;
    json_object *jobj = json_object_new_object();
  json_object *newobj = json_object_new_object();
  json_object *newobj1 = json_object_new_object();
  json_object *newobj2 = json_object_new_object();
  json_object *jstring = json_object_new_string("Students");
  json_object *jboolean = json_object_new_boolean(1);
  json_object *jstring1 = json_object_new_string("Mehmet Yolcu");
  json_object *jstring2 = json_object_new_string("Male");
  json_object *jstring3 = json_object_new_string("Konya");
  json_object *jstring4 = json_object_new_string("Gurhanlar St.");
  json_object *jstring5 = json_object_new_string("Bachelor of Science");
  json_object *jstring6 = json_object_new_string("EEE");
  json_object *jint = json_object_new_int(22);
  
    json_object *jint1 = json_object_new_int(num);
    json_object_object_add(newobj1,"Postal Code", jint1);

    json_object_object_add(jobj,"Informations", jstring);
    json_object_object_add(newobj,"Name", jstring1);
    json_object_object_add(newobj,"Gender", jstring2);
    json_object_object_add(newobj,"Age", jint);
    json_object_object_add(newobj1,"City", jstring4);
    json_object_object_add(newobj1,"Street", jstring3);
    
    json_object_object_add(newobj2,"Level", jstring5);
    json_object_object_add(newobj2,"Department", jstring6);
    json_object_object_add(newobj2,"Year", jboolean);
    json_object_object_add(newobj,"Address", newobj1);
    json_object_object_add(jobj,"Personal", newobj);
    json_object_object_add(jobj,"School", newobj2);
    printf ("The json object created: %s",json_object_to_json_string(jobj));

 
  
   
    
    if(rc!=0){
    
        printf("Client could not connect to broker! Error Code: %d\n",rc);
        mosquitto_destroy(mosq1);
        return -1;
        
    } 
    
    printf("We are now connected to the broker \n");

    
   

 
 mosquitto_publish(mosq1, NULL, "test/t2", strlen(json_object_to_json_string(jobj)),json_object_to_json_string(jobj),0,false);
 json_object_put(jobj);

    }    

mosquitto_disconnect(mosq1);
mosquitto_destroy(mosq1);

mosquitto_lib_cleanup();

//sleep(10);
return 0;
    



    
}