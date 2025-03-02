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
#include <stdbool.h>
#include <string.h>

void streamCopy(FILE* in, FILE* out, bool showControlCh, bool printNumberLine);

int main(int argc, char* argv[]){
    bool showControlCh = false;
    bool printNumberLine = false;
    int startIndex = 1;
    
    if(argc == 1) {
        streamCopy(stdin, stdout, false, false);
    } else {
        for (int i = 1; argv[i][0] == '-'; i++)
        {
            switch (argv[i][1])
            {
                case 'T':
                    showControlCh = true;
                    break;
                case 'n':
                    printNumberLine = true;
                    break;
                default:
                    fprintf(stderr, "Fatal error: Invalid parameter %s.", argv[i]);
                    return 0;
            }

            startIndex = i + 1;
        }
        
        for (int i = startIndex; i < argc; i++)
        {
            FILE* file = fopen(argv[i], "r");

            if (file == NULL) {
                fprintf(stderr, "Fatal error: File %s not found.", argv[i]);
                return 0;
            } else {
                streamCopy(file, stdout, showControlCh, printNumberLine);
                fclose(file);
            }
        }
        
    }

    return 0;
}



void streamCopy(FILE* in, FILE* out, bool showControlCh, bool printNumberLine) {
    int ch;
    int lineCount = 1;
    
    fprintf(out, "%d ", lineCount);
    while ((ch=fgetc(in)) != EOF)
    {
        if(ch == '\t' && showControlCh) fputs("TAB", out);
        else fputc(ch, out);

        if(ch == '\n'){
            fprintf(out, "%d ", lineCount++);
        }
    }
}