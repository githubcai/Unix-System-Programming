#include <syslog.h>
#include "id_echo.h"

int main(int argc, char *argv[]){
    int sfd;
    ssize_t numRead;
    socklen_t addrlen, len;
    struct sockaddr_storage claddr;
    char buf[BUF_SIZE];
    char addrStr[IS_ADDR_STR_LEN];

    
}
