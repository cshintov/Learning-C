// counts the number of 1 bits in x
int bitcount(unsigned x) {
    int count;

    for(count = 0; x != 0; x &= x - 1)
            count++;

    return count;
}
