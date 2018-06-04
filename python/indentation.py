#Blocks of code are denoted by line indentation
#in Python all the continuous lines indented with same number of spaces would form a block.

if True:
    print "true"
    print "in true 2nd line"
else:
    print "false"
    print 'in false 2nd line'


import sys

try:
    # open file stream
    file = open(file_name, "w")
except IOError:
    print " there was an error writing to ",file_name
    sys.exit()

print "Enter'",file_finish,
print "'when finished"

while file_text != file_finish:
    file_text = raw_input("enter text: ")
    if file_text == file_finish:
        #close the file
        file.close
        break
    file.write(file_text)
    file.write("\n")
file.close()
file_name = raw_input("enter filename: ")

if len(file_name) == 0:
    print "next time please enter the somthing"
    sys.exit()
file_text = file.read()
file.close()

print file_text


