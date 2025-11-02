#include <iostream>
#include <string>

#define CALCULATE_STOCK_VALUE
#define ENABLE_DISCOUNTS
#define GENERATE_SALES_REPORT
#define SHOPPING_CART

using namespace std;


 //defining a structure for product

struct product {
    int productid;
    string name;
    string category;
    float price;
    int stockq;
    float discount;
    float revenue;
};


//defining the maximum number of products

const int MAX_PRODUCTS = 100;
product products[MAX_PRODUCTS];

// productCount tracks the number of added products.

int productCount = 0;

// Cart system
struct CartItem {
    int productid;
    int quantity;
};
const int MAX_CART_ITEMS = 50;
CartItem cart[MAX_CART_ITEMS];
int cartItemCount = 0;


// function for adding a product

void addproduct() {
    if (productCount >= MAX_PRODUCTS) {
        cout << "Product list is full!" << endl;
        return;
    }

    product& p = products[productCount];
    cout << "Enter Product ID: ";
    cin >> p.productid;
    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "Enter Category: ";
    getline(cin, p.category);
    cout << "Enter Price: ";
    cin >> p.price;
    cout << "Enter Stock Quantity: ";
    cin >> p.stockq;
    cout << "Enter Discount Percentage: ";
    cin >> p.discount;
    p.revenue = 0;

    productCount++;
    cout << "Product added successfully" << endl;
}


// Function to display product details


void displayProduct(int id) {
    for (int i = 0; i < productCount; i++) {
        if (products[i].productid == id) {
            cout << "\nProduct Details:\n";
            cout << "ID: " << products[i].productid << "\n";
            cout << "Name: " << products[i].name << "\n";
            cout << "Category: " << products[i].category << "\n";
            cout << "Price: $" << products[i].price << "\n";
            cout << "Stock Quantity: " << products[i].stockq << "\n";
            cout << "Discount: " << products[i].discount << "%\n";
            cout << "Revenue Generated: $" << products[i].revenue << "\n";
            return;
        }
    }
    cout << "Product not found.\n";
}


// Multiplies each product's price by its stock quantity to get the total stock value.

void calculateStockValue() {
    float totalValue = 0;
    for (int i = 0; i < productCount; i++) {
        totalValue += products[i].price * products[i].stockq;
    }
    cout << "Total Stock Value: $" << totalValue << "\n";
}

void applyDiscounts() {
    for (int i = 0; i < productCount; i++) {
        products[i].price -= (products[i].price * (products[i].discount / 100));
    }
    cout << "Discounts Applied.\n";
}


// Adds up all revenue values to display total earnings.

void generateSalesReport() {
    float totalRevenue = 0;
    for (int i = 0; i < productCount; i++) {
        totalRevenue += products[i].revenue;
    }
    cout << "Total Revenue Generated: $" << totalRevenue << "\n";
}


// bonus part


void addToCart() {
    int id, quantity;
    cout << "Enter Product ID to add to cart: ";
    cin >> id;
    cout << "Enter Quantity: ";
    cin >> quantity;

    for (int i = 0; i < productCount; i++) {
        if (products[i].productid == id) {
            if (products[i].stockq >= quantity) {
                cart[cartItemCount].productid = id;
                cart[cartItemCount].quantity = quantity;
                cartItemCount++;
                cout << "Product added to cart.\n";
            } else {
                cout << "Not enough stock available.\n";
            }
            return;
        }
    }
    cout << "Product not found.\n";
}

void checkout() {
    float total = 0;
    cout << "\nChecking out...\n";
    for (int i = 0; i < cartItemCount; i++) {
        for (int j = 0; j < productCount; j++) {
            if (products[j].productid == cart[i].productid) {
                float discountedPrice = products[j].price * (1 - (products[j].discount / 100));
                float cost = discountedPrice * cart[i].quantity;
                total += cost;
                products[j].stockq -= cart[i].quantity;
                products[j].revenue += cost;
                cout << "Bought " << cart[i].quantity << " x " << products[j].name << " for $" << cost << "\n";
            }
        }
    }
    cout << "Total Cost: $" << total << "\n";
    cartItemCount = 0;
}

void displayMenu() {
    cout << "\n Product Management System \n";
    cout << "1. Add Product\n";
    cout << "2. Display Product\n";
    cout << "3. Calculate Total Stock Value\n";
    cout << "4. Apply Discounts\n";
    cout << "5. Generate Sales Report\n";
    cout << "6. Add to Cart\n";
    cout << "7. Checkout\n";
    cout << "8. Exit\n";
    
    cout << "Enter choice: ";
}

int main() {
    int choice, id;
    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addproduct();
                break;
            case 2:
                cout << "Enter Product ID: ";
                cin >> id;
                displayProduct(id);
                break;
            case 3:
                calculateStockValue();
                break;
            case 4:
                applyDiscounts();
                break;
            case 5:
                generateSalesReport();
                break;
            case 6:
                addToCart();
                break;
            case 7:
                checkout();
                break;
            case 8:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
