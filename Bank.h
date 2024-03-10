#pragma once
#include <string>
#include "Account.h"

struct Bank {
  std::string name;
  void CreateAccount();
  Account& LoginTo(std::string login, std::string password);  // password нельзя передовать как стринг
  void CreateBill(int type_of_bill, std::string login);
  void CheckBills(std::string login);
  void Transaction(int bill_from, int bill_to, int amount_of_money);
  void AddMoney(int bill_to, int amount_of_money);
  void WithdrawMoney(int bill_from, int amount_of_money);
};