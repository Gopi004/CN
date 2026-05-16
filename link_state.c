#include<stdio.h>
#define INF 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX],int nodes,int start){
    int cost[MAX][MAX],dist[MAX],visited[MAX],next_hop[MAX];
    int min_dist,count,next_node;

    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            if(graph[i][j]==0){
                cost[i][j]=INF;
            }
            else{
                cost[i][j]=graph[i][j];
            }
        }
    }

    for(int i=0;i<nodes;i++){
        dist[i]=cost[start][i];
        visited[i]=0;
        if(dist[i]!=INF&&i!=start){
            next_hop[i]=i;
        }
        else{
            next_hop[i]=-1;
        }
    }

    dist[start]=0;
    visited[start]=1;
    count=1;
    while(count<nodes-1){
        min_dist=INF;
        next_node=-1;

        for(int i=0;i<nodes;i++){
            if(!visited[i]&&dist[i]<min_dist){
                min_dist=dist[i];
                next_node=i;
            }
        }
        if(next_node==-1){
            break;
        }
        visited[next_node]=1;

        for(int i=0;i<nodes;i++){
            if(!visited[i]&&cost[next_node][i]!=INF){
                if(dist[i]>dist[next_node]+cost[next_node][i]){
                    dist[i]=dist[next_node]+cost[next_node][i];
                    next_hop[i]=next_hop[next_node];
                }
            }
        }
        count++;
    }

    printf("\nRouting table for router %d is:\n",start+1);
    printf("Destination\tCost\tNext Hop\n");
    for(int i=0;i<nodes;i++){
        if(i!=start){
            printf("%d\t\t%d\t%d\n",i+1,dist[i],next_hop[i]+1);
        }
    }
}

void main(){
    int graph[MAX][MAX];
    int start,nodes;

    printf("Enter the no. of nodes: ");
    scanf("%d",&nodes);

    printf("Enter the adjacent matrix (enter 0 if no edge):\n");
    for(int i=0;i<nodes;i++){
        for(int j=0;j<nodes;j++){
            scanf("%d",&graph[i][j]);
        }
    }

    printf("Enter the starting router:");
    scanf("%d",&start);

    dijkstra(graph,nodes,start-1);
}