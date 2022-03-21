#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BACKLOG 4

int main() {
    /*istemcileri dinleyen soket*/
    int s;
    /*iletişim soketi*/
    int c;
    int b;
    struct sockaddr_in sa;
    FILE *client;
    int count = 0;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    bzero(&sa, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port   = htons(PORT);

    if (INADDR_ANY)
        sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&sa, sizeof sa) < 0) {
        perror("bind");
        return 2;
    }

    listen(s, BACKLOG);

    for (;;) {
        b = sizeof sa;

        if ((c = accept(s, (struct sockaddr *)&sa, &b)) < 0) {
            perror("accept");
            return 4;
        }

        if ((client = fdopen(c, "w")) == NULL) {
            perror("fdopen");
            return 5;
        }

        fprintf(client, "%d. cevap\n", ++count);

        fclose(client);
    }
}