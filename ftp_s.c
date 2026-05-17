#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd,newsock;
    struct sockaddr_in server,client;
    socklen_t len=sizeof(client);
    char filename[1024],buffer[1024];
    FILE *fp;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port=htons(8080);

    bind(sockfd,(struct sockaddr *)&server,sizeof(server));
    listen(sockfd,5);

    newsock=accept(sockfd,(struct sockaddr *)&client,&len);

    int n=read(newsock,filename,sizeof(filename));
    filename[n]='\0';
    
    fp=fopen(filename,"r");
    if(fp==NULL){
        send(newsock,"File not found",14,0);
    }
    else{
        while(fgets(buffer,sizeof(buffer),fp)!=NULL){
            send(newsock,buffer,strlen(buffer),0);
        }
        fclose(fp);
    }
    close(newsock);
    close(sockfd);
    return 0;
}