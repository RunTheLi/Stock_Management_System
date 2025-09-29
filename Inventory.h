#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include "Product.h"
#include <sqlite3.h>
#include <iomanip> // for setw
#include <limits>  // for numeric_limits

class Inventory {
private:
    std::string dbName;
    sqlite3* db;

public:
    Inventory(const std::string& databaseName);
    ~Inventory();  // Add destructor

    bool connectDatabase();

    void addProduct(Product p);
    void viewProducts();
    void updateProduct(Product p);
    void deleteProduct(int id);

    void searchProductById(int id);
    void searchProductByName(const std::string& name);
    static int productCallback(void* NotUsed, int argc, char** argv, char** azColName);

    bool productExists(const std::string& name); // Add this
};

#endif