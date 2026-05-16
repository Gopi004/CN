#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/time.h>

#define TIMEOUT 3

int main(){
    int sockfd;
    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    char buffer[1024]={0};
    char packet[50];
    struct timeval tv;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr *)&server,sizeof(server));
    printf("Connection established\n");

    tv.tv_sec=TIMEOUT;
    tv.tv_usec=0;
    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&tv,sizeof(tv));

    int packet_no=1;
    while(packet_no<=5){
        sprintf(packet,"%d",packet_no);
        printf("Sending packet %d: \n",packet_no);
        send(sockfd,packet,strlen(packet),0);

        int valread=read(sockfd,buffer,sizeof(buffer));
        if(valread>0&&strcmp(buffer,"ACK")==0){
            printf("ACK recieved for packet%d\n\n",packet_no);
            packet_no++;
        }
        else{
            printf("Timeout, Retransmitting packet %d\n\n",packet_no);
        }
        memset(buffer,0,sizeof(buffer));
    }
    printf("All packets sent successfully\n");
    close(sockfd);
}