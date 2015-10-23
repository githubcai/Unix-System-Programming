#include "us_xfr.h"
#include <errno.h>
#include <unistd.h>

#define BACKLOG 5

int main(int argc, char *argv[]){
    struct sockaddr_un addr;
    int sfd, cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd==-1){
        FatalError("scoket");
    }

    if(remove(SV_SOCK_PATH)==-1 && errno!=ENOENT){
        printf("remove-%s\n", SV_SOCK_PATH);
        exit(1);
    }

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

    if(bind(sfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_un))==-1){
        FatalError("bind");
    }

    if(listen(sfd, BACKLOG) == -1){
        FatalError("listen");
    }

    for(;;){
        cfd = accept(sfd, NULL, NULL);
        if(cfd==-1){
            FatalError("accept");
        }

        while((numRead=read(cfd, buf, BUF_SIZE))>0){
            if(write(STDOUT_FILENO, buf, numRead)!=numRead){
                FatalError("partial/failed write");
            }
        }

        if(numRead==-1){
            FatalError("read");
        }
        if(close(cfd)==-1){
            FatalError("close");
        }
    }

    exit(EXIT_SUCCESS);    
}
