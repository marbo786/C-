student = {
    "name": "Ali",
    "age": 20,
    "department": "AI"
}

for x, y in student.items():
    print(x, ":", y)

#  *args: Becomes a tuple (e.g., (1, 2, 3)) inside the function.

# **kwargs (by convention) collects any number of keyword arguments into a dictionary.
# It's used for passing optional settings or configuration.

def total(*nums):
    return sum(nums)

print(total(2, 4, 6))  # 12


def total(*nums):
    return sum(nums)

print(total(2, 4, 6))  # 12


add = lambda a, b: a + b
print(add(3, 5))  # 8


def add(a, b, c):
    return a + b + c

values = (2, 3, 4)
print(add(*values))   # Unpack tuple into arguments



def make_profile(name, *skills): # skills will be a tuple
    skill_str = ", ".join(skills) # Joins elements of the tuple
    return f"Name: {name}, Skills: {skill_str}"
# print(make_profile("Alice", "Python", "Git"))