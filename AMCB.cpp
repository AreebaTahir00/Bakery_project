#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <iomanip>
#include <string>
#include<windows.h>
#include<conio.h>
#include <cstdlib>
#include <limits>
using namespace std;

void setTextColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class setup
{
 public:
    setup() {
        system("CLS");
           cout << "\n\n\n\n\n\n\n\n\t\t";
           setTextColor(14);
           
           string welcome="______AREEMAL CAFE AND BAKERY_______";
           for (size_t i = 0; i < welcome.length(); ++i) {
           cout << welcome[i];
           Sleep(150); 
           }
           Sleep(1500); 
           system("CLS");
           setTextColor(7);
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\tLoading... Please Wait!\n\n";
    
    char a = 177;  // Light-shade block (for empty bar)
    char b = 219;  // Dark-shade block (for progress bar)
    
    cout << "\t\t\t\t\t[";
    for (int i = 0; i < 30; i++) {
        cout << a;  // Initially filling the bar with empty blocks
    }
    cout << "]\r";  // Carriage return to overwrite the line
    
    cout << "\t\t\t\t\t[";
    for (int i = 0; i < 30; i++) {
        cout << b;  // Gradually replacing empty blocks with filled blocks
        Sleep(100); 
    }
    cout << "]\n";

    system("CLS");
    animatedWelcome();     
}
void animatedWelcome() {
    setTextColor(10);
    string welcomeText = "  .##...##..######..##.......####....####...##......##...#######..\n"
                         "  .##...##..##......##......##..    ##..##..##.#..#.##...##.......\n"
                         "  .##.#.##..####....##......##......##..##..##..##..##...#######..\n"
                         "  .#######..##......##......##......##..##..##......##...##.......\n"
                         "  ..##.##...######..######...####....####...##......##...#######..\n";

    for (char c : welcomeText) {
    
        cout << c;
        Sleep(30);
    }


    setTextColor(15);
    cout << "\n\n\n";
    cout << "\t\t\tWelcome to ";
    setTextColor(14); // Gold color
    cout << "Areemal Cafe and Bakery!";
    setTextColor(15);
    cout << "\n\t\t\tWhere every bite is a delight!  :)\n";

    Sleep(1000);   
    setTextColor(7); 
    _getch();// Wait for user input to proceed
    system("CLS");
}
};

const string OWNER_PASSWORD = "CTRLg";
const string STAFF_PASSWORD = "AMCB";

void tryagain() {
    system("CLS");
    setTextColor(12);
    cout << "  (\\__/)" << endl;
    cout << "  (o.o )" << endl;
    cout << "  (>No<)" << endl;
    cout << "  (____)" << endl;
    cout << " Try Again" << endl;

    setTextColor(7);
    _getch();
    system("CLS");
}

struct Item {
    string name;
    double price;
    int quantity;

    Item(string name, double price, int quantity) : name(name), price(price), quantity(quantity) {}
};

struct CustomerOrder {
    string customerName;
    string phone;
    string address;
    vector<Item> orderItem;

    CustomerOrder(string cName, string ph, string addr)
        : customerName(cName), phone(ph), address(addr) {}

    void addItem(const string& name, int quantity, double price) {
        orderItem.push_back({name, price, quantity});
    }    
};


vector<Item> inventory;
queue<CustomerOrder> orders;
 

class Bakery {
private:
    
    string filename = "bakery_data.txt";
    string filename1= "orders.txt";

public:
    Bakery() {
        loadFromFile();
        loadOrdersFromFile(orders);
    }
    
    void addItem(string name, double price, int quantity) {
        inventory.push_back({name, price, quantity});
        saveToFile();
    }

