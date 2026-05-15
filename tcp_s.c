#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    int sockfd, newsock;
    struct sockaddr_in server,client;
    socklen_t len= sizeof(client);
    char buffer[1024];

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    sockfd.sin_family=AF_INET;
    sockfd.sin_addr.s_addr=INADDR_ANY;
    sockfd.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr *)&server, sizeof(server));
    listen(sockfd,5);

    newsock=accept(sockfd,(struct sockaddr *)&client, &len);
    read(newsock,buffer,sizeof(buffer));
    printf("Message from client: %s\n",buffer);

    send(newsock,"Hello from server!",18,0);
    close(newsock);
    close(sockfd);
    return 0;
}