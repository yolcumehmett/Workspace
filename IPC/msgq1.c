#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX 20

struct msg_buffer
{
  long msg_type;
  char msg_text[100];
} message;


int main ()
{
  key_t key1,key2,key3;
  int msgid1,msgid2,msgid3;

  key1 = ftok("process1",11);
  key2 = ftok("process2",22);
  key3 = ftok("process3",33);

  msgid1 = msgget(key1,0666|IPC_CREAT);
  message.msg_type = 1;
  msgid3 = msgget(key3,0666|IPC_CREAT);

  printf("write data : \n");
  fgets(message.msg_text,MAX,stdin);
  sleep(5);
  msgsnd(msgid1,&message,sizeof(message),0);

  printf("data sent is : %s \n",message.msg_text);
  
  msgrcv(msgid3,&message,sizeof(message),1,0);
  printf("data received : %s \n",message.msg_text);
  printf("1.tur tamamlandi.");
  return 0;
}

