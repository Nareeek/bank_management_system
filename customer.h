#pragma once

class Customer{
  public:
    Customer(std::string n, std::string sn, std::string _id, std::string l, std::string p);

    std::string get_name(){ return name;};
    std::string get_surname(){ return surname;};
    std::string get_id(){ return id;};
    std::string get_login(){ return login;};
    std::string get_password(){ return password;};
    
    long long get_bank_account(){ return bank_account;};
    long get_balance(){ return balance;};
    

  private:
    std::string name;
    std::string surname;
    std::string id;
    std::string login;
    std::string password;
    long long bank_account;
    long balance;   
};

