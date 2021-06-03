#include "include.h"
#include "customer.h"
#include "functions.h"



void functions::welcome(){
  std::cout << "\nCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n---- WELCOME TO THE MAIN MANU ----\n\n1. Create new account\n2. Update information of existing account\n3. For transactions\n4. Check the details of existing account\n5. Removing the existing account\n6. View customer's list\n7. Exit\n\n\nEnter your choice: ";
}


int functions::choose(){
  std::string number;

  int num = input_number(number, 1, 7);
  return num;
}


int functions::input_number(std::string number, int a, int b){
  a += 48;
  b += 48;
  std::cin >> number;

  while(number.length() != 1 || (!(std::isdigit(number[0]))) || (!(number[0] >= a && number[0] <= b))){
    std::cin.clear();
    std::cout << "\ntry again!" << std::endl;
    std::cin >> number;
  }
  
  int n = number[0] - 48;
  return n;

}


void functions::input_credentials(std::string& name, std::string& surname, std::string &id, std::string& login, std::string& password){
  
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


long long int functions::generate_number() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(100000000000, 999999999999);

    long long int number = dist(mt);
    return number;
}


void functions::adding_new_customer(Customer& customer, json& Accounts){

    // checking for valid(non repetitive) customer id
    for (const auto& item : Accounts.items()){
        for (const auto& val : item.value().items()){
          if(val.key() == "ID"){
            if(val.value() == customer.get_id()){
              std::cout << "\n\n-------------\nThe ID-value is matching, wrong!\nAccount didn't created!\n---------------\n\n";
              return;
            }
          }   
        }
      }

  Accounts[std::to_string(generate_number())] =
    {
      {"Name", customer.get_name()},
      {"Surname", customer.get_surname()},
      {"ID", customer.get_id()},
      {"Login", customer.get_login()},
      {"Password", customer.get_password()},
      {"Bank_account", customer.get_bank_account()},
      {"Balance", customer.get_balance()}
    };

  std::cout << "\n----------------------\nThe new accout was created!\n-----------------\n\n";
}


void functions::add_content_to_file(std::string filename, json& Accounts){
    std::fstream myfile;
    myfile.open(filename, std::ios::out);

    if (myfile.is_open()) {
      myfile << std::setw(4) << Accounts << std::endl;
      myfile.close();
      }
    else {
      std::cout << "Unable to open file";
      }
}

bool functions::input_sign_in_credentials(std::string& login, std::string& password, std::string& id, json& account_flag, json& Accounts){
    std::cout << "\nLogin: ";
    std::cin >> login;

    std::cout << "Password: ";
    std::cin >> password;

    std::cout << "\nID: ";
    std::cin >> id;
    std::cout << std::endl;

    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    for (const auto& item : Accounts.items()){
      for (const auto& val : item.value().items()){
        if(val.key() == "Login"){
          if(val.value() == login){
            flag1 = true;
            }else{
              break;
              }
            }
        
        if(val.key() == "Password"){
          if(val.value() == password){
            flag2 = true;
            }else{
              break;
              }
            }

        if(val.key() == "ID"){
          if(val.value() == id){
            flag3 = true;
            }else{
              break;
              }
            }

          }
              
        if(flag1 && flag2){
          if(flag3){
            account_flag = item.value();
            return true;
          }
        }
    }
    return false;
}


void functions::input_update_credentials(int choise, std::string& new_name, std::string& new_surname, std::string& new_id, std::string& new_login, std::string& new_password){
  

  switch(choise) {
    case 1:
      std::cout << "\nNew Name: ";
      std::cin >> new_name;
        break;
    case 2:
      std::cout << "\nNew Surname: ";
      std::cin >> new_surname;
        break;
    case 3:
      std::cout << "\nNew ID: ";
      std::cin >> new_id;
        break;
    case 4:
      std::cout << "\nNew Login: ";
      std::cin >> new_login;
        break;
    case 5:
      std::cout << "\nNew Password: ";
      std::cin >> new_password;
        break;
    default:
        break;
    }

}