    void deleteItem(string name) {
    queue<Item> tempQueue;
    bool itemFoundInOrders = false;

    bool itemFoundInInventory = false;
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == name) {
            inventory.erase(it);  // Remove item from inventory
            itemFoundInInventory = true;
            setTextColor(2);
            system("CLS");
            cout << "Item deleted from inventory.\n";
            Sleep(2000);
            system("CLS");
            break;
        }
    }

    if (!itemFoundInInventory) {
        cout << "Item not found in inventory!\n";
    }
    saveToFile();
}


void modifyItem(string name, double price, int quantity) {
    bool itemFoundInOrders = false;
    bool itemFoundInInventory = false;
    queue<Item> tempQueue;

    for (auto &item : inventory) {
        if (item.name == name) {
            item.price = price; 
            item.quantity = quantity; 
            itemFoundInInventory = true;
            break;
        }
    }
    system("CLS");
    if (itemFoundInInventory) {
        setTextColor(2);
        cout << "Item modified in inventory.\n";
        setTextColor(7);
    } else {
        setTextColor(4);
        cout << "Item not found in inventory!\n";
        setTextColor(7);
    }

    saveToFile();
}


    void displayItems() {
    cout << "------------------------------------------------------------\n";
    cout << "| " << left << setw(15) << "Name" 
         << "| " << setw(10) << "Price" 
         << "| " << setw(10) << "Quantity" 
         << "|\n";
    cout << "------------------------------------------------------------\n"; 
    for (const auto &item : inventory) {
        cout << "| " << left << setw(15) << item.name
             << "| " << setw(10) << item.price
             << "| " << setw(10) << item.quantity
             << "|\n";
    }

    cout << "------------------------------------------------------------\n";
   }

void processOrder() {
    if (orders.empty()) {
        setTextColor(4);
        system("CLS");
        cout << "No pending orders!\n";
        setTextColor(7);
        Sleep(2000);
        return;
    }
    CustomerOrder order = orders.front();
    orders.pop(); 

    setTextColor(11);
    cout << "\nProcessing order for: " << order.customerName << endl;
    cout << order.phone << endl;
    cout << order.address << endl;

    cout << "Items Ordered:\n";
    setTextColor(7);
    double totalPrice = 0.0;
    for (const auto& item : order.orderItem) {
        cout << item.name << " | Quantity: " << item.quantity << " | Price: $" << fixed << setprecision(2) << item.price << endl;
        totalPrice += item.price * item.quantity;
    }

    cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
    setTextColor(11);
    cout << "-------------------------------------\n";
    setTextColor(7);
    Sleep(4000);

    
    saveRemainingOrdersToFile();
}
void saveRemainingOrdersToFile() {
    ofstream file("orders.txt");
    
    if (!file) {
        cerr << "Error opening file to save orders!" << endl;
        return;
    }

    queue<CustomerOrder> tempQueue = orders; // Preserve original queue

    while (!tempQueue.empty()) {
        CustomerOrder order = tempQueue.front();
        tempQueue.pop();

        for (const auto& item : order.orderItem) {
            file << order.customerName << "|"
                 << order.phone << "|"
                 << order.address << "|"
                 << item.name << "|"
                 << fixed << setprecision(2) << item.price << "|"
                 << item.quantity << "\n";
        }
    }

    file.close();
}

