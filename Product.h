//product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product {
    private:
        int id;
        int quantity;
        std::string name;
        std::string description;
        double price;
    public:
    // Constructor(s)
    // Example: Product(int id, string name, int quantity, double price, string description)
    Product(int _id, string _name, int _quantity, double _price, string _description);
    // Getter methods (optional)
    int getId() const { return id; }
    std::string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    std::string getDescription() const { return description; }
    // e.g., getId(), getName(), getQuantity(), etc.
    
    // Setter methods (optional)
    // e.g., setQuantity(int q), setPrice(double p), etc.
    void setQuantity(int quantity);
    // display() method (optional)
    void display();

    // Prints product info to console
};
#endif