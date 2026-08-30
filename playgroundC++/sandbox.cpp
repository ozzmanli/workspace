#include <iostream>
#include <vector>
#include <string>

// Sandbox: scratch space for trying things out before turning an idea into
// a proper solved-problem file. Nothing in here is "the solution" to
// anything - experiment freely, break it, rewrite it.


class User
{
    private:
        int balance;
        std::string name;
        std::string pin;
    public:
        User();
        User(std::string name, std::string pin, int balance);
        std::string getName() const{return name;}
        std::string getPin() const{return pin;}
        ~User();
};

class ATM
{
private:
    /* data */
    std::vector<User> user; 
public:
    ATM(/* args */);
    User * authentication(User currentUser);
    void createNewUser();
    bool addUser(const User &u);
    bool deleteUser(const std::string& name);
    void depositMoney(int moneyIn);
    void withdrawMoney(int moneyOut);
    void checkBalance();
    void retrieveActionHistory();
    ~ATM();

};

ATM::ATM(/* args */)
{
    std::cout << "ATM created" << std::endl;
}

bool ATM::addUser(const User& u)
{
    user.push_back(u);
    return true;
}

bool ATM::deleteUser(const std::string& name)
{
    user.erase(
        std::remove_if(user.begin(), user.end(),
            [&](const User& candidate){return candidate.getName() == name;}),
             user.end());
    return true;
}

User * ATM::authentication(User currentUser)
{
    for(User & u: user)
    {
        if(u.getName() == currentUser.getName())
        {
            std::cout << "found user" << std::endl;
            return &u;
        }
    }
    return NULL;
}


void ATM::createNewUser()
{
    std::string name;
    std::string password;
    std::string input;

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password";
    std::getline(std::cin,password);

    // after an account was created we have to ask wether the created account is want,
    // to deposit some cash
    std::cout << "Enter the amount you want to store";
    std::getline(std::cin, input);
    int money = std::stoi(input);
    // after this we go to the main page with alternatives. 
    // The has to be somehow be saved in the system.
}

User::User()
{

}

User::User(std::string name, std::string pin, int balance)
    : balance(balance), name(std::move(name)), pin(std::move(pin))
{

}

User::~User()
{

}

void ATM::depositMoney(int moneyIn)
{

}

void ATM:: withdrawMoney(int moneyOut)
{

}

void ATM::checkBalance()
{

}

void ATM::retrieveActionHistory()
{

}


ATM::~ATM()
{
    std::cout << "ATM Destroyed" << std::endl;
}

// ATM_TESTING is defined by tests/test_sandbox.cpp before it #includes this
// file, so the test binary (which supplies its own main() via doctest)
// doesn't end up with two main() functions in one link.
#ifndef ATM_TESTING
int main() {
    std::cout << "C++ sandbox is alive." << std::endl;

    ATM myAtm;   // constructor runs here -> prints "ATM created"

    return 0;
}  // myAtm goes out of scope here -> destructor runs -> prints "ATM Destroyed"
#endif
