#include <stdio.h>
#include <math.h>
#include <time.h>
#include<stdlib.h>
#include<pthread.h>
#include<sched.h>

float timings[25];
int i=0;

void* CountA()
{
    clock_t start, end;
    start = clock();
    for (long long i = 0; i < pow(2, 32); i++)
    {;}
    end = clock();
    
    printf("Time used by CountA : %f Seconds\n", (float) (end - start)/CLOCKS_PER_SEC);
    timings[i++]=(float) (end - start)/CLOCKS_PER_SEC;
    return NULL;

}

void* CountB()
{
    clock_t start, end;
    start = clock();
    for (long long i = 0; i < pow(2, 32); i++)
    {
        ;
    }
    end = clock();
    printf("Time used by CountB : %f Seconds\n", (float) (end - start)/CLOCKS_PER_SEC);
    timings[i++]=(float) (end - start)/CLOCKS_PER_SEC;
    return NULL;
}

void* CountC()
{
    clock_t start, end;
    start = clock();
    for (long long i = 0; i < pow(2, 32); i++)
    {
        ;
    }
    end = clock();
    printf("Time used by CountC : %f Seconds\n", (float) (end - start)/CLOCKS_PER_SEC);
    timings[i++]=(float) (end - start)/CLOCKS_PER_SEC;
    return NULL;
}


void function(int x){

    pthread_t CountA_thread, CountB_thread, CountC_thread;

    pthread_create(&CountA_thread,NULL,&CountA,NULL);
    struct sched_param CountA_param;
    pthread_setschedparam(CountA_thread,SCHED_OTHER, &CountA_param);
    CountA_param.sched_priority=x;
    pthread_join(CountA_thread,NULL);    
    

    pthread_create(&CountB_thread,NULL,&CountB,NULL);
    struct sched_param CountB_param;
    CountB_param.sched_priority=x;
    pthread_setschedparam(CountB_thread,SCHED_RR, &CountB_param);
    pthread_join(CountB_thread,NULL);    


    pthread_create(&CountC_thread,NULL,&CountC,NULL);
    struct sched_param CountC_param;
    CountC_param.sched_priority=x;
    pthread_setschedparam(CountC_thread,SCHED_FIFO, &CountC_param);
    pthread_join(CountC_thread,NULL);    
}


int main()
{   
    FILE *file=fopen("output.txt","w+");
    function(1);
    function(20);
    function(40);
    function(60);
    function(80);
    function(99);
    for(int i=0;i<16;i=i+3){
        fprintf(file,"%f %f %f\n", timings[i],timings[i+1],timings[i+2]);

    }
}