#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd;
    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    char response[1024];
    char buffer[1024]="hello server";

    sockfd= socket(AF_INET,SOCK_DGRAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr *)&server,sizeof(server));
    recvfrom(sockfd,response,sizeof(response),0,(struct sockaddr *)&server,&len);
    printf("message from server: %s\n",response);

    close(sockfd);
    return 0;
}