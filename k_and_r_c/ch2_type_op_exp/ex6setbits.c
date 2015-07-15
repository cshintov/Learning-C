// sets n bits of x  starting at position p with rightmost n bits of y

unsigned setbits(unsigned x, int p , int n, int y) {
    int a, b, c, k;
    a = b = c = 0;
    k = p + 1 - n; // number of bits to be shifted left
    a =  ~ (~0 << n); //  0000000111 for n = 3
    b = y & a; // last n=3 bits of y  00000000yyy
    b = b << k; // 0000000000yyy00 when k = 2
    c = a << k; // 000000000011100 when k = 2
    c = ~ c;  //   111111111100011 
    x = c & x; //  xxxxxxxxxx000xx ; x when n bits from p set to 0
    // xxxxx000xx = X
    // 00000yyy00 = B
    // xxxxxyyyxx = X | B
    return x = x | b;
}
