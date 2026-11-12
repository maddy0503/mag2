// SecureBank Account Management System
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

class BankAccount
{
private:
    // Keep account number as string to preserve leading zeroes.
    // Indian banks use different account-number lengths.
    string accountNumber;
    string customerName;
    double balance;

    int depositCount;
    int withdrawalCount;
    int rejectedCount;

public:
    BankAccount()
    {
        accountNumber = "";
        customerName = "";
        balance = 0.0;
        depositCount = 0;
        withdrawalCount = 0;
        rejectedCount = 0;
    }

    bool createAccount(string accNo, string name, double openingBalance)
    {
        // General validation range for this demo, NOT an RBI-mandated limit.
        if (accNo.length() < 9 || accNo.length() > 18)
        {
            cout << "Error: Account number must contain 9 to 18 digits." << endl;
            return false;
        }

        for (int i = 0; i < (int)accNo.length(); i++)
        {
            if (accNo[i] < '0' || accNo[i] > '9')
            {
                cout << "Error: Account number must contain digits only." << endl;
                return false;
            }
        }

        if (name.empty())
        {
            cout << "Error: Customer name cannot be empty." << endl;
            return false;
        }

        if (openingBalance < 0)
        {
            cout << "Error: Opening balance cannot be negative." << endl;
            return false;
        }

        accountNumber = accNo;
        customerName = name;
        balance = openingBalance;

        cout << "Account created successfully." << endl;
        return true;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            rejectedCount++;
            cout << "Error: Deposit amount must be greater than zero." << endl;
        }
        else
        {
            balance += amount;
            depositCount++;
            cout << "Deposit successful." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            rejectedCount++;
            cout << "Error: Withdrawal amount must be greater than zero." << endl;
        }
        else if (amount > balance)
        {
            rejectedCount++;
            cout << "Error: Insufficient balance." << endl;
        }
        else
        {
            balance -= amount;
            withdrawalCount++;
            cout << "Withdrawal successful." << endl;
        }
    }

    void checkBalance()
    {
        cout << fixed << setprecision(2);
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void displayAccount()
    {
        cout << fixed << setprecision(2);
        cout << "\nAccount Details" << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Customer Name  : " << customerName << endl;
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void displayTransactionSummary()
    {
        cout << fixed << setprecision(2);
        cout << "\nTransaction Summary" << endl;
        cout << "Successful Deposits    : " << depositCount << endl;
        cout << "Successful Withdrawals : " << withdrawalCount << endl;
        cout << "Rejected Transactions  : " << rejectedCount << endl;
        cout << "Final Balance          : Rs. " << balance << endl;
    }
};

int main()
{
    BankAccount account;
    bool accountCreated = false;

    int choice;
    string accNo;
    string name;
    double amount, openingBalance;

    do
    {
        cout << "\n===== SecureBank Account Management System =====" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Balance Enquiry" << endl;
        cout << "5. Display Account Details" << endl;
        cout << "6. Display Transaction Summary" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Error: Please enter a valid menu number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            if (accountCreated)
            {
                cout << "Account already exists." << endl;
                break;
            }

            cout << "Enter Account Number (9 to 18 digits): ";
            cin >> accNo;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Customer Name: ";
            getline(cin, name);

            cout << "Enter Opening Balance: ";
            if (!(cin >> openingBalance))
            {
                cout << "Error: Please enter a valid opening balance." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            accountCreated = account.createAccount(accNo, name, openingBalance);
            break;

        case 2:
            if (!accountCreated)
            {
                cout << "Please create an account first." << endl;
                break;
            }

            cout << "Enter Deposit Amount: ";
            if (!(cin >> amount))
            {
                cout << "Error: Please enter a valid amount." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            account.deposit(amount);
            break;

        case 3:
            if (!accountCreated)
            {
                cout << "Please create an account first." << endl;
                break;
            }

            cout << "Enter Withdrawal Amount: ";
            if (!(cin >> amount))
            {
                cout << "Error: Please enter a valid amount." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            account.withdraw(amount);
            break;

        case 4:
            if (!accountCreated)
            {
                cout << "Please create an account first." << endl;
                break;
            }
            account.checkBalance();
            break;

        case 5:
            if (!accountCreated)
            {
                cout << "Please create an account first." << endl;
                break;
            }
            account.displayAccount();
            break;

        case 6:
            if (!accountCreated)
            {
                cout << "Please create an account first." << endl;
                break;
            }
            account.displayTransactionSummary();
            break;

        case 7:
            cout << "Thank you for using SecureBank." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 7);

    return 0;
}
