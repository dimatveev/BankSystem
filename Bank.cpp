#include "AccountBuilder.cpp"
#include "AbstractFactory.cpp"
#include "DebitBillFactory.cpp"
#include "CreditBillFactory.cpp"
#include "DepositBillFactory.cpp"
#include "Account.cpp"
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

void AddAccountInFile(Account& account) {
  std::ofstream file;
  file.open("bd_accounts.csv", std::ofstream::app);
  file << std::to_string(account.account_id) << ',' << account.login << ',' << account.password_hash << ',' 
       << account.name << ',' << account.surname << ',' << account.address << ',' << std::to_string(account.passport_num) << "\n";
  file.close();
}



// функции для получения содержимого файла

std::vector<std::vector<std::string>> ReadFileBDBills() {
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

std::vector<std::vector<std::string>> ReadFileBDAccounts() {  // исходный вектор содержит следующий вид: айди аккаунта, логин, пароль, имя, фамилия, адресс, номер паспорта
  std::vector<std::vector<std::string> > vec;
  std::ifstream file("bd_accounts.csv");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str;
    std::vector<std::string> undervec;
    for (int i = 0; i < 7; i++) {
      std::getline(iss, str, ',');
      undervec.push_back(str);
    }
    vec.push_back(undervec);
  }
  return vec;
}

std::vector<std::vector<std::string>> ReadFileBDHistory() {
  std::vector<std::vector<std::string> > vec;
  std::ifstream file("bd_history.csv");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string str;
    std::vector<std::string> undervec;
    for (int i = 0; i < 5; i++) {
      std::getline(iss, str, ',');
      undervec.push_back(str);
    }
    vec.push_back(undervec);
  }
  return vec;
}

// функция для создания аккаунта

void Bank::CreateAccount(std::string login, std::string password, std::string name, std::string surname, std::string address, int passport_num) {
  AccountBuilder account_builder;
  std::hash<std::string> passw_hash; 
  Account account = account_builder.GetAccount(*(this));
  account.account_id = id_for_accounts++;
  account.login = login;
  account.password_hash = std::to_string(passw_hash(password));
  account.name = name;
  account.surname = surname;
  account.address = address;
  account.passport_num = passport_num;
  AddAccountInFile(account);
}



// функция подтверждения входа на сайт

bool Bank::LoginTo(std::string login, std::string password) {
  auto vec = ReadFileBDAccounts();
  std::hash<std::string> hash;
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][1] == login) {
      return std::to_string(hash(password)) == vec[i][2];
    }
  }
  return false;
}



//функция создания счёта

bool Bank::CreateBill(int type_of_bill, int account_id) {
  if (type_of_bill == -1) {
    CreditBill newbill;
    CreditBillFactory creditfactory;
    newbill = creditfactory.CreateCredit();
    AddBillInFile(newbill, account_id);
  } else if (type_of_bill == 0) {
    DebitBill newbill;
    DebitBillFactory debitfactory;
    newbill = debitfactory.CreateDebit();
    AddBillInFile(newbill, account_id);
  } else if (type_of_bill == 1) {
    DepositBill newbill;
    DepositBillFactory depositfactory;
    newbill = depositfactory.CreateDeposit();
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

// функция для добавления операции в историю

void AddOperInHis(std::string account_id, std::string oper_type, std::string bill_from, std::string bill_to, std::string amount_of_money) {
  std::ofstream file;
  file.open("bd_history.csv", std::ofstream::app);
  file << account_id << "," << oper_type << ',' << bill_from << ',' << bill_to << ',' 
       << amount_of_money << "\n";
  file.close();
}

// функция для проверки истории

void Bank::CheckHistory(int account_id) {
  auto vec = ReadFileBDHistory();
  std::cout << "История операций\n";
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][0] == std::to_string(account_id)) {
      std::cout << vec[i][1] << ' ' << vec[i][2] << ' ' << vec[i][3] << ' ' << vec[i][4] << '\n'; 
    }
  }
  std::cout << "Конец\n";
}

// функции для взаимодействия со счетами

void Bank::AddMoney(int account_id, int bill_to, int amount_of_money) {
  auto vec = ReadFileBDBills();
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
  AddOperInHis(std::to_string(account_id), "Add money ", "", "to " + std::to_string(bill_to), "+" + std::to_string(amount_of_money));
  file.close();
}

bool Bank::WithdrawMoney(int account_id, int bill_from, int amount_of_money) {
  auto vec = ReadFileBDBills();
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
  AddOperInHis(std::to_string(account_id), "Withdraw money ", "from " + std::to_string(bill_from), "", "-" + std::to_string(amount_of_money));
  return true;
}

bool Bank::Transaction(int account_id_from, int account_id_to, int bill_from, int bill_to, int amount_of_money) {
  auto vec = ReadFileBDBills();
  for (int i = 0; i < vec.size(); ++i) {
    if (vec[i][1] == std::to_string(bill_from)) {
      if (std::stoi(vec[i][3]) - amount_of_money < 0) {
        return false;
      }
      vec[i][3] = std::to_string(std::stoi(vec[i][3]) - amount_of_money);
    }
  }
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
  AddOperInHis(std::to_string(account_id_from), "Transaction ", "from " + std::to_string(bill_from), "to " + std::to_string(bill_to), "-" + std::to_string(amount_of_money));
  AddOperInHis(std::to_string(account_id_to), "Transaction ", "from " + std::to_string(bill_from), "to " + std::to_string(bill_to), "+" + std::to_string(amount_of_money));
  return true;
}

/*
// тестирование
int main() {
  Bank bank;
  bank.CreateAccount("Paxan", "22848", "Pavel", "Dranov", "Pervomayskaya30k7", 224423); // account_id = 0
  bank.CreateAccount("DimaZ", "43348", "Dima", "Matveev", "Pervomayskaya30k7", 224424); // account_id = 1
  bank.CreateBill(1, 0);  // bill id = 200758
  bank.CreateBill(-1, 1);  // bill id = 200759
  bank.CreateBill(0, 0);  // bill id = 200760
  bank.AddMoney(0, 200758, 1000);
  bank.Transaction(0, 1, 200758, 200759, 300);
  bank.CheckBills(0);
  bank.CheckHistory(0);
  std::cout << bank.LoginTo("Paxan", "22849") << ' ' << bank.LoginTo("Paxan", "22848") << '\n';
}*/