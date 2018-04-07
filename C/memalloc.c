#include <stdio.h>

int firstfit(int n, int m, int arrProcess[1000], int arrBlock[1000]){

    int i = 0, j=0, fit=0;
    int allocation[n];

    for ( i=0; i < n; i++) allocation[i]=-1;

    for (i=0; i < n; i++){
        for (j=0; j < m; j++){
            if (arrBlock[j] >= arrProcess[i]){
                allocation[i] = j;
                arrBlock[j] = arrBlock[j] - arrProcess[i];
                break;
            }
        }
    }

    for( i=0; i < n; i++) if( allocation[i] != -1 ) fit+=1;

    return fit;
}

int bestfit(int n, int m, int arrProcess[1000], int arrBlock[1000]){

    int i = 0, j=0, fit=0, best=0;
    int allocation[n];

    for ( i=0; i < n; i++) allocation[i]=-1;

    for(i=0; i < n; i++){
        best = -1;
        for(j=0; j < m; j++){
            if (arrBlock[j] >= arrProcess[i]){
                if (best == -1) best = j;
                else if (arrBlock[best] > arrBlock[j]) best = j;
            }
        }

        if (best != -1){ 
            allocation[i] = best;
            arrBlock[best] -= arrProcess[i];
        }
    }

    for( i=0; i < n; i++) if( allocation[i] != -1 ) fit+=1;

    return fit;
}

int worstfit(int n, int m, int arrProcess[1000], int arrBlock[1000]){
   
    int i = 0, j=0, worst=0, fit=0;
    int allocation[n];

    for ( i=0; i < n; i++) allocation[i]=-1;

    for ( i=0; i < n; i++){
        worst = -1; 
        for (j=0; j < m; j++){
            if (arrBlock[j] >= arrProcess[i]){
                if (worst == -1) worst = j;
                else if (arrBlock[worst] < arrBlock[j]) worst = j;
            }
        }
        if (worst != -1){
            allocation[i] = worst;            
            arrBlock[worst] -= arrProcess[i];
        }
    }

    for( i=0; i < n; i++) if( allocation[i] != -1 ) fit+=1;

    return fit;
}

int main(){

    int pno=0, bno=0, i=0, worst=0, best=0, first=0;

    scanf("%d",&pno);
    int arrProcess[pno], parrAux[pno];

    for(i=0; i<pno; i++){
        scanf("%d",&arrProcess[i]);
        parrAux[i]=arrProcess[i];
    }

    scanf("%d",&bno);
    int arrBlock[bno], barrAux[bno];

    for(i=0; i<bno; i++){
        scanf("%d",&arrBlock[i]);
        barrAux[i]=arrBlock[i];
    }

    worst = worstfit(pno, bno, parrAux, barrAux);

    for(i=0; i<pno; i++) parrAux[i]=arrProcess[i];
    for(i=0; i<bno; i++) barrAux[i]=arrBlock[i];

    best = bestfit(pno, bno, parrAux, barrAux);

    for(i=0; i<pno; i++) parrAux[i]=arrProcess[i];
    for(i=0; i<bno; i++) barrAux[i]=arrBlock[i];

    first = firstfit(pno, bno, parrAux, barrAux);

    if( worst > best && worst > first ){ printf("Worst\n"); }
    else if( (best == worst && best > first) || (best > worst && best > first)){ printf("Best\n"); }
    else if( (first > best && first > worst) || (first == best && first > worst) || (first == best && first == worst) ){ printf("First\n"); }
    
    return 0;

}