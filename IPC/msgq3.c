#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 20

struct msg_buffer
{
  long msg_type;
  char msg_text[100];
} message;


int main ()
{
  key_t key1,key2,key3;
  int msgid1,msgid2,msgid3;;

  key1 = ftok("process1",11);
  key2 = ftok("process2",22);
  key3 = ftok("process3",33);

  msgid2 = msgget(key2,0666|IPC_CREAT);
  msgid3 = msgget(key3,0666|IPC_CREAT);
  message.msg_type = 1;

  msgrcv(msgid2,&message,sizeof(message),1,0);

  printf("data received : %s \n",message.msg_text);
  
  message.msg_type = 1;

  printf("write data : \n");
  fgets(message.msg_text,MAX,stdin);
  sleep(5);
  msgsnd(msgid3,&message,sizeof(message),0);
  
  printf("data sent is : %s \n",message.msg_text);
  
  
  return 0;
}

