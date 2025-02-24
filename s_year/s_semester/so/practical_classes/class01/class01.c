/*
1)
    a) 
        < - reads input from file 
        > - sends output to file 
        >> - appends to file 
        2> - sends error to file 
    
    b) 

    c)

*/


#include <stdlib.h>
#include <stdio.h>

void streamCopy(FILE* in, FILE* out);

int main(int argc, char* argv[]){
    if(argc == 1) {
        streamCopy(stdin, stdout);
    } else {
        for (int i = 1; i < argc; i++)
        {
            FILE* file = fopen(argv[i], "r");

            if (file == NULL) {
                fprintf(stderr, "%s: Fatal error", argv[i]);
            } else {
                streamCopy(file, stdout);
                fclose(file);
            }
        }
        
    }

    return 0;
}

void streamCopy(FILE* in, FILE* out) {
    int ch;
    while ((ch=fgetc(in)) != EOF)
    {
        fputc(ch, out);
    }
}