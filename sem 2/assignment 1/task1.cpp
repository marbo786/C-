#include<iostream>
#include<string>

#define CALCULATE_STOCK_VALUE
#define ENABLE_DISCOUNTS
#define GENERATE_SALES_REPORT

using namespace std;

 //defining a structure for product

struct product
{

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

// function for adding a product

void addproduct(){

    if (productCount >= MAX_PRODUCTS) {
        cout << "Product list is full!"<<endl;
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
    cout << "Product added successfully"<<endl;
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


#ifdef CALCULATE_STOCK_VALUE
void calculateStockValue() {
    float totalValue = 0;
    for (int i = 0; i < productCount; i++) {
        totalValue += products[i].price * products[i].stockq;
    }
    cout << "Total Stock Value: $" << totalValue << "\n";
}
#endif

#ifdef ENABLE_DISCOUNTS
void applyDiscounts() {
    cout << "Applying Discount!!!";
    for (int i = 0; i < productCount; i++) {
        products[i].price -= (products[i].price * (products[i].discount / 100));
    }
    cout << "Discounts Applied.\n";
}
#endif


// Adds up all revenue values to display total earnings.


#ifdef GENERATE_SALES_REPORT
void generateSalesReport() {
    float totalRevenue = 0;
    for (int i = 0; i < productCount; i++) {
        totalRevenue += products[i].revenue;
    }
    cout << "Total Revenue Generated: $" << totalRevenue << "\n";
}
#endif






int main(){

    int choice, id;
    while (true) {
        cout << "\nProduct Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Display Product\n";
        #ifdef CALCULATE_STOCK_VALUE
        cout << "3. Calculate Total Stock Value\n";
        #endif
        #ifdef ENABLE_DISCOUNTS
        cout << "4. Apply Discounts\n";
        #endif
        #ifdef GENERATE_SALES_REPORT
        cout << "5. Generate Sales Report\n";
        #endif
        cout << "6. Exit\n";
        cout << "Enter choice: ";
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
            #ifdef CALCULATE_STOCK_VALUE
            case 3:
                calculateStockValue();
                break;
            #endif
            #ifdef ENABLE_DISCOUNTS
            case 4:
                applyDiscounts();
                break;
            #endif
            #ifdef GENERATE_SALES_REPORT
            case 5:
                generateSalesReport();
                break;
            #endif
            case 6:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }
    return 0;
}
