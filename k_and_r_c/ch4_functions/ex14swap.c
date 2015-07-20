// macro for swap

#include <stdio.h>
#define swap(t,x,y) {   \
        t _temp;         \
        _temp = x;       \
        x = y;          \
        y = _temp;       \
}

int main() {
    int x = 10, y = 50;
    printf("x: %d, y: %d \n", x, y);
    swap(int, x, y);
    printf("x: %d, y: %d \n", x, y);
    return 0;
}
