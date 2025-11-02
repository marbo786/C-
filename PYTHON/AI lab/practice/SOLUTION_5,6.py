import sys
                                                            # A simple class to hold transaction info
class Transaction:
    def __init__(self, tx_id, tx_type, amt, bal_after, meta=""):
        self.id = tx_id
        self.type = tx_type
        self.amount = amt
        self.balance_after = bal_after
        self.meta = meta

    def display(self):
        res = f"TX {self.id} {self.type} {self.amount} BAL {self.balance_after}"
        if self.meta:
            res += f" {self.meta}"
        return res

class Account:
    def __init__(self, num, name, pin, bal):
        self.account_no = num
        self.holder_name = name
        self.pin = pin
        self.balance = bal
        self.daily_withdrawn = 0
        self.transactions = [] 
        self.tx_counter = 1

    def add_transaction(self, tx_type, amt, meta=""):
                                                                            # create a new transaction record
        t = Transaction(self.tx_counter, tx_type, amt, self.balance, meta)
        self.transactions.append(t)
        self.tx_counter += 1
        
        if len(self.transactions) > 10:
            self.transactions.pop(0)

    def get_mini_statement(self):
                                                            # get last 5 transactions, newest first
        if not self.transactions:
            return ["TX NONE"]
        
                                                            # reverse the list to get newest first
        last_five = self.transactions[-5:]
        return [tx.display() for tx in reversed(last_five)]

