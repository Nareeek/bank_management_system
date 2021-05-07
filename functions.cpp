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


void update(json& Accounts, std::string& login, std::string& password, std::string& id){
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;

    bool name_changed = false;
    bool surname_changed = false;
    bool id_changed = false;
    bool login_changed = false;
    bool password_changed = false;
    bool exit = false;

    bool is_changed = false;
    json banking_account_flag;

    std::string _n, sn, _id, l, p, my_id;


    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "Login"){
            if(val.value() == login){
              flag1 = true;
            } else{
                break;
            }
          }

          if(val.key() == "Password"){
            if(val.value() == password){
              flag2 = true;
            } else{
                break;
            }
          }

        if(val.key() == "ID"){
            if(val.value() == id){
              my_id = val.value();
              flag3 = true;
            } else{
                break;
            }
          }
        }
          
        if(flag1 && flag2){
          if(flag3){
            banking_account_flag = item.value();
            is_changed = true;

            std::cout << "\n\n----------\nStart typing new information!\n----------\n\n";

            while(!(exit)){
              std::cout << "\n----------\nChoose what you want to change!\n----------\n1.Name\n2.Surname\n3.ID\n4.Login\n5.Password\n6.Exit\n----------\n";
              std::string number;
              std::cin >> number;

              while(number.length() != 1 || (!(std::isdigit(number[0]))) || (!(number[0] > 48 && number[0] < 56))){
                std::cin.clear();
                std::cout << "\ntry again!" << std::endl;
                std::cin >> number;
              }
              
              int n = number[0] - 48;

              if(n == 1){
                std::cout << "\nName: ";
                std::cin >> _n;
                name_changed = true;
              }

              if(n == 2){
                std::cout << "\nSurname: ";
                std::cin >> sn;
                surname_changed = true;
              }

              if(n == 3){
                std::cout << "\nID: ";
                std::cin >> _id;
                id_changed = true;
              }

              if(n == 4){
                std::cout << "\nLogin: ";
                std::cin >> l;
                login_changed = true;
              }

              if(n == 5){
                std::cout << "\nPassword: ";
                std::cin >> p;
                password_changed = true;
              }

              if(n == 6){
                exit = true;
              }
            }
          }
        } else{
           flag1 = false;
           flag2 = false;
           flag3 = false;
      }
    }
    
    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "ID"){
            if(val.value() == _id && val.value() != my_id){
              std::cout << "\n\n-------------\nThe ID-value is matching, wrong!\nAccount didn't updated!\n---------------\n\n";
              return;
            }
          }   
        }
      }


    if(is_changed){
      for (const auto& item : Accounts.items()){
        if(item.value() == banking_account_flag){
          for (const auto& val : item.value().items()){

              if(val.key() == "Name" && name_changed){
                Accounts[item.key()][val.key()] = _n;
              }

              if(val.key() == "Surname" && surname_changed){
                Accounts[item.key()][val.key()] = sn;
              }

              if(val.key() == "ID" && id_changed){
                Accounts[item.key()][val.key()] = _id;
              }

              if(val.key() == "Login" && login_changed){
                Accounts[item.key()][val.key()] = l;
              }

              if(val.key() == "Password" && password_changed){
                Accounts[item.key()][val.key()] = p;
              }           
            }
              std::fstream myfile;
              myfile.open("accounts.json", std::ios::out);

              if (myfile.is_open()) {
                myfile << std::setw(4) << Accounts << std::endl;
                myfile.close();
                }
              else {
                std::cout << "Unable to open file";
                }

              std::cout << "\n\nThe account successfully updated!\n\n";

              break;
        }
      }
    } else {
        std::cout << std::endl;
        std::cout << "Incorrect login or password\n";
    }
}


void print_account(json& Accounts, std::string& login, std::string& password, std::string& id){
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;

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

          if(val.key() == "ID"){
            if(val.value() == id){
              flag3 = true;
            }
            else{
              break;
            }
          }
        }
          
        if(flag1 && flag2){
          if(flag3){
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
        }
        else {
          flag1 = false;
          flag2 = false;
          flag3 = false;
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


void deleting(json& Accounts, json& temp,std::string& login, std::string& password, std::string& id){
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    bool is_changed = false;
    json banking_account_flag;


    for (const auto& item : Accounts.items())
    {
        for (const auto& val : item.value().items())
        {
          if(val.key() == "Login"){
            if(val.value() == login){
              flag1 = true;
            } else{
                break;
            }
          }

          if(val.key() == "Password"){
            if(val.value() == password){
              flag2 = true;
            } else{
                break;
            }
          }

          if(val.key() == "ID"){
            if(val.value() == id){
              flag3 = true;
            } else{
                break;
            }
          }
        }
          
        if(flag1 && flag2){
          if(flag3){
            banking_account_flag = item.value();
            is_changed = true;
            break;
          }

        } else{
           flag1 = false;
           flag2 = false;
           flag3 = false;
      }
    }


    if(is_changed){
      for (const auto& item : Accounts.items()){
        if(item.value() == banking_account_flag){

            Accounts.erase(item.key());
            std::cout << "\n\nThe account successfully deleted!\n\n";


            std::fstream myfile;
            myfile.open("accounts.json", std::ios::out);

            if (myfile.is_open()) {
              myfile << std::setw(4) << Accounts << std::endl;
              myfile.close();
              }
            else {
              std::cout << "Unable to open file";
              }

            std::cout << "\n\nThe account successfully deleted!\n\n";

            return;
        }
      }
    } else {
        std::cout << std::endl;
        std::cout << "Incorrect login or password\n";
    }

}