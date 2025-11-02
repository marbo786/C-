class Book():
    def __init__(self,title,author,price):
        self.title = title
        self.author = author
        self.__price = price

    def get_price(self):
        return self.__price
    
    def set_price(self, newprice):
        if newprice < 0:
            raise ValueError("price cannot be negative.")
        
        self.__price = newprice

    def display_info(self):
        return f"Title: {self.title}\nAuthor: {self.author}\nPrice: ${self.__price:.2f}"


class EBook(Book):
    def __init__(self,title,author,price,file_size):
        super().__init__(title,author,price)

        self.file_size = file_size  


    def display_info(self):
        return super().display_info() 
    

class library:
    def __init__(self):
        self.books = {}

    def addbook(self,book):
        self.books=[book.title] = book  
        print(f"✅ Book '{book.title}' added successfully!")

     # Display all books
    def display_books(self):
        if not self.books:
            print("No books available.")
        else:
            for book in self.books.values():
                print("----------------------")
                print(book.display_info())

    # Search for a book
    def search_book(self, title):
        try:
            book = self.books[title]
            print("\n📖 Book Found:\n")
            print(book.display_info())
        except KeyError:
            print(f"❌ Book titled '{title}' not found.")