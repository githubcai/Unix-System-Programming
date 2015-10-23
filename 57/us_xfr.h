#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include "fatal.h"

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 1024
