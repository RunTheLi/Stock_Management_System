#include <iostream>
#include "Inventory.h"
#include "Product.h"

using namespace std;

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

        if (choice == 1) {
            string name, description;
            int quantity;
            double price;

            cin.ignore(); // clear input buffer
            cout << "Enter product name: ";
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter price: ";
            cin >> price;
            cin.ignore();
            cout << "Enter description: ";
            getline(cin, description);

            Product p(0, name, quantity, price, description);
            inv.addProduct(p);

        } else if (choice == 2) {
            inv.viewProducts();

        } else if (choice == 3) {
            int id, quantity;
            double price;
            string name, description;

            cout << "Enter product id to update: ";
            cin >> id;
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, name);
            cout << "Enter new quantity: ";
            cin >> quantity;
            cout << "Enter new price: ";
            cin >> price;
            cin.ignore();
            cout << "Enter new description: ";
            getline(cin, description);

            Product updatedP(id, name, quantity, price, description);
            inv.updateProduct(updatedP);

        } else if (choice == 4) {
            int id;
            cout << "Enter product id to delete: ";
            cin >> id;
            inv.deleteProduct(id);

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