void functions::update(json& account_flag, json& Accounts){
  std::string new_name="", new_surname="", new_id="", new_login="", new_password="";


  // choose and enter the modified information.
  std::cout << "\n-----\nChoose what you want to change!\n-----\n1.Name\n2.Surname\n3.ID\n4.Login\n5.Password\n6.Exit\n-----\n";

  std::string number;
  int choise = input_number(number, 1, 6);
  
  while(choise != 6){
    input_update_credentials(choise, new_name, new_surname, new_id, new_login, new_password);
    std::cout << "\n\n-----\nWhat else?\n-----\n";
    choise = input_number(number, 1, 6);
  }
  

  // updating information
  for (const auto& item : Accounts.items()){
    if(item.value() == account_flag){
      for (const auto& val : item.value().items()){

          if(val.key() == "Name" && (new_name != "")){
            Accounts[item.key()][val.key()] = new_name;
          }

          if(val.key() == "Surname" && (new_surname != "")){
            Accounts[item.key()][val.key()] = new_surname;
          }

          if(val.key() == "ID" && (new_id != "")){
            Accounts[item.key()][val.key()] = new_id;
          }

          if(val.key() == "Login" && (new_login != "")){
            Accounts[item.key()][val.key()] = new_login;
          }

          if(val.key() == "Password" && (new_password != "")){
            Accounts[item.key()][val.key()] = new_password;
          }           
        }

        add_content_to_file("accounts.json", Accounts);

        std::cout << "\n-----\nThe account successfully updated!\n-----\n";
        return;
    }
  }
}


void functions::print(json& account_flag, json& Accounts){

  std::cout << "\n\n----------\n\n";
  for (const auto& item : Accounts.items()){
    if(item.value() == account_flag){
      for (const auto& val : item.value().items()){
        std::cout << val.key() << ": " << val.value() << std::endl;
      }
    }
  }
  std::cout << "\n\n\n----------\n\n\n";
}


void functions::print_all_customers(json& Accounts){
  for (const auto& item : Accounts.items()){
      for (const auto& val : item.value().items()){
        if(val.key() != "Balance" && val.key() != "ID"){
          if(val.key() != "Login" && val.key() != "Password"){
            std::cout << val.key() << ": " << val.value() << std::endl;
          }
        }
      }
      std::cout << "\n\n\n\n----------\n\n\n\n";
    }
}

std::string functions::CUSTOMERS(json& Accounts){
  std::string output = "", o1, o2, o3;

  for (const auto& item : Accounts.items()){
    output += "\n-----\n\n";
    for (const auto& val : item.value().items()){
        
      if(val.key() == "Name"){
        std::string temp1 = val.value();
        o1 = "Name: " + temp1 + "\n";
        }

        if(val.key() == "Surname"){
          std::string temp2 = val.value();
          o2 = "Surname: " + temp2 + "\n";
          }

        if(val.key() == "Bank_account"){
          long long int bank_ = val.value();
          std::string temp3 = std::to_string(bank_);
          o3 = "Bank_account: " + temp3 + "\n";
          }
    }
    output += o1 + o2 + o3;
    o1 = ""; o2 = ""; o3 = ""; 
  }
  return output;
}


void functions::deleting(json& account_flag, json& Accounts){

    for (const auto& item : Accounts.items()){
      if(item.value() == account_flag){
          Accounts.erase(item.key());
          std::cout << "\n\nThe account successfully deleted!\n\n";

          add_content_to_file("accounts.json", Accounts);
          return;
      }
    }
}


bool functions::is_valid_recipient(long long bank_account, json& Accounts, json& account_flag){
  
  for (const auto& item : Accounts.items()){
    if (item.value() != account_flag){
      for (const auto& val : item.value().items()){
        if(val.key() == "Bank_account"){
          if(val.value() == bank_account){
            return true;
          } else{ break; }
        }
      }
    }
  }
  return false;
}
      
//not a functions class member
bool check_money_type(std::string money_str){
  if(money_str.size() > 12){
    std::cout << "\nInvalid number(very big)!\n";
    return false;
  }
  for(int i = 0; i < money_str.size(); i++){
    if (!(std::isdigit(money_str[i])) || std::isspace(money_str[i])){
      std::cout << "Invalid number!\nContains some letter(s)!\n";
      return false;
    }
  }
  return true;
}


