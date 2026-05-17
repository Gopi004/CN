#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd;
    struct sockaddr_in server;
    char filename[1024],buffer[1024]={0};
    int n;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");
    server.sin_port=htons(8080);

    connect(sockfd,(struct sockaddr *)&server,sizeof(server));

    printf("Enter the filename: ");
    scanf("%s",filename);

    send(sockfd,filename,strlen(filename),0);

    printf("File contents:\n");
    while((n=read(sockfd,buffer,sizeof(buffer)))>0){
        buffer[n]='\0';
        printf("%s",buffer);
    }
    printf("\n");
    close(sockfd);
    return 0;
}