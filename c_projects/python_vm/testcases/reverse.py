# computes the reverse of the number
num = 1234
reverse = 0
print num
print
while num > 0:
    rem = num % 10
    reverse = reverse * 10 + rem
    num = num / 10

print reverse
