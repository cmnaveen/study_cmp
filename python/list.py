letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
print letters
print "list len"
print len(letters)
print "replace some values"
letters[2:5] = ['C', 'D', 'E']
print letters
# now remove them
print "now remove them"
letters[2:5] = []
print letters
print "clear the list by replacing all the elements with an empty list"
letters[:] = []
print letters

a = ['a','b','c','d']
b = [1,2,3]
x = [a,b,33,66]

print x
print x[0][1]



