// search an element in a sorted array using binary search with one test inside the loop

#include <stdio.h>
#define MAX 1000

int binsearch(int num, int sorted[], int size);

main() {
    int sorted[MAX];
    int position, size, i;
    size = 10;
    for(i = 0; i < size; i++)
        sorted[i] = i + 5;
    position = binsearch(4, sorted, size);
    if(position >= 0)
        printf("Position of 1a in the list is %d\n", position);
    else
        printf("NOT in the list!\n");
}

//binary search with one test inside is the loop
int binsearch(int num, int sorted[], int size) {
    
    int low, mid, high;
    low = 0;
    high = size - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if(num < sorted[mid])
            high = mid - 1;
        else 
            low = mid + 1;
    }
    if(sorted[mid] == num)
        return mid;
    else if(sorted[mid-1] == num)
        return mid - 1;
    else if(sorted[mid+1] == num)
        return mid + 1;
    else
        return -1;
}
