#computes lcm and hcf of x and y

x = 16
y = 40
print x
print y
print
a = x;
b = y;

while (b != 0):
    t = b;
    b = a % b;
    a = t;

gcd = a;
lcm = (x*y)/gcd;

print gcd
print lcm


