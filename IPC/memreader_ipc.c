/** Compilation: gcc -o memreader memreader.c -lrt -lpthread **/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>       
#include <fcntl.h>          
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include "protocol.h"

void report_and_exit(const char* msg) {
  perror(msg);
  exit(-1);
}

int main() {

  int ByteSize;
  void *memptr;

  ByteSize=sizeof(veri);
  veri *gelen_mesaj = NULL;
  gelen_mesaj=calloc(1,ByteSize);
  int fd = shm_open(BackingFile, O_RDONLY, AccessPerms);  /* empty to begin */
  if (fd < 0) {
    printf("fd: %d",fd);
    report_and_exit("Can't get file descriptor...");
  }
  ByteSize=sizeof(veri);
  /* get a pointer to memory */
  memptr = mmap(NULL,       /* let system pick where to put segment */
			ByteSize,   /* how many bytes */
			PROT_READ , /* access protections */
			MAP_SHARED, /* mapping visible to other processes */
			fd,         /* file descriptor */
			0);         /* offset: start at 1st byte */
      


  printf("memptr: %s ", (char *)memptr);

  memcpy(gelen_mesaj,memptr,ByteSize); /* copy some ASCII bytes to the segment */
       
  printf("yas:%d numara:%d\n",gelen_mesaj->yas, gelen_mesaj->numara);

  return 0;
}
