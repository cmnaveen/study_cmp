
x="naveen reddy"

def fun1 (x):
    print x
    return x+x
y=fun1(x)
print y



#Pass by reference vs value

def fun_cal(mylist):
    mylist.append([1,2,3,4]);
    print "values inside the fun_cal :", mylist
    return

mylist = [10,20,30];
fun_cal(mylist);

print mylist

def fun_cal1(mylist1):
    mylist1=[1,2,3,4];
    print "values inside the fun_cal :", mylist1
    return

mylist1 = [10,20,30];
fun_cal1(mylist1);

print mylist1

