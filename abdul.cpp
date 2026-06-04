#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class MenuItem {
public:
    int id;
    string name;
    float price;

    MenuItem(int i = 0, string n = "", float p = 0.0) {
        id = i;
        name = n;
        price = p;
    }
};

class Restaurant {
private:
    MenuItem menu[5];
    int menuSize;
    float total;

public:
    Restaurant() {
        // Initialize menu items
        menu[0] = MenuItem(1, "Fried Rice", 120.0);
        menu[1] = MenuItem(2, "Chicken Roll", 80.0);
        menu[2] = MenuItem(3, "Paneer Butter Masala", 150.0);
        menu[3] = MenuItem(4, "Veg Burger", 90.0);
        menu[4] = MenuItem(5, "Cold Coffee", 70.0);
        menuSize = 5;
        total = 0;
    }

    void showMenu() {
        cout << "\n==============================" << endl;
        cout << "          MENU CARD           " << endl;
        cout << "==============================" << endl;
        cout << left << setw(5) << "ID" << setw(20) << "Item" << setw(10) << "Price (?)" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < menuSize; i++) {
            cout << left << setw(5) << menu[i].id << setw(20) << menu[i].name << setw(10) << menu[i].price << endl;
        }
        cout << "----------------------------------------" << endl;
    }

    void takeOrder() {
        int choice, quantity;
        char more;

        do {
            cout << "\nEnter item ID to order: ";
            cin >> choice;
            bool found = false;

            for (int i = 0; i < menuSize; i++) {
                if (menu[i].id == choice) {
                    found = true;
                    cout << "Enter quantity: ";
                    cin >> quantity;
                    total += menu[i].price * quantity;
                    cout << "Added " << quantity << " x " << menu[i].name << " to your order.\n";
                    break;
                }
            }

            if (!found)
                cout << "Invalid item ID. Please try again.\n";

            cout << "Do you want to order more items? (y/n): ";
            cin >> more;
        } while (more == 'y' || more == 'Y');
    }

    void generateBill() {
        float gst = total * 0.05;
        float grandTotal = total + gst;

        cout << "\n==============================" << endl;
        cout << "             BILL             " << endl;
        cout << "==============================" << endl;
        cout << fixed << setprecision(2);
        cout << "Total Amount     : ?" << total << endl;
        cout << "GST (5%)         : ?" << gst << endl;
        cout << "------------------------------" << endl;
        cout << "Grand Total      : ?" << grandTotal << endl;
        cout << "==============================" << endl;

        paymentGateway(grandTotal);
    }

    void paymentGateway(float grandTotal) {
        int choice;
        cout << "\nSelect Payment Method:\n";
        cout << "1. Cash\n2. UPI\n3. Card\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\nYou selected Cash Payment.\nPlease pay ?" << grandTotal << " at the counter.\n";
                break;
            case 2:
                cout << "\nYou selected UPI Payment.\nScan the QR code and pay ?" << grandTotal << ".\n";
                break;
            case 3:
                cout << "\nYou selected Card Payment.\nPlease swipe your card for ?" << grandTotal << ".\n";
                break;
            default:
                cout << "\nInvalid option. Please contact cashier.\n";
        }

        cout << "\nThank you for visiting FOOD PLAZA!\nHave a great day!\n";
    }
};

int main() {
    Restaurant r;
    cout << "==============================" << endl;
    cout << "   WELCOME TO FOOD PLAZA     " << endl;
    cout << "==============================" << endl;

    r.showMenu();
    r.takeOrder();
    r.generateBill();

    return 0;
}
