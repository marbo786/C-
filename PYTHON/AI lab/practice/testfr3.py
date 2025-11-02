# ----------------------------------------------------------
# 🏦 Bank Account System
# Concepts: Encapsulation, Inheritance, Polymorphism, Operator Overloading,
#           Custom Exceptions, Error Handling, Class Attributes, Special Methods
# ----------------------------------------------------------

# 🔹 Custom Exception
class InsufficientFundsError(Exception):
    def __init__(self, message="❌ Insufficient funds for this withdrawal!"):
        super().__init__(message)


# 🔹 Base Class
class BankAccount:
    bank_name = "Global Trust Bank"  # Class attribute (shared by all)

    def __init__(self, holder_name, balance=0):
        assert holder_name.isalpha(), "Invalid name! Must contain only letters."

        self.holder_name = holder_name
        self.__balance = balance  # Private attribute (Encapsulation)

    # --- Encapsulation with getters/setters ---
    def get_balance(self):
        return self.__balance

    def set_balance(self, amount):
        if amount < 0:
            raise ValueError("Balance cannot be negative.")
        self.__balance = amount

    # --- Deposit Method ---
    def deposit(self, amount):
        try:
            if amount <= 0:
                raise ValueError("Deposit amount must be positive.")
            self.__balance += amount
        except ValueError as e:
            print("Error:", e)
        else:
            print(f"✅ Deposited ${amount:.2f}")
        finally:
            print("Transaction Completed.\n")

    # --- Withdraw Method ---
    def withdraw(self, amount):
        try:
            if amount <= 0:
                raise ValueError("Withdrawal amount must be positive.")
            if amount > self.__balance:
                raise InsufficientFundsError()
            self.__balance -= amount
        except (ValueError, InsufficientFundsError) as e:
            print("Error:", e)
        else:
            print(f"💸 Withdrawn ${amount:.2f}")
        finally:
            print("Transaction Completed.\n")

    # --- Check Balance ---
    def check_balance(self):
        print(f"💰 Current Balance: ${self.__balance:.2f}")

    # --- Polymorphic display method ---
    def display(self):
        print(f"🏦 Account Holder: {self.holder_name}")
        print(f"Bank: {BankAccount.bank_name}")
        print(f"Balance: ${self.__balance:.2f}")

    # --- Operator Overloading: + merges two balances ---
    def __add__(self, other):
        if not isinstance(other, BankAccount):
            raise TypeError("Can only add another BankAccount.")
        total = self.__balance + other.__balance
        return BankAccount(f"{self.holder_name}&{other.holder_name}", total)

    # --- Special Method for printing ---
    def __str__(self):
        return f"{self.holder_name}'s Account — Balance: ${self.__balance:.2f}"


# 🔹 Subclass: SavingsAccount
class SavingsAccount(BankAccount):
    def __init__(self, holder_name, balance=0, interest_rate=0.05):
        super().__init__(holder_name, balance)
        self.interest_rate = interest_rate

    def add_interest(self):
        interest = self.get_balance() * self.interest_rate
        self.deposit(interest)
        print(f"✨ Interest of ${interest:.2f} added.")

    # Polymorphism: overriding display()
    def display(self):
        print(f"💼 Savings Account — {self.holder_name}")
        print(f"Interest Rate: {self.interest_rate * 100}%")
        super().check_balance()


# 🔹 Subclass: CurrentAccount
class CurrentAccount(BankAccount):
    def __init__(self, holder_name, balance=0, overdraft_limit=500):
        super().__init__(holder_name, balance)
        self.overdraft_limit = overdraft_limit

    # Overriding withdraw to allow overdraft
    def withdraw(self, amount):
        try:
            if amount <= 0:
                raise ValueError("Withdrawal amount must be positive.")
            if amount > self.get_balance() + self.overdraft_limit:
                raise InsufficientFundsError("Overdraft limit exceeded!")
            self.set_balance(self.get_balance() - amount)
            print(f"💸 Withdrawn ${amount:.2f}")
        except (ValueError, InsufficientFundsError) as e:
            print("Error:", e)
        finally:
            print("Transaction Completed.\n")

    # Polymorphism: overriding display()
    def display(self):
        print(f"🏛️ Current Account — {self.holder_name}")
        print(f"Overdraft Limit: ${self.overdraft_limit}")
        super().check_balance()


# ----------------------------------------------------------
# 🧠 Demonstration
# ----------------------------------------------------------
if __name__ == "__main__":
    # Create accounts
    acc1 = SavingsAccount("Alice", 1000)
    acc2 = CurrentAccount("Bob", 500)

    # Deposit and withdraw
    acc1.deposit(300)
    acc1.withdraw(200)
    acc1.add_interest()

    acc2.withdraw(800)
    acc2.deposit(400)

    # Display account info (Polymorphism)
    print("\n--- Account Details ---")
    acc1.display()
    print()
    acc2.display()

    # Operator Overloading: Merge balances
    print("\n--- Merged Account ---")
    merged = acc1 + acc2
    merged.display()
