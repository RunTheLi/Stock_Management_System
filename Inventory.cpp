//Inventory.cpp
#include "Inventory.h"

using namespace std;

Inventory::Inventory(const std::string& databaseName) {
    dbName = databaseName;
    db = nullptr;
}

bool Inventory::connectDatabase() {
    // open database
    int rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        std::cerr << "❌ Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::cout << "✅ Connected successfully to " << dbName << std::endl;

    // create table if it doesn't exist
    std::string create_sql =
        "CREATE TABLE IF NOT EXISTS Products ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "quantity INTEGER, "
        "price REAL, "
        "description TEXT);";

    char* errMsg = nullptr;
    rc = sqlite3_exec(db, create_sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error (table creation): " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
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

void Inventory::viewProducts() {
    std::string sql = "SELECT id, name, quantity, price, description FROM Products;";
    char* errMsg = nullptr;

    auto callback = [](void* NotUsed, int argc, char** argv, char** azColName) -> int {
        for (int i = 0; i < argc; i++) {
            std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << " | ";
        }
        std::cout << std::endl;
        return 0;
    };

    int rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "✅ Products listed successfully!" << std::endl;
    }
}

void Inventory::updateProduct(Product p) {
    std::string sql = "UPDATE Products SET "
                      "name = '" + p.getName() + "', "
                      "quantity = " + std::to_string(p.getQuantity()) + ", "
                      "price = " + std::to_string(p.getPrice()) + ", "
                      "description = '" + p.getDescription() + "' "
                      "WHERE id = " + std::to_string(p.getId()) + ";";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "✅ Product updated successfully!" << std::endl;
    }
}

void Inventory::deleteProduct(int id) {
    std::string sql = "DELETE FROM Products WHERE id = " + std::to_string(id) + ";";
    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "🗑️ Product with id " << id << " deleted successfully!" << std::endl;
    }
}
