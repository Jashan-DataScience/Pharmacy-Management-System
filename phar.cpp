#include <iostream>
#include <string>
using namespace std;
struct Medicine {
int id;
string name;
string category;
double price;
double cost;
int quantity;
string expiryDate;
};
// medicine categories
struct Category {
string name;
string description;
};
// Bill item
struct BillItem {
int medicineIndex;
int quantity;
};
// store data
Medicine medicines[1000];
Category categories[50];
BillItem billItems[100];
int medicineCount = 0;
int categoryCount = 0;
int billItemCount = 0;
// declarations
void addNewMedicine();
void updateStockQuantity();
void manageCategories();
void removeExpiredMedicine();
void billCalculationSystem();
void salaryCalculation();
void totalProfitCalculation();
void displayMainMenu();
int main() {
cout << "=== WELCOME TO PHARMACY MANAGEMENT SYSTEM ===" << endl;
cout << "Making pharmacy operations easier and more efficient!" << endl;
    int choice;

    // main menu
    while (true) {
        displayMainMenu();

        cout << "Enter your choice (1-8): ";
        cin >> choice;

        // Switch statement for menu selection
        switch (choice) {
            case 1:
                addNewMedicine();
                break;
            case 2:
                updateStockQuantity();
                break;
            case 3:
                manageCategories();
                break;
            case 4:
                removeExpiredMedicine();
                break;
            case 5:
                billCalculationSystem();
                break;
            case 6:
                salaryCalculation();
                break;
            case 7:
                totalProfitCalculation();
                break;
            case 8:
                cout << "Thank you for using Pharmacy Management System! Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    return 0;
}

void displayMainMenu() {
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Add New Medicine" << endl;
    cout << "2. Update Stock Quantity" << endl;
    cout << "3. Manage Categories" << endl;
    cout << "4. Remove Expired Medicine" << endl;
    cout << "5. Bill Calculation System" << endl;
    cout << "6. Salary Calculation" << endl;
    cout << "7. Total Profit Calculation" << endl;
    cout << "8. Exit" << endl;
    cout << "=====================" << endl;
}

void addNewMedicine() {
    cout << "\n--- ADD NEW MEDICINE ---" << endl;

    Medicine newMed;
    cout << "Enter Medicine ID: ";
    cin >> newMed.id;

    // Check if medicine already exists using for loop
    bool exists = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == newMed.id) {
            exists = true;
            cout << "Medicine with this ID already exists! Updating stock..." << endl;

            cout << "Enter quantity to add: ";
            int addQty;
            cin >> addQty;
            medicines[i].quantity += addQty;
            cout << "Stock updated successfully! Total quantity: " << medicines[i].quantity <<
endl;
            return;
        }
    }

    // add new one
    if (!exists) {
        cout << "Enter Medicine Name: ";
        cin.ignore();
        getline(cin, newMed.name);

        cout << "Enter Category: ";
        getline(cin, newMed.category);

        cout << "Enter Selling Price: $";
        cin >> newMed.price;

        cout << "Enter Cost Price: $";
        cin >> newMed.cost;

        cout << "Enter Quantity: ";
        cin >> newMed.quantity;

        cout << "Enter Expiry Date (DD/MM/YYYY): ";
        cin >> newMed.expiryDate;

        medicines[medicineCount] = newMed;
        medicineCount++;

        cout << "New medicine added successfully!" << endl;
    }
}

