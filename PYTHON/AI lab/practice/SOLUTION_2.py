REGNO = input("Enter your REG: ")             # taking input
name = input("Enter your NAME: ")       

tokens = name.split()                       # Spliting the name
first = tokens[0]                   
last = tokens[-1]
middle = tuple(tokens[1:-1])

even = REGNO[::2]
odd = REGNO[1::2]

data = [first, middle, last, (even, odd)]       # create a small nested structure

temp = " ".join(middle)
space = " " * len(temp[:1])   
mid = space + temp

handle = "@" + first.lower() + REGNO[-2:]      # adding handle and tag
tag = even[::-1]
length = len(name.replace(" ", ""))

data[1:3] = [middle + ("remix",), last]

print(last, "," ,first, mid , "|", handle, "| tag:", tag, "| reg:", REGNO, "| len:", length)
