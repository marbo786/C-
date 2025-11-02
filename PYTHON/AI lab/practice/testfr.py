def calculate_grade(marks):
    total = sum(marks)
    average = total / len(marks)

    if average >= 85:
        grade = 'A'
    elif average >= 70:
        grade = 'B'
    elif average >= 50:
        grade = 'C'
    else:
        grade = 'Fail'

    return total, average, grade


class Student:
    def __init__(self, name, marks):
        self.name = name
        self.marks = marks
        self.total, self.average, self.grade = calculate_grade(marks)

    def __str__(self):
        return (f"Name: {self.name}\n"
                f"Marks: {self.marks}\n"
                f"Total: {self.total}\n"
                f"Average: {self.average:.2f}\n"
                f"Grade: {self.grade}\n")



students = []

while True:
    name = input("enter student name: ")

    if name.lower()== "done":
        break

    try:
        marks = []    
        for i in range(1,6):
            mark =float(input(f"Enter marks for subject {i}: "))

            if mark < 0 or mark > 100:
                raise ValueError(" MARKS OUT OF BOUNDS")
            marks.append(mark)

        
        student = Student(name,marks)

        # Store in list of dictionaries
        students.append({
            "name": student.name,
            "marks": student.marks,
            "total": student.total,
            "average": student.average,
            "grade": student.grade
        })

    except ValueError as e:
        print("Invalid input:", e)
        continue

# Display all records
print("\n--- All Student Records ---")
for s in students:
    # Recreate Student object for pretty printing
    print(Student(s['name'], s['marks']))
