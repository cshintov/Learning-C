// search an element in a sorted array using binary search

#include <stdio.h>
#define MAX 1000

int binsearch(int num, int sorted[], int size);

main() {
    int sorted[MAX];
    int position, size, i;
    size = 10;
    for(i = 0; i < size; i++)
        sorted[i] = i + 5;
    position = binsearch(25, sorted, size);
    if(position >= 0)
        printf("Position of 25 in the list is %d\n", position);
    else
        printf("NOT in the list!\n");
}

int binsearch(int num, int sorted[], int size) {
    
    int low, mid, high;
    low = 0;
    high = size - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        printf("mid %d sorted[mid] %d\n", mid , sorted[mid]);        
        if(num < sorted[mid])
            high = mid - 1;
        else if (num > sorted[mid])
            low = mid + 1;
        else
            return mid;
        printf("%d low %d high\n", low, high);            
    }
    return -1;
}
