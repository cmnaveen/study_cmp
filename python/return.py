def fib_return(n):
    result = []
    a,b = 0,1
    while a<n:
        result.append(a)
        a,b = b ,a+b
    return result 

fib_out = fib_return(100)

print fib_out
