//Inventory.cpp
#include "Inventory.h"
#include <limits>
#include <iomanip>

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
    // Check if product already exists
    if (productExists(p.getName())) {
        std::cout << "⚠️ Product \"" << p.getName() << "\" already exists!" << std::endl;
        std::cout << "Do you want to update its quantity instead? (y/n): ";
        char choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 'y' || choice == 'Y') {
            // Fetch current quantity
            std::string sqlSelect = "SELECT quantity FROM Products WHERE name = '" + p.getName() + "';";
            sqlite3_stmt* stmt;
            int rc = sqlite3_prepare_v2(db, sqlSelect.c_str(), -1, &stmt, nullptr);
            int currentQty = 0;
            if (rc == SQLITE_OK && sqlite3_step(stmt) == SQLITE_ROW) {
                currentQty = sqlite3_column_int(stmt, 0);
            }
            sqlite3_finalize(stmt);

            // Update quantity
            p.setQuantity(p.getQuantity() + currentQty);
            updateProduct(p); // reuse your updateProduct method
        }
        return; // Exit, don’t insert duplicate
    }

    // If product doesn’t exist, insert normally
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

    // Header
    std::cout << "\n📦 Current Inventory:\n";
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(8)  << "Qty"
              << std::setw(10) << "Price"
              << std::setw(30) << "Description"
              << std::endl;
    std::cout << std::string(5+20+8+10+30, '-') << std::endl;

    // Run query
    int rc = sqlite3_exec(db, sql.c_str(), Inventory::productCallback, nullptr, &errMsg);
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

void Inventory::searchProductById(int id) {
    std::string sql = "SELECT * FROM Products WHERE id = " + std::to_string(id) + ";";
    char* errMsg = nullptr;

    std::cout << "\n🔍 Search Result (by ID):\n";
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(8)  << "Qty"
              << std::setw(10) << "Price"
              << std::setw(30) << "Description"
              << std::endl;
    std::cout << std::string(5+20+8+10+30, '-') << std::endl;

    int rc = sqlite3_exec(db, sql.c_str(), Inventory::productCallback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Inventory::searchProductByName(const std::string& name) {
    std::string sql = "SELECT * FROM Products WHERE name LIKE '%" + name + "%';";
    char* errMsg = nullptr;

    std::cout << "\n🔍 Search Results (by Name):\n";
    std::cout << std::left
              << std::setw(5)  << "ID"
              << std::setw(20) << "Name"
              << std::setw(8)  << "Qty"
              << std::setw(10) << "Price"
              << std::setw(30) << "Description"
              << std::endl;
    std::cout << std::string(5+20+8+10+30, '-') << std::endl;

    int rc = sqlite3_exec(db, sql.c_str(), Inventory::productCallback, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "❌ SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}


//Create a Shared Callback for Search Results

int Inventory::productCallback(void* NotUsed, int argc, char** argv, char** azColName) {
    if (argc == 0 || !argv[0]) {
        std::cout << "❌ No product found." << std::endl;
    } else {
        std::cout << std::left
                  << std::setw(5)  << (argv[0] ? argv[0] : "NULL")      // ID
                  << std::setw(20) << (argv[1] ? argv[1] : "NULL")      // Name
                  << std::setw(8)  << (argv[2] ? argv[2] : "NULL")      // Quantity
                  << std::setw(10) << (argv[3] ? argv[3] : "NULL")      // Price
                  << std::setw(30) << (argv[4] ? argv[4] : "NULL")      // Description
                  << std::endl;
    }
    return 0;
}

bool Inventory::productExists(const std::string& name) {
    std::string sql = "SELECT COUNT(*) FROM Products WHERE name = '" + name + "';";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (productExists): " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    rc = sqlite3_step(stmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    return count > 0;
}

Inventory::~Inventory() {
    if (db) sqlite3_close(db);
}