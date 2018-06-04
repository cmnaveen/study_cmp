#Multiple Statements on a Single Line (;) semicolon

import sys; x = 'foo'; sys.stdout.write(x+'\n')

#Assigning Values to Variables

x= 100
y= 1000
z= 10000
name = 'naveen'
name2 = "naveen reddy"


print x ,y,z,name ,name2

#Multiple Assignment

a=b=c=1

print a,b,c

a,b,c = 1,2,"naveen"

print a,b,c

#Standard Data Types
#Numbers , String , List ,Tuple,Dictionary

#python Numbers
#Number data types store numeric values. 
#Number objects are created when you assign a value to them. 
var1 =1
var2 = 10

del var1

#print var1,var2 #NameError: name 'var1' is not defined

#python string 

str = 'naveen reddy cm'

print str          # Prints complete string
print str[0]       # Prints first character of the string
print str[2:5]     # Prints characters starting from 3rd to 5th
print str[2:]      # Prints string starting from 3rd character
print str * 2      # Prints string two times
print str + "TEST" # Prints concatenated string


#python List
#A list contains items separated by commas and enclosed within square brackets ([])

list =  [ 'naveen',2655,"reddy",2455,2.032]

print list 
print list *2
print list[2]
print list [2:4]
#print list + 'naveen reddy' #TypeError: can only concatenate list (not "str") to list

print list + [0001,1000]
#python Tuples
#"The main differences between lists and tuples are: Lists are enclosed in brackets ( [ ] ) and their elements and size can be changed, while tuples are enclosed in parentheses ( ( ) ) and cannot be updated. Tuples can be thought of as read-only lists."

tuple  = ( 'naveen' ,2655,2.22,'reddy',2)
addtuple = (213,'cmnaveenreddy')

print tuple
print tuple[0]
#print tuple(0) #object is not called
print tuple[2:]
#print tuple + ('cmnaveenreddy') //TypeError: can only concatenate tuple (not "str") to tuple

print tuple + addtuple

# tuple and list

tuple = ('naveen',2655,"reddy")
list = ["naveen",2655,'reddy']
#tuple[2] = 1000 #Invalid syntax with tuple
#list[2] = 1000 #valid syntax with list

#python Dictionary

dict = {}
dict['one'] = "this is one "
dict[2655] = "this is cm naveen reddy"

displaydict = {'name':'naveen','code':2655,"dept":'engineer'}

print dict['one']
print dict[2655]
print displaydict
print displaydict.keys()
print displaydict.values()
print displaydict['code']

#Python Membership Operators

#in, not in


#Identity operators
# is ,is not

#if if--else

nav = 100
if (nav == 100) :print "value of expression is 100"
print "good bye!"

print abs(nav)
va1=12
va2=123
print cmp(va1,va2) # -1 if x < y, 0 if x == y, or 1 if x > y

var1 = 'Hello World!'
var2 = "Python Programming"

print "var1[0]: ", var1[0]
print "var2[1:5]: ", var2[1:5]

#String formate Operator
print "My name is %s and weight is %d kg!" % ('Zara', 21)

#Triple Quotes

para_str = """this is a long string that is made up of
several lines and non-printable characters such as
TAB ( \t ) and they will show up that way when displayed.
NEWLINEs within the string, whether explicitly given like
this within the brackets [ \n ], or just a NEWLINE within
the variable assignment will also show up.
"""
print para_str
print "\n"
print "\n\n\n"








#---------------------------

xx=12
yy=5
print xx//yy #output is 2
print xx/yy #output is 2



