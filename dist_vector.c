#include <stdio.h>
#define INFINITY 9999
#define MAX 10

int nodes;
int dist[MAX][MAX],cost[MAX][MAX],next_hop[MAX][MAX];

void initialize(){
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            dist[i][j]=cost[i][j];
            next_hop[i][j]=j;
        }
    }
}

void update(){
    int updated;
    do{
        updated=0;
        for(int i=0;i<nodes;i++){
            for(int j=0;j<nodes;j++){
                for(int k=0;k<nodes;k++){
                    if(dist[i][j]>dist[i][k]+dist[k][j]){
                        dist[i][j]=dist[i][k]+dist[k][j];
                        next_hop[i][j]=next_hop[i][k];
                        updated=1;
                    }
                }
            }
        }
    }while(updated);
}

void display(){
    for(int i=0;i<nodes;i++){
        printf("\nNode %d's Routing Table:\n",i+1);
        printf("Destination\tCost\tNext Hop\n");
        for(int j=0;j<nodes;j++){
            printf("%d\t%d\t%d\n",j+1,dist[i][j],next_hop[i][j]+1);
        }
    }
}

void main(){
    printf("Enter the no. of routers: ");
    scanf("%d",&nodes);

    printf("Enter the code matrix(enter 9999 if no direct link):\n");
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            scanf("%d",&cost[i][j]);
            if(i==j){
                cost[i][j]=0;
            }
        }
    }
    initialize();
    update();
    display();
}