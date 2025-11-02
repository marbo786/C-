class Parent:
    def __init__(self):
        print("Parent Constructor")

class Child(Parent):
    def __init__(self):
        super().__init__()              # Used to call a method from the parent class.
        print("Child Constructor")

obj = Child()



class Document:
    """Base class for a generic document."""
    def render(self):
        print("Rendering a generic document...")
        
class PdfDocument(Document):
    """Represents a PDF document."""
    def render(self): # Overriding the parent's method
        print("Rendering PDF... 📄")
        
class HtmlDocument(Document):
    """Represents an HTML web page."""
    def render(self): # Overriding the parent's method
        print("Rendering HTML... <html>")

def render_all(documents):
    """
    Takes a list of Document objects and calls render() on each one.
    This function demonstrates polymorphism.
    """
    print("--- Batch Rendering Documents ---")
    for doc in documents:
        # Python calls the correct .render() method
        # based on the object's actual class.
        doc.render()
    print("---------------------------------")
        
# --- Example Usage ---

# Create a list of different-but-related objects
my_documents = [
    HtmlDocument(),
    PdfDocument(),
    Document(), # The base class
    PdfDocument()
]

# Pass the list to the function
render_all(my_documents)



class Wallet:
    """A class to represent a wallet with a specific amount of money."""
    def __init__(self, amount):
        if amount < 0:
            raise ValueError("Amount cannot be negative")
        self.amount = amount
        
    def __str__(self):
        """Returns the user-friendly string representation (for print())."""
        return f"${self.amount}"
        
    def __add__(self, other):
        """
        Defines the '+' operator for Wallet + Wallet.
        Returns a new Wallet object.
        """
        if isinstance(other, Wallet):
            new_amount = self.amount + other.amount
            return Wallet(new_amount) # Return a new instance
        
        # Return NotImplemented to let Python try other ways (e.g., other.__radd__)
        return NotImplemented 
        
    def __eq__(self, other):
        """
        Defines the '==' operator for Wallet == Wallet.
        Returns True or False.
        """
        if isinstance(other, Wallet):
            # Two wallets are equal if their amounts are equal
            return self.amount == other.amount
        
        # If comparing to a non-Wallet type, they are not equal
        return False

# --- Example Usage ---

w1 = Wallet(100)
w2 = Wallet(50)
w3 = Wallet(100) # Same amount as w1

# 1. Test __str__
print(f"Wallet 1: {w1}")
print(f"Wallet 2: {w2}")
print(f"Wallet 3: {w3}")

# 2. Test __add__
w_total = w1 + w2 # This calls w1.__add__(w2)
print(f"w1 + w2 = {w_total}")
print(f"Type of total: {type(w_total)}")

# 3. Test __eq__
print(f"Is w1 == w2? {w1 == w2}") # Calls w1.__eq__(w2) -> False
print(f"Is w1 == w3? {w1 == w3}") # Calls w1.__eq__(w3) -> True

# 4. Test comparison with other types
print(f"Is w1 == 100? {w1 == 100}") # Calls w1.__eq__(100) -> False