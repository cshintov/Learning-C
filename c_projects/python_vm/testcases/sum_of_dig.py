# computes the sum of digits of num

num = 1204
sum_dig = 0
print num
print 
while num > 0:
    rem = num % 10
    sum_dig = sum_dig + rem
    num = num / 10

print sum_dig
