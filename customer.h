#pragma once
#include <iostream>
#include <string>

class Customer{
  public:
    std::string name;
    std::string surname;
    std::string id;
    std::string login;
    std::string password;
    long long bank_account;
    long balance;
    // static unsigned counter;


    Customer(std::string n, std::string sn, std::string _id, std::string l, std::string p);
    
};
