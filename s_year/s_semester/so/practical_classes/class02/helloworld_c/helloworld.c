#include <stdio.h>

int main(){
    printf("ola\n");
    printf("mundo");
    asm("cli");
    printf("\nfim\n");
    
    setvbuf(stdout, NULL, _IONBF, 0);
 return 0;
}