void functions::transfer(json& account_flag, json& Accounts){
  try{
      std::cout << "\nEnter recipient bank account (number)!\n----------\n\n";

      std::cout << "\nBank_account: ";
      std::string _bank_account_str;

      getline(std::cin >> std::ws, _bank_account_str);
      long long _bank_account = 0;
      

      if(_bank_account_str.size() > 12){
          throw std::runtime_error("\nError!... Wrong bank_account number!\nMaximum 12 digits!\n");
      }
      for(auto el: _bank_account_str){
        if(isspace(el) || isalpha(el)){
          throw std::runtime_error("\nError!... Wrong bank_account number!\nContain letter(s)!");
        }
      }
      _bank_account = std::stoll(_bank_account_str);

      
      long int money = 0;

      if(!(is_valid_recipient(_bank_account, Accounts, account_flag))){
        std::cout << "\nInvalid bank account number\n\n";
        return;
      }

      // decreasing your balance.
      for (const auto& item : Accounts.items()){
        if(item.value() == account_flag){
          for (const auto& val : item.value().items()){
            if(val.key() == "Balance"){
              std::cout << "\n\n-----\nNow you have " << val.value() << "$ in your balance\n-----\n";
              std::cout << "How much you want to transfer from your account?\n----------\n\n";


              std::string money_str;
              getline(std::cin >> std::ws, money_str);

              bool is_valid_money = check_money_type(money_str);

              // change string(money) -> int(money)
              while(!(is_valid_money)){
                std::cout << "\n\n-----\nNot a valid money type, try again!\n-----\n\n";

                std::cin.clear();
                getline(std::cin >> std::ws, money_str);
                is_valid_money = check_money_type(money_str);
              }

                std::stringstream geek(money_str);
                geek >> money; 

                long int current_balance = Accounts[item.key()][val.key()];

                if (money <= current_balance){
                  Accounts[item.key()][val.key()] = current_balance - money;
                  break;
                }else{
                  std::cout << "\n\n----------\nYou can't transfer, not enough balance!\n----------\n\n";
                  return;
                }
              }
            }
          }
        }

      //increasing recipient balance.
      json resipient_flag;
      for (const auto& item : Accounts.items()){
          for (const auto& val : item.value().items()){
            if(val.key() == "Bank_account"){
              if(Accounts[item.key()][val.key()] == _bank_account){
                resipient_flag = item.value();
              }
            }
          }
        }

      for (const auto& item : Accounts.items()){
        if(item.value() == resipient_flag){
          for (const auto& val : item.value().items()){
            if(val.key() == "Balance"){
              long int recipient_current_ballance = Accounts[item.key()][val.key()];
              Accounts[item.key()][val.key()] = recipient_current_ballance + money;
            } 
          }
        }
      }
      std::cout << "\n\n----------\nThe transfer done successfully!\n----------\n";
      add_content_to_file("accounts.json", Accounts);
  }
  catch(const std::exception& ex){
    std::cout << ex.what() << '\n';
  }
}



void functions::top_up_balance(json& account_flag, json& Accounts){
  
    long int money = 0;

    for (const auto& item : Accounts.items()){
      if(item.value() == account_flag){
        for (const auto& val : item.value().items()){
          if(val.key() == "Balance"){
            std::cout << "Now you have " << val.value() << "$ in your balance \n\n";

            std::cout << "\n\n----------\nhow much do you want to add cash to your account?\n----------\n\n";

            std::string money_str;
            getline(std::cin >> std::ws, money_str);

            bool is_valid_money = check_money_type(money_str);

            // change string(money) -> int(money)
            while(!(is_valid_money)){
              std::cout << "\n\n-----\nNot a valid money type, try again!\n-----\n\n";

              std::cin.clear();
              getline(std::cin >> std::ws, money_str);
              is_valid_money = check_money_type(money_str);
            }

            std::stringstream geek(money_str);
            geek >> money; 

            long int current_balance = Accounts[item.key()][val.key()];

            Accounts[item.key()][val.key()] = current_balance + money;

            add_content_to_file("accounts.json", Accounts);
            std::cout << "\n\n----------\nY've successfully top-up your bank account!\n----------\n\n";
          }
        }
      }
    }
  }

