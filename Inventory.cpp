//Inventory.cpp
#include "Inventory.h"

using namespace std;

Inventory::Inventory(const std::string& databaseName) {
    dbName = databaseName;
    db = nullptr;
}

bool Inventory::connectDatabase(){
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    } else {
        std::cout << "Connected successfully to " << dbName << std::endl;
        return true;
    }
}

void Inventory::addProduct(Product p) {
    std::string sql = "INSERT INTO Products (name, quantity, price, description) VALUES ('" +
                      p.getName() + "', " +
                      std::to_string(p.getQuantity()) + ", " +
                      std::to_string(p.getPrice()) + ", '" +
                      p.getDescription() + "');";
    
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if(rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "✅ Product added successfully!" << std::endl;
    }
}