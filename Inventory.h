//Inventory.h
#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include <string>
#include "Product.h"
#include <sqlite3.h>


class Inventory {
    private:
        std::string dbName;
        sqlite3* db;

    public:
        Inventory(const std::string& databaseName);

        bool connectDatabase();

        void addProduct(Product p);
        void viewProducts();
        void updateProduct(Product p);
        void deleteProduct(int id);

        void searchProductById(int id);
        void searchProductByName(std::string& name);
};

#endif