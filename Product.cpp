//Product.cpp
#include "Product.h"
#include <iostream>
#include <string>

using namespace std;

Product::Product(int _id, string _name, int _quantity, double _price, string _description) {
    id = _id;
    name = _name;
    quantity = _quantity;
    price = _price;
    description = _description;
}

void Product::display() {
    cout << "ID: " << id << ", Name: " << name << ", Quantity: " << quantity
         << ", Price: " << price << ", Description: " << description << endl;
}

void Product::setQuantity(int quantity) {
    this->quantity = quantity;
}