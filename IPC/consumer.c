#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define file "file.dat"

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1); /* EXIT_FAILURE */
}

int main() {
  struct flock lock;
  lock.l_type = F_WRLCK;    
  lock.l_whence = SEEK_SET; 
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();    
  
  int fd; 
  if ((fd = open(file, O_RDONLY)) < 0)  
    report_and_exit("open to read failed...");

  fcntl(fd,F_GETLK,&lock);
  if(lock.l_type != F_UNLCK)
    report_and_exit("file is still write locked.");
  
  lock.l_type = F_RDLCK;
  if(fcntl(fd,F_SETLK,&lock)<0)
    report_and_exit("can't get a read-only lock.");
 
 int c;
 while(read(fd,&c,1)>0)
  write(STDOUT_FILENO,&c,1);

 lock.l_type = F_UNLCK;
 if(fcntl(fd,F_SETLK,&lock)<0)
   report_and_exit("explicit unlocking failed.");
  //printf("%d\n",lock.l_pid);
  //printf("%d",lock.l_type);

 close(fd);
return 0;

}