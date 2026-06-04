#include <iostream>    
#include <iomanip>     
#include <string>      
#include <vector>      
#include <time.h>       
#include <stdlib.h>     
#include <limits>      
#include <math.h>       

using namespace std;

// Class representing a single item in the supermarket
class Item {
public:
    int id;               
    string name;          
    string category;      
    double mrp;           
    double retailPrice;   

    Item(int i, string n, string c, double m, double r)
        : id(i), name(n), category(c), mrp(m), retailPrice(r) {}
};

// Class representing the supermarket system
class SuperMarket {
private:
    vector<Item> inventory;            
    vector<pair<int,int> > cart;        // Space added for older compilers

public:
    int nextID = 101; // Auto-increment ID for new items

    // Constructor: Initialize with default items
    SuperMarket() {
        inventory.push_back(Item(nextID++, "Rice", "Groceries", 60, 50));
        inventory.push_back(Item(nextID++, "Oil", "Groceries", 150, 120));
        inventory.push_back(Item(nextID++, "Chips", "Snacks", 30, 25));
        inventory.push_back(Item(nextID++, "Juice", "Beverages", 80, 60));
        inventory.push_back(Item(nextID++, "Soap", "Personal Care", 40, 35));
        inventory.push_back(Item(nextID++, "Shampoo", "Personal Care", 120, 100));
    }

    // Display all items
    void displayItems() {
        if(inventory.empty()) {
            cout << "\nNo items available in the inventory!\n";
            return;
        }

        cout << "\n+----------------------------------------------------------------+";
        cout << "\n¦                       AVAILABLE ITEMS LIST                     ¦";
        cout << "\n+----------------------------------------------------------------+";
        cout << "\n+-----------------------------------------------------------------+";
        cout << "\n¦ ID  ¦ Item Name          ¦ Category   ¦ MRP (?)    ¦ Retail (?) ¦";
        cout << "\n+-----+--------------------+------------+------------+------------¦";

        for(unsigned int i = 0; i < inventory.size(); i++){
            Item &item = inventory[i];
            cout << "\n¦ " << setw(3) << item.id
                 << " ¦ " << setw(19) << left << item.name
                 << " ¦ " << setw(10) << left << item.category
                 << " ¦ " << setw(10) << left << fixed << setprecision(2) << item.mrp
                 << " ¦ " << setw(10) << left << fixed << setprecision(2) << item.retailPrice
                 << "¦";
        }
        cout << "\n+-----------------------------------------------------------------+\n";
    }

    // Admin adds a new item
    void addItem() {
        string name, category;
        double mrp, retail;

        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Category: ";
        getline(cin, category);
        cout << "Enter MRP: ";
        cin >> mrp;
        cout << "Enter Retail Price: ";
        cin >> retail;

        inventory.push_back(Item(nextID++, name, category, mrp, retail));
        cout << "? Item added successfully with ID " << nextID-1 << "!\n";
    }

    // Admin removes an item by ID
    void removeItem() {
        int id;
        cout << "Enter Item ID to remove: ";
        cin >> id;
        bool found = false;
        for(unsigned int i = 0; i < inventory.size(); i++){
            if(inventory[i].id == id){
                cout << "? Item " << inventory[i].name << " removed successfully.\n";
                inventory.erase(inventory.begin() + i);
                found = true;
                break;
            }
        }
        if(!found) cout << "? Item ID not found!\n";
    }

    // User adds item to cart by ID
    void addToCart() {
        if(inventory.empty()) {
            cout << "\nNo items available to add to cart!\n";
            return;
        }

        int itemID, qty;
        displayItems();  
        cout << "\nEnter Item ID to add to cart: ";
        cin >> itemID;
        cout << "Enter quantity: ";
        cin >> qty;

        bool found = false;
        for(unsigned int i = 0; i < inventory.size(); i++){
            if(inventory[i].id == itemID){
                cart.push_back(make_pair(itemID, qty));  
                cout << "? " << inventory[i].name << " x" << qty << " added to cart.\n";
                found = true;
                break;
            }
        }
        if(!found) cout << "? Invalid Item ID!\n";
    }

