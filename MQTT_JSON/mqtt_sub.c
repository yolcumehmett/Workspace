#include <stddef.h>
#include <stdio.h>
#include <mosquitto.h>
#include <string.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>

void on_connect(struct mosquitto *mosq, void *obj, int rc)
{

    printf("ID: %d\n", *(int *)obj);

    if (rc)
    {
        printf("Error with the result code: %d\n", rc);
        exit(-1);
    }
    mosquitto_subscribe(mosq, NULL, "test/t1", 0);
    mosquitto_subscribe(mosq, NULL, "test/t2", 0);
    mosquitto_subscribe(mosq, NULL, "salla", 0);
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{

    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *categ;
    struct json_object *age;
    struct json_object *friends;
    struct json_object *friend;
    struct json_object *jvaluearray;
    size_t n_friends;
    int i;

    // printf("New message with topic %s: %s\n",msg->topic,(char*)msg->payload);
    
    if (strcmp("test/t1",msg->topic) == 0){

        parsed_json = json_tokener_parse(msg->payload);

        json_object_object_get_ex(parsed_json, "Name", &name);

        printf("Name: %s\n", json_object_get_string(name));
        printf("mesaj uzunluğu: %d\n", msg->payloadlen);
        printf("isim uzunluğu: %d\n", json_object_get_string_len((name)));
    } 
    else if (strcmp("test/t2",msg->topic) == 0){
        
        parsed_json = json_tokener_parse(msg->payload);

        json_object_object_get_ex(parsed_json, "Name", &name);
        json_object_object_get_ex(parsed_json, "friends", &categ);

        printf("Name: %s\n", json_object_get_string(name));
        printf("arkadaslar: %s\n", json_object_get_string(categ));
        
        jvaluearray = json_object_array_get_idx(categ,1);

        printf("2. arkadas : %s\n", json_object_get_string(jvaluearray));
        
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
