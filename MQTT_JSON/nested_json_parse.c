#include<stdio.h>
#include<string.h>
#include<json-c/json.h>
#include<json-c/json_util.h>
#include <json-c/json_object.h>
#include <json-c/json_visit.h>




int main(int argc, char **argv) {
	FILE *fp;
	int rv;
	char buffer[1024];
	
	struct json_object *jobj;
	struct json_object *newobj;
	struct json_object *newobj2;
	struct json_object *newobj3;
	struct json_object *jstring;
	struct json_object *jstring1;
	struct json_object *jstring2;
	struct json_object *jstring3;
	struct json_object *jboolean;
	struct json_object *jdouble;
	struct json_object *jarray;
    struct json_object *jint;
	size_t n_jarray;

	size_t i;	

	fp = fopen("nested.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	jobj = json_tokener_parse(buffer);
	//rv = json_c_visit(jobj,0,emit_object,NULL);
	//printf("json_c_visit(string)=%d\n",rv);
	

	//json_object_object_get_ex(jobj, "Informations", &jstring);
	json_object_object_get_ex(jobj, "School", &jstring1);
	//json_object_object_get_ex(jstring1, "Level", &newobj2);
	newobj=json_object_array_get_idx(jstring1, 0);
	//json_object_object_get_ex(jobj, "Year", &jint);
	json_object_object_get_ex(newobj, "Department", &jstring2);
	json_object_object_get_ex(jobj,"Personal",&jstring);
	newobj2=json_object_array_get_idx(jstring,0);
	json_object_object_get_ex(newobj2,"Gender",&jstring3);
	
	//json_object_object_get_ex(jobj, "Number of posts", &jint);
	//json_object_object_get_ex(jobj, "Categories", &jarray);

	//printf("Informations: %s\n", json_object_get_string(jstring));
	printf("Output: %s\n", json_object_get_string(jstring2));
	printf("Output: %s\n", json_object_get_string(jstring3));
	printf("Output: %s\n", json_object_get_string(newobj));
	printf("Output: %s\n", json_object_get_string(jobj));
	printf("Output: %s\n", json_object_get_string(newobj2));
	//printf("Output: %s\n", json_object_get_string(newobj2));
	//printf("Output: %s\n", json_object_get_string(jstring));
	//printf("Output1: %d\n", json_object_get_int(jint));
	//printf("Number of posts: %d\n", json_object_get_int(jint));

	/*n_jarray= json_object_array_length(jarray);
	printf("Found %lu friends\n",n_jarray);*/

	/*for(i=0;i<n_jarray;i++) {
		jarray = json_object_array_get_idx(jarray, i);
		printf("%lu. %s\n",i+1,json_object_get_string(jarray));
	}	*/
}

