#pragma once
#include <string>
#include <fstream>
#include "AbstractFactory.h"
#include "DebitBillFactory.h"
#include "CreditBillFactory.h"
#include "DepositBillFactory.h"
#include "AccountBuilder.h"
#include "CreditBill.h"
#include "DebitBill.h"
#include "DepositBill.h"

struct Bank {
  std::string name;
  int id_for_bills = 0;
  int id_for_accounts = 0;
  void AddBillInFile(CreditBill&, int);
  void AddBillInFile(DebitBill&, int);
  void AddBillInFile(DepositBill&, int);
  void CreateAccount(std::string&, std::string&, std::string&, std::string&, std::string&, int);
  //Account& LoginTo(std::string login, std::string password);  // password нельзя передовать как стринг
  bool CreateBill(int type_of_bill, int account_id);  // true если счёт создан
  void CheckBills(int account_id);
  void CheckHistory(int account_id);
  bool Transaction(int bill_from, int bill_to, int amount_of_money);  // true если можно перевести данную сумму денег
  void AddMoney(int bill_to, int amount_of_money);
  bool WithdrawMoney(int bill_from, int amount_of_money);  // true если можно снять данную сумму денег
};