void loadOrdersFromFile(queue<CustomerOrder>& orderQueue) {
    ifstream file("orders.txt");
    if (!file) {
        setTextColor(4);
        system("CLS");
        cerr << "Error: Could not open file!" << endl;
        setTextColor(7);
        Sleep(3000);
        system("CLS");
        return;
    }

    vector<CustomerOrder> orders; // Stores all orders

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string customerName, phone, address, itemName;
        int quantity;
        double price;

        getline(ss, customerName, '|');
        getline(ss, phone, '|');
        getline(ss, address, '|');
        getline(ss, itemName, '|');
        ss >> price;
        ss.ignore(); // Ignore '|'
        ss >> quantity;

        // Check if customer already exists
        bool found = false;
        for (auto& order : orders) {
            if (order.customerName == customerName && order.phone == phone && order.address == address) {
                order.addItem(itemName, quantity, price);
                found = true;
                break;
            }
        }

        if (!found) {
            CustomerOrder newOrder(customerName, phone, address);
            newOrder.addItem(itemName, quantity, price);
            orders.push_back(newOrder);
        }
    }

    file.close();

    for (const auto& order : orders) {
        orderQueue.push(order);
    }

    // Debugging: Print all loaded orders
    for (const auto& order : orders) {
        setTextColor(11);
        cout << "\nOrder for: " << order.customerName << endl;
        cout << "Phone: " << order.phone << endl;
        cout << "Address: " << order.address << endl;
        cout << "Items Ordered:\n";
        setTextColor(7);
        double totalPrice = 0.0;
        for (const auto& item : order.orderItem) {
            cout << item.name << " | Quantity: " << item.quantity 
                 << " | Price: $" << fixed << setprecision(2) << item.price << endl;
            totalPrice += item.price * item.quantity;
        }
        cout << "Total Price: $" << fixed << setprecision(2) << totalPrice << endl;
        setTextColor(11);
        cout << "-------------------------------------\n";
        setTextColor(7);
    }
    Sleep(2000);
    system("CLS");
}

void viewAllOrders(queue<CustomerOrder> orderQueue) {
    if (orderQueue.empty()) {
        cout << "No orders available.\n";
        return;
    }

    while (!orderQueue.empty()) {
        CustomerOrder order = orderQueue.front();
        orderQueue.pop(); 

        cout << "\nCustomer: " << order.customerName 
             << " | Phone: " << order.phone 
             << " | Address: " << order.address << endl;
        cout << "Items Ordered:\n";

        double totalPrice = 0.0;
        for (const auto& item : order.orderItem) {
            cout << item.name << " | Quantity: " << item.quantity 
                 << " | Price: $" << fixed << setprecision(2) << item.price << endl;
            totalPrice += item.quantity * item.price;
        }

        cout << "Total Bill: $" << fixed << setprecision(2) << totalPrice << endl;
        cout << "-----------------------------------\n";
    }
}

void saveToFile() {
    ofstream file(filename);

    if (!file) {
        setTextColor(4);
        cerr << "Error: Could not open file for writing!" << endl;
        setTextColor(7);
        Sleep(3000);
        system("CLS");
        return;
    }

    file << "Name|Price|Quantity\n"; 

    for (const auto &item : inventory) {
        file << item.name << "|" 
             << fixed << setprecision(2) << item.price << "|" 
             << item.quantity << "\n";
    }

    file.close();
    setTextColor(2);
    cout << "Inventory successfully saved to file!\n"; 
    setTextColor(7);
    Sleep(2000);
    system("CLS");  
}


   void loadFromFile() {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file!" << endl;
        return;
    }

    string line;
    cout << "Reading from file...\n";

    while (getline(file, line)) {
        cout << "Raw line read: " << line << endl; // Debugging print

        if (line.empty() || line.find("-") != string::npos) {
            cout << "Skipping line: " << line << endl; // Debug message
            continue;
        }

        string name;
        double price;
        int quantity;

        stringstream ss(line);
        getline(ss >> ws, name, '|');

        name.erase(name.find_last_not_of(" \t\n\r") + 1);

        cout << "Extracted name: " << name << endl;

        if (!(ss >> price)) {
            cerr << "Error parsing price in line: " << line << endl;
            continue;
        }

        ss.ignore(); // Ignore the '|'

        if (!(ss >> quantity)) {
            cerr << "Error parsing quantity in line: " << line << endl;
            continue;
        }

        inventory.push_back({name, price, quantity});
        setTextColor(2);
        cout << "Added item: " << name << " | " << price << " | " << quantity << endl;
        setTextColor(7);
    }

    file.close();
    cout << "Final inventory size: " << inventory.size() << endl;
}

};

