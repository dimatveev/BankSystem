#include "AccountBuilder.h"

int AccountBuilder::account_id = 1;

void AccountBuilder::Reset(){
  name = "";
  surname = "";
  address = "";
  login = "";
  password_hash = "";
  passport_num = 0;
  account_id += 1;
}

void AccountBuilder::SetName(std::string& newname){
  name = newname;
}

void AccountBuilder::SetSurname(std::string& newsurname){
  surname = newsurname;
}

void AccountBuilder::SetAddress(std::string& newaddress){
  address = newaddress;
}

void AccountBuilder::SetPassportNum(int newnum){
  passport_num = newnum;
}

void AccountBuilder::SetLogin(std::string& newlogin){
  login = newlogin;
}

void AccountBuilder::SetPassword(std::string& newpassword_hash){
  password_hash = newpassword_hash;
}

Account AccountBuilder::GetAccount(Bank& mybank){
  Account account(mybank);
  account.account_id = account_id;
  account.name = name;
  account.surname = surname;
  account.address = address;
  account.passport_num = passport_num;
  account.login = login;
  account.password_hash = password_hash;
  (*this).Reset();
  return account;
}