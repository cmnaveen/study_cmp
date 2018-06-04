
#prime number 

for n in range(2,19):
    for x in range(2,n):
        if n % x == 0:
            print n, 'equals',x,'*',n/x
            break
        else:
            print n, 'is a prime number'


# even odd numbers
for num in range(2,19):
    if num % 2 == 0:
        print "even num:",num
        continue
    print "odd num:", num


# pass statements
#while True:
 #   pass 
class MyEmptyClass:
    pass


def initlog(*args):
    pass

def fib(n): # function defination
    a,b = 0,1
    while a < n:
        print a,
        a,b =b ,a+b

fib(20) # function call