class User {
protected:
    string role;
public:
    User(string role): role(role) {}
    virtual void menu() = 0;
};

class Owner : public User {
private:
    Bakery &bakery;
public:
    Owner(Bakery &b) : User("Owner"), bakery(b) {}

    void menu() override {
        int choice;
        string name;
        double price;
        int quantity;

        do {
            setTextColor(11);
            cout << "\nOwner Menu:\n1. Add Item\n2. Delete Item\n3. Modify Item\n4. Display Items\n5. View Orders\n6. Exit\n";
            cout << "Enter your choice: ";
            setTextColor(7);
            cin >> choice;
            system("CLS");

            switch (choice) {
                case 1:
                    setTextColor(11);
                    cout << "Enter item name: ";
                    setTextColor(7);
                    cin >> name;
                    setTextColor(11);
                    cout << "Enter item price: ";
                    setTextColor(7);
                    cin >> price;
                    setTextColor(11);
                    cout << "Enter item quantity: ";
                    setTextColor(7);
                    cin >> quantity;
                    setTextColor(11);
                    bakery.addItem(name, price, quantity);
                    Sleep(1000);
                    system("CLS");
                    setTextColor(2);
                    cout<<"Item Added";
                    Sleep(2000);
                    setTextColor(7);
                    system("CLS");
                    break;

                case 2:
                    setTextColor(11);
                    cout << "Enter item name to delete: ";
                    setTextColor(7);
                    cin >> name;
                    bakery.deleteItem(name);    
                    system("CLS");
                    break;

                case 3:
                    setTextColor(11);
                    cout << "Enter item name to modify: ";
                    setTextColor(7);
                    cin >> name;
                    setTextColor(11);
                    cout << "Enter new price: ";
                    setTextColor(7);
                    cin >> price;
                    setTextColor(11);
                    cout << "Enter new quantity: ";
                    setTextColor(7);
                    cin >> quantity;
                    bakery.modifyItem(name, price, quantity);
                    Sleep(2000);
                    setTextColor(7);
                    system("CLS");
                    break;

                case 4:
                    setTextColor(11);
                    bakery.displayItems();
                    Sleep(4000);
                    system("CLS");
                    setTextColor(7);
                    break;

                case 5:
                    setTextColor(11);
                    bakery.viewAllOrders(orders);
                    Sleep(6000);
                    system("CLS");
                    setTextColor(7);
                    break;

                case 6:
                    setTextColor(2);
                    cout << "Exiting...\n";
                    Sleep(3000);
                    system("CLS");
                    setTextColor(7);
                    break;

                default:
                    tryagain();
            }
        } while (choice != 6);
    }
};

class Staff : public User {
private:
    Bakery &bakery;
public:
    Staff(Bakery &b) : User("Staff"), bakery(b) {}

    void menu() override {
        int choice;
        string name;

        do {
            setTextColor(11);
            cout << "\nStaff Menu:\n1. Display Items\n2. Process Order\n3. View Customer Orders\n4. Exit\n";
            cout << "Enter your choice: ";
            setTextColor(7);
            cin >> choice;
            system("CLS");

            switch (choice) {
                case 1:
                    setTextColor(11);
                    bakery.displayItems();
                    setTextColor(11);
                    Sleep(4000);
                    system("CLS");
                    break;

                case 2:
                    bakery.processOrder();
                    break;

                case 3:
                    setTextColor(11);
                    bakery.viewAllOrders(orders);
                    Sleep(6000);
                    system("CLS");
                    setTextColor(7);
                    break;

                case 4:
                    setTextColor(2);
                    cout << "Exiting...\n";
                    Sleep(3000);
                    system("CLS");
                    setTextColor(7);
                    break;

                default:
                    tryagain();
            }
        } while (choice != 4);
    }
};

