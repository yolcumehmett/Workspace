#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define file "file.dat"
#define filedata "PALTO\nNikolay Vasilievich Gogol\n1842\n"

void report_and_exit(const char* msg){
    perror(msg);
    exit(-1);
}

int main(){
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;        
    lock.l_len = 0;           
    lock.l_pid = getpid(); 

    int fd;
    if ((fd=open(file,O_RDWR | O_CREAT,0666))<0)
      report_and_exit("open failed");

    if (fcntl(fd,F_SETLK,&lock)<0)
      report_and_exit("fcntl failed to lock"); 
    else{
        write(fd, filedata,strlen(filedata));
        fprintf(stderr, "process %d written to data file\n", lock.l_pid);
    }

    lock.l_type = F_UNLCK;
    if (fcntl(fd,F_SETLK,&lock)<0)
        report_and_exit("explicit unlocking failed.");
    close(fd);
    return 0;
    
}