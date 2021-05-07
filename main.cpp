#include "declarations.h"
#include "customer.h"
#include "json.hpp"

using json = nlohmann::json;

json Accounts;
json temp;


void adding_new_json_object(Customer& customer, json& Accounts);

void update(json& Accounts, std::string& login, std::string& password);

void print_account(json& Accounts, std::string& login, std::string& password);

void print_all_customers(json& Accounts);

std::string CUSTOMERS(json& Accounts);

int main() {

  bool exists = false;
  std::ifstream tempfile;
  tempfile.open("temp.json");

  if (tempfile.is_open()) {
    std::cout << std::endl;
    std::cout << "Welcome back!...\n\n";
    exists = true;
    tempfile.close();
    }
  else {
    std::cout << "\nThere is no old data! Brand new system!...\n\n";
    }

  if(exists){
    std::ifstream temp_file("temp.json", std::ifstream::binary);
    temp_file >> temp;

    Accounts = temp;

    remove("temp.json");
  }

  while(1){
    int choise = choose();

    if(choise == 1){
      std::cout << "\nCreating a new account!\n";
      std::string n, sn, login, password, id;
      
      print(n, sn, id, login, password);
      Customer customer(n, sn, id, login, password);

      adding_new_json_object(customer, Accounts);

      

      std::fstream myfile;
      myfile.open("accounts.json", std::ios::out);

      if (myfile.is_open()) {
        myfile << std::setw(4) << Accounts << std::endl;
        myfile.close();
        }
      else {
        std::cout << "Unable to open file";
        }

    }

    else if (choise == 2){
      std::cout << "\nUpdate account!\n";
      std::cout << "Please enter your login and password for updateing account!...\n";

      std::string login, password;
      
      std::cout << "\nLogin: ";
      std::cin >> login;

      std::cout << "Password: ";
      std::cin >> password;
      std::cout << std::endl;

      update(Accounts, login, password);
    }

    else if (choise == 4){

      std::cout << "\nChecking account details!\n";
      std::cout << "Please enter your login and password!...\n";

      std::string login, password;
      
      std::cout << "\nLogin: ";
      std::cin >> login;

      std::cout << "Password: ";
      std::cin >> password;

      print_account(Accounts, login, password);
    }

    else if (choise == 6){
      std::cout << std::endl;
      std::cout << "\n----------\n";

      print_all_customers(Accounts);

      std::string customers_list = CUSTOMERS(Accounts);

      std::ofstream add_all_customers_in_file("customers_list.txt");

      if (add_all_customers_in_file.is_open()) {
        add_all_customers_in_file << customers_list << std::endl;
        add_all_customers_in_file.close();
        }
      else {
        std::cout << "Unable to open file";
        }
             
    }

    else if(choise == 7){
      temp = Accounts;

      std::fstream tempfile;
      tempfile.open("temp.json", std::ios::out);

      if (tempfile.is_open()) {
        tempfile << std::setw(4) << temp << std::endl;
        tempfile.close();
        }
      else {
        std::cout << "Unable to open file";
        }
    
      break; }

  }
}