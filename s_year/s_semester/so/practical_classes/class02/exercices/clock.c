#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    int MAX=2000000,i,c;
    clock_t ini,mean=0;
    FILE *fp=tmpfile();
    
    ini = clock();

    while (i++<MAX){
        c = rand();
        write(&c,1,sizeof(int));
    }

    mean=clock()-ini;
    double medio=(mean/(double)CLOCKS_PER_SEC)/MAX;
 
    printf("medio %.10lf Total Time %lf\n",medio,medio*MAX);
}