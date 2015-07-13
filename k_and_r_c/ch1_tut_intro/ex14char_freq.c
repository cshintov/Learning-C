// histogram of character frequency

#include <stdio.h>

main(){
    int freq[128], i, chr;

    for(i = 0; i < 128; i++)
        freq[i] = 0;

    while((chr = getchar()) != EOF){
        freq[chr]++;
    }

    printf("\t\t\tNumber Of Occurrences\n");
    printf("    ");
    for(i = 1; i <= 25; i++)
        printf("%d ", i);
    printf("\n");

    for(chr = 0; chr < 128; chr++){
        if(freq[chr] > 0){
            if(chr == 10)
                printf(" NL ");
            else if(chr == 11)
                printf("TB ");
            else if(chr == 32)
                printf("SP ");
            else 
                printf("%3c ", chr);
            for(i = 0; i < freq[chr]; i++)
                printf("# ");
            printf("\n");
        }
    }
}
