#include <stdio.h>

typedef struct{
    int arrival_time, waiting_time, burst_time, tat, priority;
    int status, pno;
}queue;

int main(){

    int n=0, time = 0, i=0, pno=0, aux=0;
    int tat=0, burst_time=0, total_time=0;
    float avg_tat=0;
    queue queue[100];

    scanf("%d", &n);

    for( i=0; i < n; i++ ){
        scanf("%d %d %d", &queue[i].arrival_time, &queue[i].priority, &queue[i].burst_time);
        queue[i].status = 0;
        queue[i].pno = i;
        burst_time += queue[i].burst_time;
    }

    total_time+=burst_time;

    if( queue[0].arrival_time != 0){
        for(time=0; time < queue[0].arrival_time; time++){
            printf("%d-IDLE\n",time);
            total_time+=1;
        }
    }

    for(i=1; i < n; i++){
        if(queue[i].arrival_time == queue[pno].arrival_time && queue[i].priority < queue[pno].priority){
            pno = i;
        }
    }

    for( time = queue[pno].arrival_time; time < total_time; time++ ){

        for(i=0; i < n; i++){
            if( queue[i].arrival_time == time ){ queue[i].status = -1; /*printf("P%d NOW WAITING ----> %d\n",queue[i].pno+1,queue[i].status);*/ }
        }

        for(i = 0; i < n; i++){
            if( queue[i].arrival_time == time 
            && queue[i].status == -1 
            && queue[i].priority < queue[pno].priority ){
                queue[pno].status = 2;
                //printf("INTERRUPTION STATUS FOR P%d ----> %d\n",queue[pno].pno+1,queue[pno].status);
                pno = i;
                //printf("INTERRUPTED BY P%d\n",queue[i].pno+1);
            }else if(queue[pno].burst_time == 0){
                if(queue[i].arrival_time <= time && queue[i].status == -1){
                    pno = i;
                }
            }
        }
        
        if( queue[pno].burst_time == 0){
            printf("%d-IDLE\n", time);
            total_time+=1;
            for(i = 0; i < n; i++){
                if( queue[i].status == 0 && queue[i].priority < queue[pno].priority && queue[i].arrival_time == queue[pno].arrival_time){
                        pno = i;
                }else if( queue[i].status == 0 && queue[i].arrival_time == time+1) pno = i;
            }
            continue;
        }else{
            printf("%d-P%d\n", time, pno+1);
            queue[pno].status = 1;
            queue[pno].burst_time -= 1;
        }
        
        //printf("BURST LEFT FOR P%d :: %d\n",queue[pno].pno+1, queue[pno].burst_time);

        if( queue[pno].burst_time == 0 ){
            queue[pno].status = 3;
            //printf("FINISHED PROCESS P%d ----> %d\n",queue[pno].pno+1,queue[pno].status);
            queue[pno].tat = (time+1 - queue[pno].arrival_time);
            tat += queue[pno].tat;
            //printf("TAT P%d:%d\n", queue[pno].pno+1,queue[pno].tat);
            //printf("Soma TAT : %d\n", tat);
            aux = pno;
            for(i = 0; i < n; i++){
                if( queue[i].status == -1 || queue[i].status == 2 ){
                    if( queue[aux].burst_time != 0
                        && queue[i].burst_time != 0
                        && queue[i].priority < queue[aux].priority ){
                        aux = i;
                    //printf("PICKED %d FROM WAITING QUEUE-> Priority : %d\n",queue[i].pno+1, queue[i].priority);
                    }else if( queue[aux].burst_time != 0
                        && queue[i].burst_time != 0 
                        && queue[i].priority == queue[aux].priority ){
                        if( i < aux ){ 
                            aux = i;
                        }else continue;
                    }else if( queue[aux].burst_time == 0 
                        && queue[i].burst_time != 0) aux = i;
                }
            
            }

            if( i == n
            && queue[aux].burst_time == 0){
                for(i = 0; i < n; i++){
                    if( queue[i].status == 2 ){
                        if( queue[aux].burst_time != 0
                            && queue[i].burst_time != 0
                            && queue[i].priority < queue[aux].priority ){
                            aux = i;
                            //printf("PICKED %d FROM INTERRUPTED-> Priority : %d\n",queue[i].pno+1, queue[i].priority);
                        }else if( queue[aux].burst_time != 0 
                            && queue[i].burst_time != 0
                            && queue[i].priority == queue[aux].priority ){
                            if( i < aux ){
                                aux = i;
                            }else continue;
                        }else if ( queue[aux].burst_time  == 0
                            && queue[i].burst_time != 0)  aux = i;         
                    }
                }
            }else if( queue[aux].burst_time != 0){
                for(i = 0; i < n; i++){
                    if ( ((queue[i].status == -1 || queue[i].status == 2)
                        && queue[i].priority <= queue[aux].priority
                        && i < aux) ) {
                        aux = i;
                    }
                }
            }
            
            pno = aux;
            aux = 0;
            continue;
        }
    
        //printf("STATUS FOR P%d :: %d\n",queue[pno].pno+1, queue[pno].status);

    }

    avg_tat = (float)tat / n;
    printf("TMC=%.1f\n",avg_tat);
    
    return 0;

}