#include <sys/un.h>
#include <sys/socket.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 10

#define SV_SOCK_PATH "/tmp/ud_ud_ucase"
