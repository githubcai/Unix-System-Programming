struct sockaddr_un addr;

memset(&addr, 0, sizeof(struct sockaddr_un));
addr.sun_family = AF_UNIX;

strncpy(&addr.sun_path[1], "xyz", sizeof(addr.sun_path)-2);

sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
if(sockfd==-1){
    FatalError("socket");    
}

if(bind(sockfd, (struct sockaddr*)&addr), sizeof(struct sockaddr_un)==-1){
    FatalError("bind");
}
