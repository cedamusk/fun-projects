#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

class Account{
private:
    std::string accountNumber;
    std::string customerName;
    double balance;
    std::string accountType;

public:
    Account(std::string accNum, std::string name, double initialBalance, std::string type)
        :accountNumber(accNum), customerName(name), balance(initialBalance), accountType(type){}

    std::string getAccountNumber() const{ return accountNumber;}
    std::string getCustomerName() const{return customerName;}
    double getBalance() const { return balance;}
    std::string getAccountType() const {return accountType;}

    bool deposit (double amount){
        if (amount > 0){
            balance += amount;
            return true;
        }
        return false;
    }
    bool withdraw (double amount){
        if (amount > 0 && amount<= balance){
            balance-= amount;
            return true;
        }
        return false;
    }
};

class Bank{
private:
    std::vector<Account> accounts;
    int lastAccountNumber;

    void clearInputBuffer(){
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
public:
    Bank() : lastAccountNumber(1000){

        void createAccount(){
            std::string name, type;
            double initialBalance;

            std::cout << "\nEnter customer name:";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter account type (Savings/current):";
            std::getline(std::cin, type);

            while (true){
                std::cout <<"Enter Initial balance: $";
                if (std::cin >> initialBalance && initialBalance >=0){
                    break;
                }
                std::cout <<"Invalid amount. Plead enter a valid positive number.\n";
                clearInputBuffer();
            }

            std::string accNum ='ACC' + std::to_string(++lastAccountNumber);
            accounts.emplace_back(accNum, name, initialBalance, type);

            std::cout <<"\nAccount created successfully!";
            std::cout <<"\nYour account number is: "<<accNum <<"\n";
        }
    }

    void displayAccount() const{
        std::string accNum;
        std::cout <<"\nEnter account number:";
        std::cin >>accNum;

        for (const auto& acc: accounts){
            if (acc.getAccountNumber()==accNum){
                std::cout <<"\nAccount details:";
                std::cout<<"\n-----------------";
                std::cout <<"\nAccount Number: "<<acc.getAccountNumber();
                std::cout<<"\nCustomer Name: "<<acc.getCustomerName();
                std::cout<<"\nAccount Type:"<<acc.getAccountType();
                std::cout<<"\nBalance: $"<<std::fixed<< std::setprecision(2) <<acc.getBalance() <<"\n";
                return;

            }
        }
        std::cout <<"\nAccount not found!\n";
    }

    void deposit(){
        std::string accNum;
        double amount;

        std::cout <<"\nEnter account number: ";
        std::cin >>accNum;

        for (auto& acc: accounts){
            if (acc.getAccountNumber()==accNum){
                std::cout <<"Enter amount to deposit: $";
                std::cin >> amount;

                if (acc.deposit(amount)){
                    std::cout << "\nDeposit successful!";
                    std::cout <<"\nNew Balance: $"<<std::fixed << std::setprecision(2)<<acc.getBalance()<<"\n";
                }else{
                    std::cout <<"\nInvalid amount for deposit!\n";
                }
                return;
            }
        }

        std::cout <<"\nAccount not found!\n";
    }

    void withdraw(){
        std::string accNum;
        double amount;

        std::cout <<"\nEnter account number:";
        std::cin >>accNum;

        for(auto& acc: accounts){
            if(acc.getAccountNumber()== accNum){
                std::cout <<"Enter amount to withdraw: $";
                std::cin >> amount;

                if(acc.withdraw(amount)){
                    std::cout <<"\nWithdrawal successful!";
                    std::cout <<"\nNew Balance: $"<<std::fixed <<std::setprecision(2)<< acc.getBalance() <<"\n";
                }else{
                    std::cout <<"\nInvalid amount or insufficient balance!\n";
                }
                return;
            }
        }
        std::cout <<"\nAccount not found!\n";
    }
}

void listAllAccounts() const{
    if (accounts.empty()){
        std::cout <<"\nNo accounts exist in the system.\n";
        return;
    }

    std::cout<<"\nAll Account Details:";
    std::cout <<"\n-----------------\n";
    for (const auto& acc:accounts){
        std::cout <<"\nAccount Number:"<< acc.getAccountNumber();
        std::cout<<"\nCustomer Name: "<<acc.getCustomerName();
        std::cout<<"\nAccount Type:"<<acc.getAccountType();
        std::cout<<"\nBalance:$"<<std::fixed <<std::setprecision(2) <<acc.getBalance();
        std::cout <<"\n------------------\n";
    }
}