#pragma once
#include "Bank.h"
#include <string>
#include <iostream>

struct Account {
  Bank& bank;
  int account_id;
  std::string name;
  std::string surname;
  std::string address;
  int passport_num;
  std::string login;
  std::string password;  // должны поменять
  Account(Bank&);
  void CreateBill(int type_of_bill);
  void CheckBills();
  void CheckHistory();
  void Transaction(int bill_from, int bill_to, int amount_of_money);
  void AddMoney(int bill_to, int amount_of_money);
  void WithdrawMoney(int bill_from, int amount_of_money);
};