#include <iostream>
#include <fstream>
using namespace std;

class Account {
public:
    int accNo;
    char name[50];
    float balance;

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void deposit(float amt) {
        balance += amt;
    }

    void withdraw(float amt) {
        if (amt <= balance)
            balance -= amt;
        else
            cout << "Insufficient Balance!\n";
    }
};

// Add Account
void addAccount() {
    Account a;
    ofstream file("bank.dat", ios::binary | ios::app);

    a.createAccount();
    file.write((char*)&a, sizeof(a));

    file.close();
    cout << "\nAccount Created Successfully!\n";
}

// Display All
void displayAll() {
    Account a;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&a, sizeof(a))) {
        a.display();
        cout << "------------------";
    }

    file.close();
}

// Search Account
void searchAccount(int accNo) {
    Account a;
    ifstream file("bank.dat", ios::binary);
    bool found = false;

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            a.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\nAccount Not Found!\n";

    file.close();
}

// Deposit
void depositMoney(int accNo) {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    float amt;
    bool found = false;

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            cout << "Enter Amount: ";
            cin >> amt;

            a.deposit(amt);

            int pos = -1 * sizeof(a);
            file.seekp(pos, ios::cur);
            file.write((char*)&a, sizeof(a));

            cout << "Amount Deposited!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Account Not Found!\n";

    file.close();
}

// Withdraw
void withdrawMoney(int accNo) {
    Account a;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    float amt;
    bool found = false;

    while (file.read((char*)&a, sizeof(a))) {
        if (a.getAccNo() == accNo) {
            cout << "Enter Amount: ";
            cin >> amt;

            a.withdraw(amt);

            int pos = -1 * sizeof(a);
            file.seekp(pos, ios::cur);
            file.write((char*)&a, sizeof(a));

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Account Not Found!\n";

    file.close();
}

// Main Menu
int main() {
    int choice, accNo;

    do {
        cout << "\n===== Bank Management System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Display All Accounts\n";
        cout << "3. Search Account\n";
        cout << "4. Deposit\n";
        cout << "5. Withdraw\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                cout << "Enter Account No: ";
                cin >> accNo;
                searchAccount(accNo);
                break;
            case 4:
                cout << "Enter Account No: ";
                cin >> accNo;
                depositMoney(accNo);
                break;
            case 5:
                cout << "Enter Account No: ";
                cin >> accNo;
                withdrawMoney(accNo);
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}