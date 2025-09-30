#include <iostream>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include "Inventory.h"
#include "Product.h"

using namespace std;

// Optional: Colors for terminal (works on most Linux/WSL terminals)
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"

// Clear screen function
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wait for user to press enter
void waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.peek() == '\n') cin.get();
}

// Safe integer input
int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << RED << "⚠️ Invalid input, enter a number." << RESET << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Safe double input
double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << RED << "⚠️ Invalid input, enter a valid number." << RESET << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Display menu
void showMenu() {
    cout << CYAN;
    cout << "\n========================================\n";
    cout << "      📦 Stock Management System\n";
    cout << "========================================\n" << RESET;
    cout << "1️⃣  Add Product\n";
    cout << "2️⃣  View Products\n";
    cout << "3️⃣  Update Product\n";
    cout << "4️⃣  Delete Product\n";
    cout << "5️⃣  Search Product\n";
    cout << "6️⃣  Exit\n";
    cout << "----------------------------------------\n";
    cout << "👉 Enter your choice: ";
}

int main() {
    Inventory inv("stock.db"); // make sure the filename matches your DB

    if (!inv.connectDatabase()) {
        cerr << RED << "❌ Failed to connect to database." << RESET << endl;
        return -1;
    }

    int choice;
    do {
        clearScreen();
        showMenu();
        choice = getIntInput("");

        if (choice == 1) {
            cin.ignore();
            string name, description;
            int quantity;
            double price;

            cout << "Enter product name: ";
            getline(cin, name);
            quantity = getIntInput("Enter quantity: ");
            price = getDoubleInput("Enter price: ");
            cin.ignore();
            cout << "Enter description: ";
            getline(cin, description);

            Product p(0, name, quantity, price, description);
            inv.addProduct(p);
            waitForEnter();

        } else if (choice == 2) {
            inv.viewProducts();
            waitForEnter();

        } else if (choice == 3) {
            int id = getIntInput("Enter product ID to update: ");
            inv.updateProductInteractive(id);   // 👈 new interactive method
            waitForEnter();
        } else if (choice == 4) {
            int id = getIntInput("Enter product ID to delete: ");
            inv.deleteProduct(id);
            waitForEnter();

        } else if (choice == 5) {
            int searchChoice;
            cout << "\n🔍 Search Options\n";
            cout << "1️⃣  Search by ID\n";
            cout << "2️⃣  Search by Name\n";
            cout << "👉 Enter your choice: ";
            searchChoice = getIntInput("");

            cin.ignore(); // clear buffer
            if (searchChoice == 1) {
                int id = getIntInput("Enter product ID: ");
                inv.searchProductById(id);
            } else if (searchChoice == 2) {
                string name;
                cout << "Enter product name (partial allowed): ";
                getline(cin, name);
                inv.searchProductByName(name);
            } else {
                cout << RED << "⚠️ Invalid search option." << RESET << endl;
            }
            waitForEnter();

        } else if (choice == 6) {
            cout << GREEN << "👋 Exiting program. Goodbye!" << RESET << endl;

        } else {
            cout << RED << "⚠️ Invalid choice, try again." << RESET << endl;
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
