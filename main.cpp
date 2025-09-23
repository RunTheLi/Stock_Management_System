#include <iostream>
#include "Inventory.h"
#include "Product.h"

using namespace std;

int main() {
    Inventory inv("stock.db"); // pass the database filename
    if (inv.connectDatabase()) {
        std::cout << "Database is ready for operations." << std::endl;
    } else {
        std::cerr << "Failed to connect to database." << std::endl;
    }
    return 0;
}