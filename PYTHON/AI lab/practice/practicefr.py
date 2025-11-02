#  print(input("ENTER FULL NAME: " ).split()[0] == "john")

#  Advanced QUESTION: A set of permissions is stored in an integer (a "bitmask").
#  Flag A = 1 (binary 001), Flag B = 2 (binary 010), and Flag C = 4 (binary 100).
#  Given current_permissions = 5 (binary 101), write Python expressions using bitwise operators  to: 
#  a. Check if Flag B is set (it shouldn't be). 
#  b. Add Flag B to the current_permissions. 
#  c. Remove Flag A from the current_permissions.

# solution 
# a... current_permissions & B > 0
# b... current_permissions | B   ## 5 | 2 ---> 7  (BITWISE OR)
# c... current_permissions & ~A  ## 5 & ~ -1 ---> 4  (BITWISE NOT)


#   Left shift — x << 1 (multiply by 2)
#   right shift = x >> 1 (Divide by 2)