void updateStockQuantity() {
    cout << "\n--- UPDATE STOCK QUANTITY ---" << endl;

    int searchId;
    cout << "Enter Medicine ID to update: ";
    cin >> searchId;

    // Search for medicine
    bool found = false;
    for (int i = 0; i < medicineCount; i++) {
        if (medicines[i].id == searchId) {
            found = true;
            cout << "Medicine Found: " << medicines[i].name << endl;
            cout << "Current Quantity: " << medicines[i].quantity << endl;

            cout << "Enter new quantity: ";
            cin >> medicines[i].quantity;

            cout << "Stock quantity updated successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Medicine not found!" << endl;
    }
}

void manageCategories() {
    cout << "\n--- MANAGE CATEGORIES ---" << endl;

    int choice;
    cout << "1. Create New Category" << endl;
    cout << "2. See All Categories" << endl;
    cout << "3. Edit Category" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    // category management
    if (choice == 1) {
        // Create new category
        if (categoryCount < 50) {
            cout << "Enter Category Name: ";
            cin.ignore();
            getline(cin, categories[categoryCount].name);

            cout << "Enter Category Description: ";
            getline(cin, categories[categoryCount].description);

            categoryCount++;
            cout << "Category added successfully!" << endl;
        } else {
            cout << "Category limit reached!" << endl;
        }
    } else if (choice == 2) {
        // See all categories
        cout << "\n--- ALL CATEGORIES ---" << endl;
        if (categoryCount == 0) {
            cout << "No categories found!" << endl;
        } else {
            for (int i = 0; i < categoryCount; i++) {
                cout << (i+1) << ". " << categories[i].name << " - " << categories[i].description <<
endl;
            }
        }
    } else if (choice == 3) {
        // Edit category
        if (categoryCount == 0) {
            cout << "No categories to edit!" << endl;
            return;
        }

        cout << "Select category to edit:" << endl;
        for (int i = 0; i < categoryCount; i++) {
            cout << (i+1) << ". " << categories[i].name << endl;
        }

        int catChoice;
        cout << "Enter category number: ";
        cin >> catChoice;

        if (catChoice > 0 && catChoice <= categoryCount) {
            cout << "Enter new category name: ";
            cin.ignore();
            getline(cin, categories[catChoice-1].name);

            cout << "Enter new description: ";
            getline(cin, categories[catChoice-1].description);

            cout << "Category updated successfully!" << endl;
        } else {
            cout << "Invalid category choice!" << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }
}

void removeExpiredMedicine() {
    cout << "\n--- REMOVE EXPIRED MEDICINE ---" << endl;

    string currentDate;
    cout << "Enter today's date (DD/MM/YYYY): ";
    cin >> currentDate;

    // expired medicines
    int expiredIndices[100];
    int expiredCount = 0;

    // Find expired medicines
    for (int i = 0; i < medicineCount; i++) {
        // expiry date
        if (medicines[i].expiryDate < currentDate) {
            expiredIndices[expiredCount] = i;
            expiredCount++;
        }
    }

    if (expiredCount == 0) {
        cout << "No expired medicines found!" << endl;
        return;
    }

    // expired medicines
    cout << "\nEXPIRED MEDICINES:" << endl;
    for (int i = 0; i < expiredCount; i++) {
        int idx = expiredIndices[i];
        cout << (i+1) << ". " << medicines[idx].name << " (ID: " << medicines[idx].id
             << ") - Expired: " << medicines[idx].expiryDate << endl;
    }

    char confirm;
    cout << "Are you sure you want to remove these expired medicines? (y/n): ";
    cin >> confirm;


    if (confirm == 'y' || confirm == 'Y') {
        // Remove expired medicines
        for (int i = expiredCount - 1; i >= 0; i--) {
            int idx = expiredIndices[i];
            cout << "Removing: " << medicines[idx].name << endl;


            for (int j = idx; j < medicineCount - 1; j++) {
                medicines[j] = medicines[j + 1];
            }
            medicineCount--;
        }
        cout << "Expired medicines have been cleared out!" << endl;
    } else {
        cout << "Operation cancelled." << endl;
    }
}

void billCalculationSystem() {
    cout << "\n--- BILL CALCULATION SYSTEM ---" << endl;

    // Reset bill items
    billItemCount = 0;
    double totalBill = 0;

    char addMore = 'y';

    // adding items to bill
    do {
        if (billItemCount >= 100) {
            cout << "Bill is full! Cannot add more items." << endl;
            break;
        }

        int medId, qty;
        cout << "Enter Medicine ID: ";
        cin >> medId;

        // Find medicine
        bool found = false;
        int medIndex = -1;
        for (int i = 0; i < medicineCount; i++) {
            if (medicines[i].id == medId) {
                found = true;
                medIndex = i;
                break;
            }
        }

        if (found) {
            cout << "Medicine: " << medicines[medIndex].name << " - Price: $" <<
medicines[medIndex].price << endl;
            cout << "Available Quantity: " << medicines[medIndex].quantity << endl;

            cout << "Enter quantity to buy: ";
            cin >> qty;

            // Check stock
            if (qty <= medicines[medIndex].quantity && qty > 0) {
                billItems[billItemCount].medicineIndex = medIndex;
                billItems[billItemCount].quantity = qty;
                billItemCount++;
                medicines[medIndex].quantity -= qty; // Update stock
                cout << "Item added to bill!" << endl;
            } else {
                cout << "Invalid quantity or not enough stock available!" << endl;
            }
        } else {
            cout << "Medicine not found!" << endl;
        }

        if (billItemCount < 100) {
            cout << "Add more items? (y/n): ";
            cin >> addMore;
        }
    } while ((addMore == 'y' || addMore == 'Y') && billItemCount < 100);

    // Calculate total
    cout << "\n--- BILL SUMMARY ---" << endl;
    for (int i = 0; i < billItemCount; i++) {
        int medIndex = billItems[i].medicineIndex;
        double itemTotal = medicines[medIndex].price * billItems[i].quantity;
        totalBill += itemTotal;
        cout << medicines[medIndex].name << " x " << billItems[i].quantity << " = $" <<
itemTotal << endl;
    }

    cout << "Subtotal: $" << totalBill << endl;

    // Apply discount
    char hasMembership;
    cout << "Does customer have membership card? (y/n): ";
    cin >> hasMembership;

    double discount = 0;
    double finalAmount = totalBill;

    if (hasMembership == 'y' || hasMembership == 'Y') {
        discount = totalBill * 0.10; // 10% discount
        finalAmount = totalBill - discount;
        cout << "Membership Discount (10%): -$" << discount << endl;
    }

    cout << "Final Amount: $" << finalAmount << endl;

    // Payment processing
    cout << "\n--- PAYMENT ---" << endl;
    int paymentMethod;
    cout << "Choose payment method: 1. Cash 2. Card: ";
    cin >> paymentMethod;

    if (paymentMethod == 1) {
        double cashReceived;
        cout << "Enter cash amount received: $";
        cin >> cashReceived;


        while (cashReceived < finalAmount) {
            cout << "Insufficient cash! Amount due: $" << finalAmount << endl;
            cout << "Enter cash amount received: $";
            cin >> cashReceived;
        }

        double change = cashReceived - finalAmount;
        cout << "Change: $" << change << endl;

    } else if (paymentMethod == 2) {
        cout << "Card payment processed successfully!" << endl;
    } else {
        cout << "Invalid payment method!" << endl;
        return;
    }

    cout << "\n--- RECEIPT ---" << endl;
    cout << "Items purchased:" << endl;
    for (int i = 0; i < billItemCount; i++) {
        int medIndex = billItems[i].medicineIndex;
        cout << "- " << medicines[medIndex].name << " x " << billItems[i].quantity << endl;
    }
    cout << "Subtotal: $" << totalBill << endl;
    if (discount > 0) {
        cout << "Discount: $" << discount << endl;
}
cout << "Final Amount: $" << finalAmount << endl;
cout << "Thank you for your purchase!" << endl;
}
void salaryCalculation() {
cout << "\n--- SALARY CALCULATION ---" << endl;
string name;
int workingDays;
cout << "What is your name? ";
cin.ignore();
getline(cin, name);
cout << "How many days did you work this month? ";
cin >> workingDays;
while (workingDays < 0 || workingDays > 31) {
cout << "Invalid number of days! Enter between 0-31: ";
cin >> workingDays;
}
double salary = workingDays * 2000; // Assuming $2000 per day

    if (salary > 40000) {
        double bonus = 5000;
        double fullSalary = salary + bonus;
        cout << "\nHello " << name << "!" << endl;
        cout << "Your base salary: $" << salary << endl;
        cout << "Bonus: $" << bonus << endl;
        cout << "Full salary: $" << fullSalary << endl;
    } else {
        cout << "\nHello " << name << "!" << endl;
        cout << "Your salary: $" << salary << endl;
        cout << "No bonus this month." << endl;
    }
}

void totalProfitCalculation() {
    cout << "\n--- TOTAL PROFIT CALCULATION ---" << endl;

    int transactions;
    cout << "Enter number of transactions to calculate: ";
    cin >> transactions;


    while (transactions <= 0 || transactions > 100) {
        cout << "Enter number between 1-100: ";
        cin >> transactions;
    }

    double totalProfit = 0;
    double profits[100];


    for (int i = 0; i < transactions; i++) {
        cout << "\nTransaction " << (i + 1) << ":" << endl;

        double costPrice, sellingPrice;
        int quantity;
        double discount;

        cout << "Enter Cost Price: $";
        cin >> costPrice;

        cout << "Enter Selling Price: $";
        cin >> sellingPrice;

        cout << "Enter Quantity Sold: ";
        cin >> quantity;

        cout << "Enter Discount Amount: $";
        cin >> discount;

        // after discount
        double revenue = (sellingPrice * quantity) - discount;

        // Calculate total cost
        double totalCost = costPrice * quantity;

        // Calculate profit
        double profit = revenue - totalCost;
        profits[i] = profit;
        totalProfit += profit;

        cout << "Profit for this transaction: $" << profit << endl;
    }

    cout << "\n--- PROFIT SUMMARY ---" << endl;
    cout << "Total Profit from all transactions: $" << totalProfit << endl;


    cout << "Individual transaction profits:" << endl;
    for (int i = 0; i < transactions; i++) {
        cout << "Transaction " << (i + 1) << ": $" << profits[i] << endl;
    }
}
