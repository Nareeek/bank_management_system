#include "include.h"
#include "customer.h"
#include "functions.h"

json Accounts;
json temp;
json account_flag;


int main() {

  // put "temp.json" into Accounts and remove.
  std::ifstream tempfile;
  tempfile.open("temp.json");

  if (tempfile.is_open()) {
    std::cout << "Welcome back!...\n\n";
    tempfile.close();

    std::ifstream temp_file("temp.json", std::ifstream::binary);
    temp_file >> temp;

    Accounts = temp;
    remove("temp.json");
    }

  else {
    std::cout << "\nThere is no old data! Brand new system!...\n\n";
    }


  // Starting program.
  while(1){
    welcome();
    int choise = choose();

    // 1.Creating new customer.
    if(choise == 1){
      std::cout << "\n\nCreating a new account!\n\n";
      std::string n, sn, login, password, id;
      
      input_credentials(n, sn, id, login, password);
      Customer customer(n, sn, id, login, password);

      adding_new_customer(customer, Accounts);
      add_content_to_file("accounts.json", Accounts);

    }

    // 2.Updating customer information.
    else if(choise == 2){
      std::cout << "\nUpdate account!\n";
      std::cout << "Please enter your login, password and ID - for updating account!...\n";
      std::string login, password, id;

      bool is_valid_user = input_sign_in_credentials(login, password, id, account_flag, Accounts);

      if(is_valid_user){
        update(account_flag, Accounts);
      } else{
        std::cout << "\n\n----------\nIncorrect login, password or id\n----------\n\n";
      }
    }

    // 3.transactions
    else if (choise == 3){
      std::cout << "\nNew transaction!\n";
      std::cout << "Please enter your login, password and ID - for transaction!...\n";
      std::string login, password, id;

      bool is_valid_user = input_sign_in_credentials(login, password, id, account_flag, Accounts);

      if(is_valid_user){
        std::cout << "\n\n-----\nChoose transaction number\n-----\n\n1.Transfer from your account!.\n2.Top up the balance in cash\n-----\n\n";
        
        std::string direction_str;
        int direction = input_number(direction_str, 1, 2);
        std::cout << "\n\n----------\nNew transaction!\n----------\n\n";
          
        if(direction == 1){
          transfer(account_flag, Accounts);
        } else if(direction == 2){
          top_up_balance(account_flag, Accounts);
        }
      } else{
        std::cout << "\n\n----------\nIncorrect login, password or id\n----------\n\n";
      }
    }

    // 4.Checking customer details.
    else if (choise == 4){
      std::cout << "\nChecking account details!\n";
      std::cout << "Please enter your login, password and ID!...\n";
      std::string login, password, id;
      
      bool is_valid_user = input_sign_in_credentials(login, password, id, account_flag, Accounts);

      if(is_valid_user){
        print(account_flag, Accounts);
      } else{
        std::cout << "\n\n----------\nIncorrect login, password or id\n----------\n\n";
      }
    }

    // 5.deleting account
    else if (choise == 5){
      std::cout << "\nDelete account!\n";
      std::cout << "Please enter your login, password and ID - for deleting account!...\n";
      std::string login, password, id;

      bool is_valid_user = input_sign_in_credentials(login, password, id, account_flag, Accounts);

      if(is_valid_user){
        deleting(account_flag, Accounts);
      } else{
        std::cout << "\n\n----------\nIncorrect login, password or id\n----------\n\n";
      }
    }

    // 6.Print customers list.
    else if (choise == 6){
      std::cout << "\n\n-----\nPrinting all Customers information!\n-----\n\n";

      print_all_customers(Accounts);

      // add all customers list in -> customers_list.txt
      std::string customers_list = CUSTOMERS(Accounts);
      std::ofstream customers_list_file("customers_list.txt");

      if (customers_list_file.is_open()) {
        customers_list_file << customers_list << std::endl;
        customers_list_file.close();
        }
      else {
        std::cout << "Unable to open file";
        }     
    }

    // 7.Exit the program.
    else if(choise == 7){
      std::cout << "\n\n-----\nExit from bank system!\n-----\n\n";

      temp = Accounts;
      add_content_to_file("temp.json", temp);    
      break;
      }
  }
}