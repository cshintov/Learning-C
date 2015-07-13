// print word length histogram

#include <stdio.h>
#define IN 1
#define OUT 0
#define MAX 11

main(){
    int chr, state, length, maxfreq=0;
    int freq[MAX], frq, maxlength=0;
    
    for(frq = 0; frq < MAX; frq++){
        freq[frq] = 0;
    }

    state = OUT;
    length = 0;
    while((chr = getchar()) != EOF){
        if(chr == ' ' || chr == '\n' || chr == '\t'){
            if(state == IN){
                if(length >= MAX)
                    freq[MAX]++;
                else
                    freq[length]++;
                length = 0;
            }
            state = OUT;
        }
        else if(state == OUT)
            state = IN;
        if(state == IN)
            length++;
        if(length > maxlength)
            maxlength = length;
    }
    if(maxlength >= MAX)
        freq[MAX+1] = -1;
    else
        freq[maxlength+1] = -1;
    maxfreq = max(freq);

    for(frq = maxfreq; frq > 0; frq--){
        printf("\t%3d | ", frq);
        for(length = 1; length <= MAX; length++){
            if(freq[length] >= frq)
                printf("#  ");
            else
                printf("   ");
        }
        printf("\n");
    }
    printf("\t    +");

    for(length = 1; length <= MAX; length++)
        printf("---");
    
    printf("\n\t    ");

    for(length = 1; length < MAX; length++)
        printf("%3d", length);
    
    printf("%3d+",MAX -1);
    printf("\n");
    
}

int max(int array[]) {
    int max = 0, i = 0;
    for(i = 1; array[i] != -1; i++) {
        if(array[i] > max)
            max = array[i];
    }
    return max;
}