class Customer : public User {
private:
    Bakery &bakery;
    string customerName;
    string customerPhone;
    string customerAddress; 
    queue<Item> orderQueue;
    double totalBill = 0.0;

public:
    Customer(Bakery &b) : User("Customer"), bakery(b) {}

    void enterDetails() {
        setTextColor(11);
        cout << "Enter your name: ";
        setTextColor(7);
        cin.ignore();
        getline(cin, customerName);

        setTextColor(11);
        cout << "Enter your phone number: ";
        setTextColor(7);
        cin >> customerPhone;
        setTextColor(11);
        cin.ignore(); 

        cout << "Enter your address: ";
        setTextColor(7);
        getline(cin, customerAddress);

        _getch();
        system("CLS");
    }

    void menu() override {
        int choice;
        string itemName;

        enterDetails();

        do {
            setTextColor(11);
            cout << "\nCustomer Menu:\n";
            cout << "1. Display Items\n";
            cout << "2. Place Order\n";
            cout << "3. Checkout\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";
            setTextColor(7);
            cin >> choice;
            system("CLS");

            switch (choice) {
                case 1:
                    setTextColor(11);
                    bakery.displayItems();
                    Sleep(4000);
                    setTextColor(7);
                    system("CLS");
                    break;

                case 2:
                    setTextColor(11);
                    cout << "Enter item name to order: ";
                    setTextColor(7);
                    cin >> itemName;
                    placeOrder(itemName);
                    break;

                case 3:
                    setTextColor(11);
                    checkout();
                    setTextColor(7);
                    Sleep(3000);
                    system("CLS");
                    break;

                case 4:
                    setTextColor(2);
                    cout << "Exiting...\n";
                    setTextColor(7);
                    Sleep(2000);
                    system("CLS");
                    return;

                default:
                    tryagain();
            }
        } while (choice != 4);
    }

    void placeOrder(string itemName) {
        bool itemFound = false;

        for (auto &item : inventory) {
            if (item.name == itemName && item.quantity > 0) {
                Item orderedItem = item;
                int quantity;

                setTextColor(11);
                cout << "Enter quantity: ";
                setTextColor(7);
                cin >> quantity;

                if (quantity > item.quantity) {
                    setTextColor(4);
                    cout << "Only " << item.quantity << " available.\n";
                    setTextColor(7);
                    return;
                }

                orderedItem.quantity = quantity;
                orderQueue.push(orderedItem);
                totalBill += orderedItem.price * quantity;

                item.quantity -= quantity; 
                bakery.saveToFile(); 

                setTextColor(2);
                system("CLS");
                cout << "Item added to your order!\n";
                setTextColor(7);
                Sleep(2000);
                itemFound = true;
                break;
            }
        }

        if (!itemFound) {
            setTextColor(4);
            cout << "Item not found or out of stock!\n";
            setTextColor(7);
            Sleep(2000);
            system("CLS");  
        }
    }

    void checkout() {
        if (orderQueue.empty()) {
            setTextColor(4);
            cout << "No items in your order!\n";
            setTextColor(7);
            Sleep(2000);
            system("CLS");
            return;
        }

        setTextColor(11);
        cout << "\n--- Checkout ---\n";
        cout << "Customer: " << customerName << " | Phone: " << customerPhone << " | Address: " << customerAddress << "\n";
        cout << "Items Ordered:\n";

        queue<Item> tempQueue = orderQueue;

        while (!tempQueue.empty()) {
            Item item = tempQueue.front();
            tempQueue.pop();
            cout << item.name << " - " << item.quantity << " x " << item.price << " = " << item.quantity * item.price << endl;
        }

        cout << "Total Bill: $" << totalBill << "\n";
        double pay;

        do {
            cout << "Pay bill: $";
            setTextColor(7);
            cin >> pay;

            if (pay < totalBill) {
                setTextColor(4);
                cout << "Insufficient amount! Please pay at least $" << totalBill << endl;
                setTextColor(7);
                }
           }
            while (pay < totalBill);

            setTextColor(2);
            cout << "Payment received!" << endl;
            setTextColor(11);
 
           if (pay > totalBill) {
            cout << "Your change: $" << (pay - totalBill) << "\n";
            }

            setTextColor(2);
            cout << "Order is being processed soon...\n";
            setTextColor(7);

        saveCustomerData();

        while (!orderQueue.empty()) orderQueue.pop();
        totalBill = 0.0;
    }

