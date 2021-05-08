#pragma once

class Customer{
  public:
    std::string name;
    std::string surname;
    std::string id;
    std::string login;
    std::string password;
    long long bank_account;
    long balance;

    Customer(std::string n, std::string sn, std::string _id, std::string l, std::string p);
    
};
