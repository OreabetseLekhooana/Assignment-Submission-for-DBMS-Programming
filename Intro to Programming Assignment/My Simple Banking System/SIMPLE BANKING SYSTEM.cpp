#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// User account structure to store account details
struct UserAccount {
    string accountNumber;
    string username;
    string password;
    double balance;
};

// Banking System class to manage user accounts and transactions
class BankingSystem {
private:
    unordered_map<string, UserAccount> accounts;

public:
    // Check if username exists
    bool isUsernameExists(const string& username) {
        return accounts.find(username) != accounts.end();
    }

    // Helper to get the logged-in user
    UserAccount* login(const string& username, const string& password) {
        if (isUsernameExists(username)) {
            UserAccount& user = accounts[username];
            if (user.password == password) {
                return &user;
            } else {
                cout << "Invalid password, please try again." << endl;
                return nullptr;
            }
        } else {
            cout << "Username not found." << endl;
            return nullptr;
        }
    }

    // Create a new user account
    void createAccount(const string& accountNumber, const string& username, const string& password) {
        if (!isUsernameExists(username)) {
            UserAccount newUser = {accountNumber, username, password, 0.0};
            accounts[username] = newUser;
            cout << "Account created successfully!" << endl;
        } else {
            cout << "Username already exists. Please choose another." << endl;
        }
    }

    // Deposit money into an account
    void depositMoney(UserAccount* user, double amount) {
        if (amount > 0) {
            user->balance += amount;
            cout << "Deposit successful! Current balance: R " << user->balance << endl;
        } else {
            cout << "Invalid amount." << endl;
        }
    }

    // Withdraw money from an account
    void withdrawMoney(UserAccount* user, double amount) {
        if (amount > 0 && amount <= user->balance) {
            user->balance -= amount;
            cout << "Withdrawal successful! Current balance: R " << user->balance << endl;
        } else if (amount > user->balance) {
            cout << "Insufficient funds for withdrawal." << endl;
        } else {
            cout << "Invalid amount." << endl;
        }
    }

    // Check account balance
    void checkBalance(const UserAccount* user) {
        cout << "Current balance: R " << user->balance << endl;
    }

    // Menu-driven interface
    void menu() {
        int option;
        string username, password, accountNumber;
        UserAccount* loggedInUser = nullptr;

        do {
            cout << "\n--- Simple Banking System ---" << endl;
            cout << "1. Create an Account" << endl;
            cout << "2. Login" << endl;
            cout << "3. Deposit Money" << endl;
            cout << "4. Withdraw Money" << endl;
            cout << "5. Check Balance" << endl;
            cout << "6. Exit" << endl;
            cout << "Select an option: ";
            cin >> option;

            switch (option) {
                case 1:
                    cout << "Enter Account Number: ";
                    cin >> accountNumber;
                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                    createAccount(accountNumber, username, password);
                    break;

                case 2:
                    if (loggedInUser == nullptr) {
                        cout << "Enter Username: ";
                        cin >> username;
                        cout << "Enter Password: ";
                        cin >> password;
                        loggedInUser = login(username, password);
                    } else {
                        cout << "You are already logged in" << endl;
                    }
                    break;

                case 3:
                    if (loggedInUser != nullptr) {
                        double amount;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        depositMoney(loggedInUser, amount);
                    } else {
                        cout << "Please login first." << endl;
                    }
                    break;

                case 4:
                    if (loggedInUser != nullptr) {
                        double amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        withdrawMoney(loggedInUser, amount);
                    } else {
                        cout << "Please login first." << endl;
                    }
                    break;

                case 5:
                    if (loggedInUser != nullptr) {
                        checkBalance(loggedInUser);
                    } else {
                        cout << "Please login first." << endl;
                    }
                    break;

                case 6:
                    cout << "Exiting..." << endl;
                    break;

                default:
                    cout << "Invalid option. Please try again." << endl;
            }
        } while (option != 6);
    }
};

// Main function to run the banking system
int main() {
    BankingSystem bankSystem;
    bankSystem.menu();
    return 0;
}