    void saveCustomerData() {
    ofstream file("orders.txt", ios::app);

    if (!file) {
        setTextColor(4);
        cout << "Error opening order file!\n";
        setTextColor(7);
        Sleep(2000);
        system("CLS");
        return;
    }

    queue<Item> tempQueue = orderQueue;

    while (!tempQueue.empty()) {
        Item item = tempQueue.front();
        tempQueue.pop();

        file << customerName << "|"
             << customerPhone << "|"
             << customerAddress << "|"
             << item.name << "|"
             << fixed << setprecision(2) << item.price << "|"
             << item.quantity << "\n";
    }
    file.close();
    orders= queue<CustomerOrder>();
    bakery.loadOrdersFromFile(orders);
}

};

void wavingBye() {
    system("CLS");  

    string frames[3] = {
        "         (\\__/)\n"
        "         (o.o )   Bye! \n"
        "         (>  >)  \n",

        "         (\\__/)\n"
        "         (o.o )/  Bye! \n"
        "         (  >)  \n",

        "         (\\__/)\n"
        "         (o.o )   Bye! \n"
        "         (<  )>  \n"
    };

    for (int i = 0; i < 6; i++) {  
        system("CLS");
        setTextColor(2);  
        cout << frames[i % 3] << endl;
        setTextColor(7);  
        Sleep(1000);  
    }

    system("CLS");
}
void goodbyeAnimation() {
    system("CLS");
    
    string byeMessage = "Goodbye!";
    setTextColor(14);
    
    // Animating Bye message
    for (size_t i = 0; i < byeMessage.length(); ++i) {
        cout << byeMessage[i];
        Sleep(250);
    }
    cout << "\n\n";
    setTextColor(10);
    string quote = "Baked with love, served with warmth—Areemal Cafe & Bakery, where every bite feels like home!";
    for (size_t i = 0; i < quote.length(); ++i) {
        cout << quote[i];
        Sleep(100); 
    }
    cout << "\n\n";
    setTextColor(7);
    Sleep(3000); 
    system("CLS"); 
}

int main() {
    setup();
    setTextColor(7);
    Bakery bakery;
    

    string pass;
    int role;
    do
    {
    setTextColor(11);
    system("CLS");
    cout << "Enter your role:\n1--> Owner\n2--> Staff\n3--> Customer\n0--> Exit "<<endl;
    setTextColor(7);
    cin >> role;

    if (role == 1)
     {
        system("CLS");
        Owner owner(bakery);
        setTextColor(11);
        cout<<"Enter Password:"<<endl;
        setTextColor(7);
        cin>>pass;
        if(pass ==OWNER_PASSWORD)   
        {
            system("CLS");
            owner.menu();
        } 
        else
        {
            tryagain();
        }    
    }
    else if (role == 2) {
        system("CLS");
        Staff staff(bakery);
        setTextColor(11);
        cout<<"Enter Password:"<<endl;
        setTextColor(7);
        cin>>pass;
        if(pass == STAFF_PASSWORD)
        {
            system("CLS");
            staff.menu();
        } 
        else
        {
            tryagain();
        }
    }
    else if (role == 3) {
        system("CLS");
        Customer customer(bakery);
        customer.menu();
    }
    else if (role == 0)
    {
       wavingBye();
       goodbyeAnimation();
       break;
    }
    else {
        tryagain();
    } 
    }
    while(true);

    return 0;
}
