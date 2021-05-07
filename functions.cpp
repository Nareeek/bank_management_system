#include "declarations.h"
#include "customer.h"
#include "json.hpp"

using json = nlohmann::json;


int choose()
{
  std::string welcome = "\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n---- WELCOME TO THE MAIN MANU ----\n\n1. Create new account\n2. Update information of existing account\n3. For transactions\n4. Check the details of existing account\n5. Removing the existing account\n6. View customer's list\n7. Exit\n\n\nEnter your choice: ";

  std::cout << welcome;

  std::string number;
  std::cin >> number;

  while(number.length() != 1 || (!(std::isdigit(number[0]))) || (!(number[0] > 48 && number[0] < 56))){
    std::cin.clear();
    std::cout << "\ntry again!" << std::endl;
    std::cin >> number;
  }
  
  int n = number[0] - 48;
  return n;
}


long long int generate_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(100000000000, 999999999999);

    long long int number = dist(mt);
    return number;
}

void print(std::string& name, std::string& surname, std::string &id, std::string& login, std::string& password){
  
  std::cout << "\nName: ";
  std::cin >> name;
  
  std::cout << "Surname: ";
  std::cin >> surname;
  
  std::cout << "\nID: ";
  std::cin >> id;

  std::cout << "\nLogin: ";
  std::cin >> login;

  std::cout << "Password: ";
  std::cin >> password;
  std::cout << std::endl;

}

void adding_new_json_object(Customer& customer, json& Accounts){
  std::cout << "+";

    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "ID"){
            if(val.value() == customer.id){
              std::cout << "\n\n-------------\nThe ID-value is matching, wrong!\nAccount didn't created!\n---------------\n\n";
              return;
            }
          }   
        }
      }

  Accounts[std::to_string(generate_number())] =
    {
      {"Name", customer.name},
      {"Surname", customer.surname},
      {"ID", customer.id},
      {"Login", customer.login},
      {"Password", customer.password},
      {"Bank account", customer.bank_account},
      {"Balance", customer.balance}
    };

    
      std::cout << std::endl;
      std::cout << "\n----------------------\n";
      std::cout << "The new accout was created!\n";
      std::cout << "-----------------\n\n";
}


void update(json& Accounts, std::string& login, std::string& password){
    bool flag1 = false;
    bool flag2 = false;
    std::string banking_account_flag;

    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "Login"){
            if(val.value() == login){
              flag1 = true;
            }
          }

          if(val.key() == "Password"){
            if(val.value() == password){
              flag2 = true;
            }
          }
        }
          
        if(flag1 && flag2){
          std::string n, sn, id, l, p;
          banking_account_flag = item.value();

          std::cout << "\nName:";
          std::cin >> n;

          std::cout << "Surname:";
          std::cin >> sn;

          std::cout << "\nId:";
          std::cin >> id;

          std::cout << "\nLogin:";
          std::cin >> l;

          std::cout << "Password:";
          std::cin >> p;

          for (const auto& item : Accounts.items()){
            if(item.value() == banking_account_flag){
              for (const auto& val : item.value().items()){
                  if(val.key() == "Name"){
                    val.value() = n;
                  }
                  if(val.key() == "Surname"){
                    val.value() = sn;
                  }
                  if(val.key() == "ID"){
                    val.value() = id;
                  }
                  if(val.key() == "Login"){
                    val.value() = l;
                  }
                  if(val.key() == "Password"){
                    val.value() = p;
                  }           
                }
            }
          }
          return;
      }
    } 
    std::cout << std::endl;
    std::cout << "Incorrect login or password\n";
}


void print_account(json& Accounts, std::string& login, std::string& password){
    bool flag1 = false;
    bool flag2 = false;
    std::string banking_account_flag;

    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "Login"){
            if(val.value() == login){
              flag1 = true;
            }
            else {
              break;
            }
          }

          if(val.key() == "Password"){
            if(val.value() == password){
              flag2 = true;
            }
            else{
              break;
            }
          }
        }
          
        if(flag1 && flag2){
          std::cout << "\n\n-------\n";
          for (const auto& val : item.value().items()){
            if(val.key() == "Name"){
              std::cout << "Name: " << val.value() << std::endl;
            }

            if(val.key() == "Surname"){
              std::cout << "Surname: " << val.value() << std::endl;
              }

            if(val.key() == "ID"){
              std::cout << "ID: " << val.value() << std::endl;
              }

            if(val.key() == "Bank account"){
              std::cout << "Bank account: " << val.value() << std::endl;
              }

            if(val.key() == "Balance"){
              std::cout << "Balance: " << val.value() << " $" << std::endl;
              }

          }
          std::cout << "\n----------\n\n";
          return;
        }
        else {
          flag1 = false;
          flag2 = false;
        }
    }
    std::cout << std::endl;
    std::cout << "-----------------\nWrong login or password!\n-----------------";
    std::cout << std::endl;
    std::cout << std::endl;

}


void print_all_customers(json& Accounts){

    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
            
          if(val.key() == "Name"){


              std::cout << "Name: " << val.value() << std::endl;
            }

            if(val.key() == "Surname"){

              std::cout << "Surname: " << val.value() << std::endl;
              }

            if(val.key() == "Bank account"){

              std::cout << "Bank account: " << val.value() << std::endl;
              }
        }

        std::cout << "\n\n----------\n\n";
    }

    std::cout << "\n\n----------\n";
    std::cout << "You can check all customers list informations from new created customers_list.txt file!...";
    std::cout << "\n----------\n\n";
}


std::string CUSTOMERS(json& Accounts){
  std::string output, o1, o2, o3;

    for (const auto& item : Accounts.items())
    {
      output += "\n----------\n\n";
        for (const auto& val : item.value().items())
        {
            
          if(val.key() == "Name"){
            std::string temp1 = val.value();
            o1 = "Name: " + temp1 + "\n";
            }

            if(val.key() == "Surname"){
              std::string temp2 = val.value();
              o2 = "Surname: " + temp2 + "\n";

              }

            if(val.key() == "Bank account"){
              long long int bank_ = val.value();
              std::string temp3 = std::to_string(bank_);
              o3 = "Bank account: " + temp3 + "\n";

              }
        }
        output += o1 + o2 + o3;
        o1 = "";
        o2 = "";
        o3 = "";
        
    }
    return output;
}