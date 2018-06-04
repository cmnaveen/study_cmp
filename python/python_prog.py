#fibonacci series
a,b = 0,1

while b < 10:
    print b
    a,b = b , a+b


print "------------"
b,a=1,0
while b < 10:
    print b,
    a,b = b , a+b

#if else
if a > 0:
    a=0
    print "a changed to zero",a
elif a==0:
    b=1
    print "changed to zero",b
else:
    print "while loop start"
b=1
while b < 10:
    print b,
    a,b = b , a+b

print "\n------------"

words = ['cat','mat','pot']

for w in words:
    print w, len(w)

for w in words[:]:
    if len(w) > 2:
        words.insert(0,w)
print words
print "ranges"

print range(5,10) # print the 5 6 7 8 9 
print range(0,10,3) # print the 0 3,6,9
print range(-10,-100,-30) # print -10 -40 -70

wordss = ['Mary', 'had', 'a', 'little', 'lamb']
for i in range(len(wordss)):
    print i, wordss[i]




