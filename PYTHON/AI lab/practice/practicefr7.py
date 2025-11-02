print("\n--- P1, Problem 2: Full try-except-else-finally ---")
try:
    a = float(input("Enter first number: "))
    b = float(input("Enter second number: "))
    result = a / b
except ValueError:
    print("Error: Invalid input. Please enter numbers.")
except ZeroDivisionError:
    print("Error: Cannot divide by zero.")
else:
    # This block runs ONLY if the 'try' block was successful
    print(f"Success! Result: {result}")
finally:
    # This block runs NO MATTER WHAT
    print("Division attempt finished.")


print("\n--- P2, Problem 1: Raising an Exception ---")

def set_age(age):
    """Sets an age, raising an error if it's invalid."""
    if not isinstance(age, int):
        # Enforce type
        raise TypeError(f"Age must be an integer, got {type(age)}")
    if age < 0:
        # Enforce business logic
        raise ValueError("Age cannot be negative")
    
    # If code reaches here, the age is valid
    print(f"Age set to {age}")
    # In a real class, you'd have: self.age = age

# --- Example Usage (catching the error) ---
try:
    print("Attempting set_age(25)...")
    set_age(25)  # Valid
    
    print("\nAttempting set_age('ten')...")
    set_age("ten") # Invalid, will raise TypeError
    
    print("This line will not be reached.")
    
except (ValueError, TypeError) as e:
    print(f"Caught expected error: {e}")

print("\n---")

try:
    print("Attempting set_age(-5)...")
    set_age(-5)  # Invalid, will raise ValueError
    print("This line will not be reached.")
except (ValueError, TypeError) as e:
    print(f"Caught expected error: {e}")



print("\n--- P2, Problem 2: Using assert ---")

def calculate_average(grades):
    """Calculates the average of a list of grades."""
    
    # 'assert' checks for internal logical errors.
    # It assumes the list *should* have items by this point.
    assert len(grades) > 0, "Grades list cannot be empty to calculate average"
    
    return sum(grades) / len(grades)

# --- Example Usage ---

# 1. Valid case
try:
    avg = calculate_average([90, 80, 100])
    print(f"Valid average: {avg}")
except AssertionError as e:
    print(f"This should not happen: {e}")

# 2. Invalid case (catching the assertion)
empty_list = []
print("\nAttempting to average an empty list...")
try:
    avg_empty = calculate_average(empty_list)
    print(f"Empty average: {avg_empty}")
except AssertionError as e:
    print(f"Caught expected assertion: {e}")