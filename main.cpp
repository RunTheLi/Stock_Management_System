#include <iostream>
#include <limits>       // for numeric_limits
#include <cstdlib>
#include <iomanip>
#include "Inventory.h"
#include "Product.h"

using namespace std;


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // If input buffer already empty, wait for one more newline:
    if (cin.peek() == '\n') { cin.get(); }
}

// Helper: get integer safely
int getIntInput(const string& prompt) {
    int value;
    while (true) {
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

// Helper: get double safely
double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            return value;
        } else {
            cout << "⚠️ Invalid input, please enter a valid number." << endl;
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

    int choice = 0;
    do {
        clearScreen();
        cout << "===== Stock Management System =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. View Products" << endl;
        cout << "3. Update Product" << endl;
        cout << "4. Delete Product" << endl;
        cout << "5. Search Product" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush

        if (choice == 1) {
            string name, description;
            int quantity;
            double price;

            cout << "Enter product name: ";
            getline(cin, name);
            quantity = getIntInput("Enter quantity: ");
            price = getDoubleInput("Enter price: ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter description: ";
            getline(cin, description);

            if (name.empty()) {
                cout << "⚠️ Name cannot be empty." << endl;
            } else if (quantity < 0 || price < 0) {
                cout << "⚠️ Quantity and price cannot be negative." << endl;
            } else {
                Product p(0, name, quantity, price, description);
                inv.addProduct(p);
            }
            waitForEnter();

        } else if (choice == 2) {
            inv.viewProducts();
            waitForEnter();

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

            if (name.empty()) {
                cout << "⚠️ Name cannot be empty." << endl;
            } else if (quantity < 0 || price < 0) {
                cout << "⚠️ Quantity and price cannot be negative." << endl;
            } else {
                Product updatedP(id, name, quantity, price, description);
                inv.updateProduct(updatedP);
            }
            waitForEnter();

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
            waitForEnter();

        } else if (choice == 5) {
            int searchChoice;
            cout << "Search by: 1. ID  2. Name" << endl;
            cin >> searchChoice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (searchChoice == 1) {
                int id = getIntInput("Enter product id: ");
                // print header for consistency
                cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(8) << "Qty" << setw(10) << "Price" << setw(30) << "Description" << endl;
                cout << string(5+20+8+10+30, '-') << endl;
                inv.searchProductById(id);
            } else if (searchChoice == 2) {
                string name;
                cout << "Enter product name (partial allowed): ";
                getline(cin, name);
                cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(8) << "Qty" << setw(10) << "Price" << setw(30) << "Description" << endl;
                cout << string(5+20+8+10+30, '-') << endl;
                inv.searchProductByName(name);
            } else {
                cout << "⚠️ Invalid search option." << endl;
            }
            waitForEnter();

        } else if (choice == 6) {
            cout << "👋 Exiting program. Goodbye!" << endl;
            // destructor of Inventory will close DB if you added it
        } else {
            cout << "⚠️ Invalid choice, try again." << endl;
            waitForEnter();
        }

    } while (choice != 6);

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
