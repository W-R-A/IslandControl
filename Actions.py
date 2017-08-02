print("Actions if statements")
for i in range (0, 44, 1):
    print("//Trigger response to button %d being presed" % i)
    print("if (action == %d)" % i)
    print("{\n    ACTION%d;" % i)
    print("} \n")


print("Defining actions")
for j in range (0, 44, 1):
    print("#define ACTION%d " % j, end = "")
    print('Serial.print("Action %d triggered");'% j)
