class Student:
    def __init__(self, name, age):
        self.name = name      # instance attribute
        self.age = age

    def show(self):           # instance method
        print(f"Name: {self.name}, Age: {self.age}")

# Object
s1 = Student("Ali", 20)
s1.show()



class Student:
    def __init__(self):
        self.name = "Ali"     # public
        self._grade = "A"     # protected
        self.__cgpa = 3.8     # private

s = Student()
print(s.name)       # ✅ works
print(s._grade)     # ⚠️ works but should not be accessed directly
# print(s.__cgpa)   # ❌ Error (private)


class Student:
    def __init__(self, name, cgpa):
        self.__cgpa = cgpa
        self.name = name

    def get_cgpa(self):
        return self.__cgpa

    def set_cgpa(self, value):
        if 0 <= value <= 4:
            self.__cgpa = value
        else:
            print("Invalid CGPA")

s = Student("Ali", 3.5)
print(s.get_cgpa())   # 3.5
s.set_cgpa(3.9)
print(s.get_cgpa())   # 3.9


class Student:
    def __init__(self):
        self.__cgpa = 3.9

s = Student()
print(s._Student__cgpa)  # ✅ Works (name mangled)  ?????



class Student:
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def __str__(self):
        return f"{self.name} is {self.age} years old."

s = Student("Sara", 21)
print(s)                    # String representation (runs when you print the object)



class book:
    default_genre="FICTION"

    def __init__(self,title,author):
        self.title = title
        self.author = author
        

class user:
    def __init__(self,password): 
        self.__password = "";

    def set_password(self, new_password):
        if len(new_password) >= 8:
            self.__password = new_password # Name mangling happens here
        else:
            print("Password must be 8+ characters.")
            
    def check_password(self, guess):
        return self.__password == guess
