#include <iostream>

using namespace std;

int main() {
    char greeting[] = "Hello World";

};

struct Vector {
    int sz;
    double* elem;
};

enum class Color {red, green, blue};
Color x = Color::red;

class Vector {
    public:
    Vector(int s) : elem{new double[s]}, sz{s} { }
    double& operator[](int i) {
        if (i < 0 || size() <= i) throw out_of_range{"Vector::operator[]"};
        return elem[i];
    }
    int size() {
        return sz;
    } 

    ~Vector() {delete[] elem;}

    private:
        int sz;
        double* elem;

};

class BankAccount {
    public:
        BankAccount(string x, int y, double z) {
            owner = x;
            accountNumber = y;
            balance = z;
        }

        void deposit(double amount) {
            balance += amount;
        }

        void withdraw(double amount) {
            if (amount > balance) {
                cout << "Insufficient funds" << endl;
                return;
            }

            balance -= amount;
        }

        void display() {
            cout << "Account owner:" << owner << ".\nBalance:" << balance << ".\nAccount number:" << accountNumber << endl;
        }

        ~BankAccount() {
            cout << "Bank account of " << owner << " is being closed." << endl;
        }


    private:
        string owner;
        double balance;
        int accountNumber;
};