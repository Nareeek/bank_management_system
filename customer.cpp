#include "include.h"
#include "customer.h"
#include "functions.h"

Customer::Customer(std::string n, std::string sn, std::string _id, std::string l, std::string p): name(n), surname(sn), id(_id), login(l), password(p), bank_account(generate_number()), balance(0){

}
