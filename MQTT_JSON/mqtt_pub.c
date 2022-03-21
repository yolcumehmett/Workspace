#include <stddef.h>
#include <stdio.h>
#include <mosquitto.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>


int main(){
    char buffer[200];
      /*Creating a json object*/
  json_object * jobj = json_object_new_object();

  /*Creating a json string*/
  json_object *jstring = json_object_new_string("Joys of Programming");

  /*Creating a json integer*/
  json_object *jint = json_object_new_int(10);

  /*Creating a json boolean*/
  json_object *jboolean = json_object_new_boolean(1);

  /*Creating a json double*/
  json_object *jdouble = json_object_new_double(2.14);

  /*Creating a json array*/
  json_object *jarray = json_object_new_array();

  /*Creating json strings*/
  //json_object *jstring1 = json_object_new_string("c");
  json_object *jstring1 = json_object_new_string("java");
  json_object *jstring2 = json_object_new_string("c++");
  json_object *jstring3 = json_object_new_string("php");

  /*Adding the above created json strings to the array*/
  json_object_array_add(jarray,jstring1);
  json_object_array_add(jarray,jstring2);
  json_object_array_add(jarray,jstring3);

  /*Form the json object*/
  /*Each of these is like a key value pair*/
  //json_object_object_add(jobj,"Site Name", jstring);
  json_object_object_add(jobj,"Mehmet Yolcu", jstring);
  json_object_object_add(jobj,"Technical blog", jboolean);
  json_object_object_add(jobj,"Average posts per day", jdouble);
  json_object_object_add(jobj,"Number of posts", jint);
  json_object_object_add(jobj,"Categories", jarray);

  /*Now printing the json object*/
  printf ("The json object created: %sn",json_object_to_json_string(jobj));

    int rc;
    struct mosquitto *mosq;

    mosquitto_lib_init();

    mosq = mosquitto_new("publisher-test",true,NULL);
    
    rc = mosquitto_connect(mosq,"localhost",1883,60);
    
    if(rc!=0){
    
        printf("Client could not connect to broker! Error Code: %d\n",rc);
        mosquitto_destroy(mosq);
        return -1;
    }

    printf("We are now connected to the broker \n");

mosquitto_publish(mosq, NULL, "test/t1",6,"Hello",0,false);

mosquitto_disconnect(mosq);
mosquitto_destroy(mosq);
      
mosquitto_lib_cleanup();
return 0;
    




}
