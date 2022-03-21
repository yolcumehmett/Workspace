#include<stdio.h>
#include<json-c/json.h>
#include<json-c/json_util.h>
#include <json-c/json_object.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[1024];
	struct json_object *jobj;
	struct json_object *jstring;
	struct json_object *jboolean;
	struct json_object *jdouble;
	struct json_object *jarray;
    struct json_object *jint;
	size_t n_jarray;

	size_t i;	

	fp = fopen("jsonprint.json","r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	jobj = json_tokener_parse(buffer);

	json_object_object_get_ex(jobj, "Name", &jstring);
	json_object_object_get_ex(jobj, "Number of posts", &jint);
	json_object_object_get_ex(jobj, "Categories", &jarray);

	printf("Name: %s\n", json_object_get_string(jstring));
	printf("Number of posts: %d\n", json_object_get_int(jint));

	n_jarray= json_object_array_length(jarray);
	printf("Found %lu friends\n",n_jarray);

	for(i=0;i<n_jarray;i++) {
		jarray = json_object_array_get_idx(jarray, i);
		printf("%lu. %s\n",i+1,json_object_get_string(jarray));
	}	
}f