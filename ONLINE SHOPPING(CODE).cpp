#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Product {
public:
    int id;
    string name;
    string category;
    double price;
    int stock;

    Product(int id, string name, string category, double price, int stock) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->stock = stock;
    }

    void display() const {
        cout << left << setw(4) << id
             << setw(20) << name
             << setw(12) << category
             << setw(8) << fixed << setprecision(2) << price
             << setw(6) << stock << endl;
    }
};

class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product p, int q) : product(p), quantity(q) {}
};

class Cart {
public:
    vector<CartItem> items;

    void addItem(Product p, int qty) {
        for (auto &item : items) {
            if (item.product.id == p.id) {
                item.quantity += qty;
                return;
            }
        }
        items.push_back(CartItem(p, qty));
    }

    void removeItem(int pid) {
        items.erase(remove_if(items.begin(), items.end(),
                              [&](CartItem &item) { return item.product.id == pid; }),
                    items.end());
    }

    double total() const {
        double sum = 0;
        for (auto &item : items)
            sum += item.product.price * item.quantity;
        return sum;
    }

    void show() const {
        if (items.empty()) {
            cout << "Cart is empty!\n";
            return;
        }
        cout << "\nYour Cart:\n";
        cout << left << setw(4) << "ID" << setw(20) << "Name" << setw(8)
             << "Price" << setw(6) << "Qty" << setw(10) << "Subtotal" << endl;
        for (auto &item : items) {
            cout << setw(4) << item.product.id
                 << setw(20) << item.product.name
                 << setw(8) << item.product.price
                 << setw(6) << item.quantity
                 << setw(10) << item.product.price * item.quantity << endl;
        }
        cout << "--------------------------------------\n";
        cout << "Total: " << total() << "\n";
    }

    void clear() {
        items.clear();
    }
};

class Shop {
public:
    vector<Product> products;
    Cart cart;

    Shop() {
        products.push_back(Product(1, "Wireless Mouse", "Electronics", 499.00, 15));
        products.push_back(Product(2, "Keyboard", "Electronics", 899.00, 8));
        products.push_back(Product(3, "Water Bottle", "Home", 199.00, 30));
        products.push_back(Product(4, "Running Shoes", "Footwear", 1299.00, 5));
        products.push_back(Product(5, "Notebook", "Stationery", 45.00, 100));
    }

    void showProducts() const {
        cout << "\nAvailable Products:\n";
        cout << left << setw(4) << "ID" << setw(20) << "Name"
             << setw(12) << "Category" << setw(8) << "Price"
             << setw(6) << "Stock" << endl;
        for (auto &p : products)
            p.display();
    }

    Product* findProduct(int id) {
        for (auto &p : products)
            if (p.id == id)
                return &p;
        return nullptr;
    }

    void addToCart() {
        int id, qty;
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Quantity: ";
        cin >> qty;
        Product* p = findProduct(id);
        if (p && qty > 0 && qty <= p->stock) {
            cart.addItem(*p, qty);
            cout << qty << " x " << p->name << " added to cart.\n";
        } else {
            cout << "Invalid product or quantity.\n";
        }
    }

    void checkout() {
        if (cart.items.empty()) {
            cout << "Cart is empty!\n";
            return;
        }
        double total = cart.total();
        cout << "\n--- Checkout Summary ---\n";
        cart.show();
        cout << "Thank you for shopping! Your total is: " << total << " INR\n";

        // Reduce stock
        for (auto &item : cart.items) {
            for (auto &p : products) {
                if (p.id == item.product.id)
                    p.stock -= item.quantity;
            }
        }
        cart.clear();
    }
};

int main() {
    Shop shop;
    int choice;

    while (true) {
        cout << "\n==== ONLINE SHOPPING SYSTEM ====\n";
        cout << "1. View Products\n";
        cout << "2. Add to Cart\n";
        cout << "3. View Cart\n";
        cout << "4. Remove Item from Cart\n";
        cout << "5. Checkout\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                shop.showProducts();
                break;
            case 2:
                shop.addToCart();
                break;
            case 3:
                shop.cart.show();
                break;
            case 4: {
                int pid;
                cout << "Enter Product ID to remove: ";
                cin >> pid;
                shop.cart.removeItem(pid);
                break;
            }
            case 5:
                shop.checkout();
                break;
            case 0:
                cout << "Thank you for visiting!\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }
} 
