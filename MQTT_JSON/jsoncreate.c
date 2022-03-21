#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <json-c/json.h>
#include <json-c/json_util.h>
#include <json-c/json_object.h>
#include <unistd.h>




/*void printRandoms(int lower, int upper, 
                             int count)
{
    int i;
   
    while(1){
        
        for (i = 0; i < count; i++) {
        
        jint = (rand() %
           (upper - lower + 1)) + lower;
        printf("%d ", num);
        sleep(5);
    }
    }
}
*/

int main() {
  
  int lower = 10000, upper = 99999, count = 2, num, i;
    
  
    while(1){
        
        
        
        num = (rand() %
           (upper - lower + 1)) + lower;
        
  
  json_object *jobj = json_object_new_object();
  json_object *newobj = json_object_new_object();
  json_object *newobj1 = json_object_new_object();
  json_object *newobj2 = json_object_new_object();
  json_object *jstring = json_object_new_string("Students");
  json_object *jboolean = json_object_new_boolean(1);
  json_object *jdouble = json_object_new_double(3.14);
  json_object *jarray = json_object_new_array();
  json_object *jarray1 = json_object_new_array();
  json_object *jarray2 = json_object_new_array();
  json_object *jarray3 = json_object_new_array();
  json_object *jstring1 = json_object_new_string("Mehmet Yolcu");
  json_object *jstring2 = json_object_new_string("Male");
  json_object *jstring3 = json_object_new_string("Konya");
  json_object *jstring4 = json_object_new_string("Gurhanlar St.");
  json_object *jstring5 = json_object_new_string("Bachelor of Science");
  json_object *jstring6 = json_object_new_string("EEE");
  json_object *jint = json_object_new_int(22);
  json_object *jint1 = json_object_new_int(num);
  json_object_object_add(jobj,"Informations", jstring);
  json_object_object_add(newobj,"Name", jstring1);
  json_object_object_add(newobj,"Gender", jstring2);
  json_object_object_add(newobj,"Age", jint);
  json_object_object_add(newobj,"Address", newobj1);
  json_object_object_add(newobj1,"City", jstring4);
  json_object_object_add(newobj1,"Street", jstring3);
  json_object_object_add(newobj1,"Postal Code", jint1);
  json_object_object_add(newobj2,"Level", jstring5);
  json_object_object_add(newobj2,"Department", jstring6);
  json_object_object_add(newobj2,"Year", jboolean);
  json_object_object_add(jobj,"Personal", newobj);
  json_object_object_add(jobj,"School", newobj2);
  printf ("The json object created: %s",json_object_to_json_string(jobj));

  sleep(5);      
    
    }
    // Use current time as 
    // seed for random generator
    srand(time(0));
  
   
    
  

  return 0;
}