    // Generate bill
    void generateBill() {
        if(cart.empty()){ 
            cout << "Your cart is empty!\n"; 
            return; 
        }

        double subtotal = 0;  
        cout << "\n+--------------------------------------------+";
        cout << "\n¦                 BILL                       ¦";
        cout << "\n+--------------------------------------------+";
        cout << "\n+-----------------------------------------------------------+";
        cout << "\n¦ ID  ¦ Item Name          ¦ Price    ¦ Qty      ¦ Amount   ¦";
        cout << "\n+-----+--------------------+----------+----------+----------¦";

        for(unsigned int i = 0; i < cart.size(); i++){
            int id = cart[i].first;
            int qty = cart[i].second;
            for(unsigned int j = 0; j < inventory.size(); j++){
                if(inventory[j].id == id){
                    double amt = inventory[j].retailPrice * qty;
                    subtotal += amt;
                    cout <<"\n¦ " << setw(3) << id
                         << " ¦ " << setw(19) << left << inventory[j].name
                         << " ¦ " << setw(8) << inventory[j].retailPrice
                         << " ¦ " << setw(8) << qty
                         << " ¦ " << setw(8) << amt << "¦";
                }
            }
        }

        double gst = subtotal * 0.18;
        double discount = (subtotal > 1200) ? 500 : 0;
        double total = subtotal + gst - discount;

        cout << "\n+-----------------------------------------------------------¦";
        cout << "\n¦ Subtotal:                      " << subtotal << "         ¦";
        cout << "\n¦ GST (18%):                     " << gst << "              ¦";
        if(discount > 0) 
        cout << "\n¦ Discount (?500 for purchase >1200):   " << discount << "  ¦";
        cout << "\n¦ Grand Total:                   " << total << "            ¦";
        cout << "\n+-----------------------------------------------------------+\n";

        processPayment(total);
        cart.clear(); 
    }

    // Payment processing
    void processPayment(double total){
        int choice; 
        string name;
        cout << "\nSelect Payment Method:\n1. Cash   \n2. Online (UPI)   \n3. Card   \nEnter choice: ";
        cin >> choice;

        switch(choice){
            case 1: { 
                double cash; 
                cout << "Enter cash amount:  "; 
                cin >> cash;
                if(cash >= total) 
                    cout << "  Payment successful! Change:  " << cash - total << "\n";
                else 
                    cout << "  Insufficient cash!\n"; 
                break;
            }
            case 2: 
                cout << "Enter UPI ID: "; 
                cin >> name; 
                cout << "  Payment of  " << total << " successful via " << name << "\n"; 
                break;
            case 3: 
                cout << "Enter last 4 digits of card: "; 
                cin >> name; 
                cout << "  Payment of  " << total << " successful via card ****" << name << "\n"; 
                break;
            default:
                cout << "  Invalid choice!\n"; 
                return;
        }

        displayBasket();
    }

    // Basket animation + receipt
    void displayBasket(){
        cout << "\n+---------------------------------------------+";
        cout << "\n¦           Your Basket is Ready!             ¦";
        cout << "\n¦   Thank you for shopping with SUPER SHOP!   ¦";
        cout << "\n¦    Enjoy your day with smiles & savings     ¦";
        cout << "\n+---------------------------------------------+";

        time_t now = time(0);
        char* dt = ctime(&now);

        cout << "\n   RECEIPT GENERATED ON: " << dt;
        cout << "============================================\n";
        cout << "      Visit Again — We Value You!           \n";
        cout << "============================================\n";
    }
};

// Main function
int main(){
    SuperMarket shop; 
    int choice;

    while(true){
        cout << "\n\n+----------------------------------+";
        cout << "\n¦       SUPER SHOP MAIN MENU         ¦";
        cout << "\n+------------------------------------+";
        cout << "\n1. Display All Items";
        cout << "\n2. Add Item to Cart";
        cout << "\n3. Generate Bill (Admin)";
        cout << "\n4. Add New Item (Admin)";
        cout << "\n5. Remove Item (Admin)";
        cout << "\n6. Exit";
        cout << "\nEnter your choice: "; 
        cin >> choice;

        switch(choice){
            case 1: shop.displayItems(); break;
            case 2: shop.addToCart(); break;
            case 3: shop.generateBill(); break;
            case 4: shop.addItem(); break;
            case 5: shop.removeItem(); break;
            case 6: 
                cout << "\nThank you for visiting SUPER SHOP! \n"; 
                return 0;
            default: cout << "  Invalid choice! Try again.\n";
        }
    }
}

