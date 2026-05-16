#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<time.h>

int main(){
    int sockfd,newsock;
    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    char buffer[1024]={0};
    int ack_prob=70;
    srand(time(0));

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr *)&server,len);
    listen(sockfd,3);
    printf("Waiting for connection\n");

    newsock=accept(sockfd,(struct sockaddr *)&server,&len);
    printf("Connection established\n");

    while(1){
        int readval=read(newsock,buffer,sizeof(buffer));
        if(readval==0){
            break;
        }

        printf("Recieved packet: %s\n",buffer);
        if(rand()%100<ack_prob){
            printf("ACK sent for packet: %s\n\n",buffer);
            send(newsock,"ACK",3,0);
        }
        else{
            printf("ACK lost for packet: %s\n\n",buffer);
        }
        memset(buffer,0,sizeof(buffer));
    }
    close(sockfd);
    close(newsock);
    return 0;
}