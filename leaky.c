#include<stdio.h>
#include<stdlib.h>

void leaky(int bucket_cap, int leak_rate, int num, int packets[num]){
    int bucket=0;
    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for(int i=0;i<num;i++){
        printf("%d\t%d\t",i+1,packets[i]);
        bucket+=packets[i];

        if(bucket>bucket_cap){
            printf("%d(overflowed)\t",bucket_cap);
            bucket=bucket_cap;
        }
        else{
            printf("%d\t",bucket);
        }

        int leaked=(bucket>leak_rate)?leak_rate:bucket;
        bucket-=leaked;
        printf("%d\t%d\n",leaked,bucket);
    }

    int time=num+1;
    while(bucket>0){
        int leaked=(bucket>leak_rate)?leak_rate:bucket;
        printf("%d\t%d\t%d\t%d\t%d\n",time,0,bucket,leaked,bucket-leaked);
        bucket-=leaked;
        time++;
    }
}

void main(){
    int bucket_cap,leak_rate,num;
    
    printf("Enter the bucket capacity: ");
    scanf("%d",&bucket_cap);

    printf("Enter the leak rate: ");
    scanf("%d",&leak_rate);

    printf("Enter the no. of packets: ");
    scanf("%d",&num);

    int packets[num];
    printf("Enter the packets:\n");
    for(int i=0;i<num;i++){
        scanf("%d",&packets[i]);
    }

    leaky(bucket_cap,leak_rate,num,packets);
}