#include "Bank.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

// функции для записи в файл

void Bank::AddBillInFile(CreditBill& bill, int account_id) {
  std::ofstream file;
  file.open("bd_bills.csv", std::ofstream::app);
  file << account_id << ',' << bill.unique_id << ',' << -1 << ',' << bill.money << "\n";
  file.close();
}

void Bank::AddBillInFile(DebitBill& bill, int account_id) {
  std::ofstream file;
  file.open("bd_bills.csv", std::ofstream::app);
  file << account_id << ',' << bill.unique_id << ',' << 0 << ',' << bill.money << "\n";
  file.close();
}

void Bank::AddBillInFile(DepositBill& bill, int account_id) {
  std::ofstream file;
  file.open("bd_bills.csv", std::ofstream::app);
  file << account_id << ',' << bill.unique_id << ',' << 1 << ',' << bill.money << "\n";
  file.close();
}



// функция для получения содержимого файла

std::vector<std::vector<std::string> > ReadFile() {
  std::vector<std::vector<std::string> > vec;
  std::ifstream file("bd_bills.csv");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str;
    std::vector<std::string> undervec;
    for (int i = 0; i < 4; i++) {
      std::getline(iss, str, ',');
      undervec.push_back(str);
    }
    vec.push_back(undervec);
  }
  return vec;
}



// функция для создания аккаунта
/*
void Bank::CreateAccount() {  // ТРЕБУЕТ ДОРАБОТКИ
  AccountBuilder account_builder;
  Account account = account_builder.GetAccount();
  //...
  id_for_accounts += 1;
}
*/


// функция для входа на сайт
/*
Account& Bank::LoginTo(std::string login, std::string password) {};  // ТРЕБУЕТ ДОРАБОТКИ
*/


//функция создания счёта

bool Bank::CreateBill(int type_of_bill, int account_id) {
  if (type_of_bill == -1) {
    CreditBillFactory cf;
    CreditBill newbill = cf.CreateCredit();
    AddBillInFile(newbill, account_id);
  } else if (type_of_bill == 0) {
    DebitBillFactory df;
    DebitBill newbill = df.CreateDebit();
    AddBillInFile(newbill, account_id);
  } else if (type_of_bill == 1) {
    DepositBillFactory dpf;
    DepositBill newbill = dpf.CreateDeposit();
    AddBillInFile(newbill, account_id);
  } else {
    std::cout << "CreateBill error" << std::endl;
    return false;
  }
  return true;
}



// функция вывода списка счетов

void Bank::CheckBills(int account_id) {
  std::vector<std::vector<std::string> > vec;
  std::ifstream file("bd_bills.csv");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str;
    std::vector<std::string> undervec;
    for (int i = 0; i < 4; i++) {
      std::getline(iss, str, ',');
      undervec.push_back(str);
    }
    vec.push_back(undervec);
  }
  std::cout << "bill_id, type, amount" << std::endl;
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][0] == std::to_string(account_id)) {
      std::cout << vec[i][1] << ' ' << vec[i][2] << ' ' << vec[i][3] + "$" << std::endl; 
    }
  }
}



// функция для проверки истории

void Bank::CheckHistory(int account_id) {}  // ТРЕБУЕТ ДОРАБОТКИ



// функции для взаимодействия со счетами

void Bank::AddMoney(int bill_to, int amount_of_money) {
  auto vec = ReadFile();
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][1] == std::to_string(bill_to)) {
      vec[i][3] = std::to_string(std::stoi(vec[i][3]) + amount_of_money);
    }
  }
  std::ofstream file;
  file.open("bd_bills.csv");
  for (int i = 0; i < vec.size(); ++i) {
    file << vec[i][0] << ',' << vec[i][1] << ',' << vec[i][2] << ',' << vec[i][3] << "\n";
  }
  file.close();
}

bool Bank::WithdrawMoney(int bill_from, int amount_of_money) {
  auto vec = ReadFile();
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][1] == std::to_string(bill_from)) {
      if (std::stoi(vec[i][3]) - amount_of_money < 0) {
        return false;
      }
      vec[i][3] = std::to_string(std::stoi(vec[i][3]) - amount_of_money);
    }
  }
  std::ofstream file;
  file.open("bd_bills.csv");
  for (int i = 0; i < vec.size(); ++i) {
    file << vec[i][0] << ',' << vec[i][1] << ',' << vec[i][2] << ',' << vec[i][3] << "\n";
  }
  file.close();
  return true;
}

bool Bank::Transaction(int bill_from, int bill_to, int amount_of_money) {
  if (WithdrawMoney(bill_from, amount_of_money)) {
    AddMoney(bill_to, amount_of_money);
    return true;
  }
  return false;
}

int main() {
  Bank bank;
  bank.CreateBill(1, 69);  // bill id = 0
  bank.CreateBill(-1, 96);  // bill id = 1
  bank.AddMoney(69, 1000);
  bank.Transaction(69, 96, 300);
}