class CashCassette:
    def __init__(self):
        self.notes = {5000: 10, 1000: 25, 500: 30, 100: 50}
        self.denominations = sorted(self.notes.keys(), reverse=True)

    def can_dispense(self, amount):
        temp_notes = self.notes.copy()
        temp_amount = amount
        mix = {}

        for d in self.denominations:
                                                            # // is integer division
            num_notes = min(temp_amount // d, temp_notes[d])
            if num_notes > 0:
                mix[d] = num_notes
                temp_amount -= d * num_notes
        
        if temp_amount == 0:
            return mix 
        else:
            return None 

    def dispense(self, amount):
        mix = self.can_dispense(amount)
        if mix:
            for denomination, count in mix.items():
                self.notes[denomination] -= count
            
                                                        # format the mix string like 5000x2 
            mix_parts = []
            for d in self.denominations:
                if d in mix and mix[d] > 0:
                    mix_parts.append(f"{d}x{mix[d]}")
            return " ".join(mix_parts)
        return None


class Bank:
    def __init__(self):
        self.accounts = {
            "1001": Account("1001", "ALI RAZA", "1234", 50000),
            "1002": Account("1002", "AYESHA M RAZA", "2468", 20000),
            "1003": Account("1003", "HAMZA B ZUBAIR", "1357", 150000)
        }
        self.cash_cassette = CashCassette()

    def get_account(self, acc_num):
        return self.accounts.get(acc_num)

    def reset_daily_limits(self):
        for acc in self.accounts.values():
            acc.daily_withdrawn = 0

class ATM:
    def __init__(self):
        self.bank = Bank()
        self.state = "IDLE" 
        self.current_account = None
        self.pin_tries = 0

    def process_command(self, cmd_line):
        parts = cmd_line.strip().split()
        if not parts:
            return 
        
        command = parts[0]
        args = parts[1:]

                                                    #  if/elif block to handle states
        if self.state == "IDLE":
            if command == "CARD" and len(args) == 1:
                self.handle_card_insert(args[0])
            else:
                print("ERROR INVALID_STATE")

        elif self.state == "CARD_INSERTED":
            if command == "PIN" and len(args) == 1:
                self.handle_pin(args[0])
            else:
                print("ERROR INVALID_STATE")

        elif self.state == "AUTHENTICATED":
            if command == "BALANCE":
                self.handle_balance()
            elif command == "WITHDRAW" and len(args) == 1:
                self.handle_withdraw(args[0])
            elif command == "DEPOSIT" and len(args) == 1:
                self.handle_deposit(args[0])
            elif command == "TRANSFER" and len(args) == 2:
                self.handle_transfer(args[0], args[1])
            elif command == "MINI":
                self.handle_mini()
            elif command == "EJECT":
                self.handle_eject()
            else:
                print("ERROR FORMAT")
        else:
            print("ERROR UNKNOWN_STATE")

    def handle_card_insert(self, acc_num):
        acc = self.bank.get_account(acc_num)
        if acc:
            self.current_account = acc
            self.state = "CARD_INSERTED"
            self.pin_tries = 0
            print(f"CARD_OK {acc_num}")
        else:
            print("ERROR UNKNOWN_ACCOUNT")

    def handle_pin(self, pin):
        if self.current_account.pin == pin:
            self.state = "AUTHENTICATED"
            print("PIN_OK")
        else:
            self.pin_tries += 1
            if self.pin_tries >= 3:
                self.handle_eject(error=True) 
            else:
                remaining = 3 - self.pin_tries
                print(f"PIN_INVALID {remaining}")

    def handle_balance(self):
                                                        # add a transaction for the balance inquiry
        self.current_account.add_transaction("BALANCE", 0)
        print(f"BALANCE {self.current_account.balance}")

    def handle_withdraw(self, amount_str):
        try:
            amount = int(amount_str)
        except ValueError:
            print("ERROR AMOUNT_INVALID")
            return

        if amount < 100 or amount > 50000 or amount % 100 != 0:
            print("ERROR AMOUNT_INVALID")
            return
        
        if self.current_account.balance < amount:
            print("ERROR INSUFFICIENT_FUNDS")
            return

        if self.current_account.daily_withdrawn + amount > 100000:
            print("ERROR DAILY_LIMIT_EXCEEDED")
            return

                                                            # check if we can even dispense this amount
        mix_str = self.bank.cash_cassette.dispense(amount)
        if mix_str:
            self.current_account.balance -= amount
            self.current_account.daily_withdrawn += amount
            meta = f"MIX={mix_str.replace(' ', ',')}"
            self.current_account.add_transaction("WITHDRAW", amount, meta)
            print(f"WITHDRAW_OK {amount} {mix_str}")
        else:
            print("ERROR DENOMINATION_UNAVAILABLE")

    def handle_deposit(self, amount_str):
        try:
            amount = int(amount_str)
        except ValueError:
            print("ERROR AMOUNT_INVALID")
            return

        if amount <= 0 or amount % 100 != 0:
            print("ERROR AMOUNT_INVALID")
            return
        
                                                                # update balance and add transaction
        self.current_account.balance += amount
        self.current_account.add_transaction("DEPOSIT", amount)
        print(f"DEPOSIT_OK {amount}")

    def handle_transfer(self, target_acc_num, amount_str):
        if target_acc_num == self.current_account.account_no:
            print("ERROR TARGET_SAME_AS_SOURCE")
            return

        target_acc = self.bank.get_account(target_acc_num)
        if not target_acc:
            print("ERROR TARGET_UNKNOWN")
            return

        try:
            amount = int(amount_str)
        except ValueError:
            print("ERROR AMOUNT_INVALID")
            return

        if amount <= 0:
            print("ERROR AMOUNT_INVALID")
            return

        if self.current_account.balance < amount:
            print("ERROR INSUFFICIENT_FUNDS")
            return
        
                                                    # if all checks passed, perform the transfer
        self.current_account.balance -= amount
        target_acc.balance += amount
        
        self.current_account.add_transaction("TRANSFER_OUT", amount, f"TO={target_acc_num}")
        target_acc.add_transaction("TRANSFER_IN", amount, f"FROM={self.current_account.account_no}")
        
        print(f"TRANSFER_OK {amount} to:{target_acc_num}")

    def handle_mini(self):
        statement_lines = self.current_account.get_mini_statement()
        for line in statement_lines:
            print(line)

    def handle_eject(self, error=False):
        print("CARD_EJECTED")
        self.state = "IDLE"
        self.current_account = None
        self.pin_tries = 0

def main():
    atm = ATM()
    for line in sys.stdin:
        atm.process_command(line)

if __name__ == "__main__":
    main()
