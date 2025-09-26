#include <iostream>
#include "Inventory.h"
#include "Product.h"
#include <limits>

using namespace std;

int getIntInput(string& prompt) {
    int value;
    while(true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "⚠️ Invalid input, please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double getDoubleInput(string& prompt) {
    double value;
    while(true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "⚠️ Invalid input, please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    Inventory inv("stock.db");
    if (!inv.connectDatabase()) {
        cerr << "❌ Failed to connect to database." << endl;
        return -1;
    }

    int choice;
    do {
        cout << "\n===== Stock Management Menu =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. View Products" << endl;
        cout << "3. Update Product" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string name, description;
            int quantity;
            double price;

            cout << "Enter product name: ";
            getline(cin, name);
            quantity = getIntInput("Enter quantity: ");
            price = getDoubleInput("Enter price: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush
            cout << "Enter description: ";
            getline(cin, description);

            if (quantity < 0 || price < 0) {
                cout << "⚠️ Quantity and price cannot be negative." << endl;
            } else {
                Product p(0, name, quantity, price, description);
                inv.addProduct(p);
            }

        } else if (choice == 2) {
            inv.viewProducts();

        } else if (choice == 3) {
            int id = getIntInput("Enter product id to update: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            string name, description;
            int quantity;
            double price;

            cout << "Enter new name: ";
            getline(cin, name);
            quantity = getIntInput("Enter new quantity: ");
            price = getDoubleInput("Enter new price: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter new description: ";
            getline(cin, description);

            if (quantity < 0 || price < 0) {
                cout << "⚠️ Quantity and price cannot be negative." << endl;
            } else {
                Product updatedP(id, name, quantity, price, description);
                inv.updateProduct(updatedP);
            }

        } else if (choice == 4) {
            int id = getIntInput("Enter product id to delete: ");
            char confirm;
            cout << "Are you sure you want to delete product " << id << "? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                inv.deleteProduct(id);
            } else {
                cout << "❌ Delete cancelled." << endl;
            }

        } else if (choice == 5) {
            cout << "👋 Exiting program. Goodbye!" << endl;

        } else {
            cout << "⚠️ Invalid choice, try again." << endl;
        }

    } while (choice != 5);

    return 0;
}

//HARD CODE 
//Product p1(0, "Apple", 50, 1.5, "Fresh red apple");
//inv.addProduct(p1);

//Product p2(0, "Banana", 100, 0.9, "Sweet ripe bananas");
//inv.addProduct(p2);

//Product p3(0, "Orange", 70, 1.2, "Juicy oranges");
//inv.addProduct(p3);s

//Product updatedP1(1, "Green Apple", 60, 2.0, "Crispy green apple");
//inv.updateProduct(updatedP1);

//inv.deleteProduct(2);

//inv.viewProducts();
