#pragma once


void welcome();
int choose();
int input_number(std::string number, int a, int b);

void input_credentials(std::string& name, std::string& surname, std::string& id, std::string& login, std::string& password);
long long int generate_number();

void adding_new_customer(Customer& customer, json& Accounts);
void add_content_to_file(std::string filename, json& Accounts);


bool input_sign_in_credentials(std::string& login, std::string& password, std::string& id, json& account_flag, json& Accounts);
      
void update(json& account_flag, json& Accounts);
void input_update_credentials(int choise, std::string& new_name, std::string& new_surname, std::string& new_id, std::string& new_login, std::string& new_password);


void print(json& account_flag, json& Accounts);
void print_all_customers(json& Accounts);

std::string CUSTOMERS(json& Accounts);


void deleting(json& account_flag, json& Accounts);


void transfer(json& account_flag, json& Accounts);
bool is_valid_recipient(long long bank_account, json& Accounts);

void top_up_balance(json& account_flag, json& Accounts);