#include "ud_ucase.h"
#include <stdlib.h>
#include <stdio.h>
#include "fatal.h"

int main(int argc, char *argv[]){
    struct sockaddr_un svaddr, claddr;
    int sfd, j;
    size_t msgLen;
    ssize_t numBytes;
    char resp[BUF_SIZE];

    if(argc<2 || strcmp(argv[1], "--help")==0){
        printf("%s msg...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(sfd==-1){
        FatalError("socket");
    }

    memset(&claddr, 0, sizeof(struct sockaddr_un));
    claddr.sun_family = AF_UNIX;
    snprintf(claddr.sun_path, sizeof(claddr.sun_path), "/tmp/ud_ucase_cl.%ld", (long)getpid());

    if(bind(sfd, (struct sockaddr*)&claddr, sizeof(struct sockaddr_un))==-1){
        FatalError("bind");
    }

    memset(&svaddr, 0, sizeof(struct sockaddr_un));
    svaddr.sun_family = AF_UNIX;
    strncpy(svaddr.sun_path, SV_SOCK_PATH, sizeof(svaddr.sun_path)-1);

    for(j=1;j<argc;j++){
        msgLen = strlen(argv[j]);
        if(sendto(sfd, argv[j], msgLen, 0, (struct sockaddr*)&svaddr, sizeof(struct sockaddr_un))!=msgLen){
            FatalError("sendto");
        }

        numBytes = recvfrom(sfd, resp, BUF_SIZE, 0, NULL, NULL);
        if(numBytes==-1){
            FatalError("recvfrom");
        }
        printf("Response %d: %.*s\n", j, (int)numBytes, resp);
    }

    remove(claddr.sun_path);
    exit(EXIT_SUCCESS);
}
