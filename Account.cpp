#include "Account.h"

void Account::CreateBill(int type_of_bill) {
  if (!bank.CreateBill(type_of_bill, account_id)) {
    std::cout << "Укажите корректный тип счёта: -1 - кредитный, 0 - дебетовый, 1 - депозитный" << std::endl;
    return;
  }
  if (type_of_bill == -1) {
    std::cout << "Создан кредитный счёт" << std::endl;
  } else if (type_of_bill == 0) {
    std::cout << "Создан дебетовый счёт" << std::endl;
  } else if (type_of_bill == 1) {
    std::cout << "Создан депозитный счёт" << std::endl;
  } else {
    std::cout << "CreateBill error" << std::endl;
  }
}

Account::Account(Bank& mybank) : bank(mybank) {}

void Account::CheckBills() {
  bank.CheckBills(account_id);
}

void Account::CheckHistory() {
  bank.CheckHistory(account_id);
}
/*
void Account::Transaction(int bill_from, int bill_to, int amount_of_money) {
  if (bank.Transaction(bill_from, bill_to, amount_of_money)) {
    std::cout << "Переведено " << amount_of_money << "$ со счёт " << bill_from  << " на счёт " << bill_to << std::endl;
    AddOperInHis("Transaction", "from " + std::to_string(bill_from), "to " + std::to_string(bill_to), std::to_string(amount_of_money));
  } else {
    std::cout << "Недостаточно средств для перевода или ваш счёт подозрительный" << std::endl;
  }
}

void Account::AddMoney(int bill_to, int amount_of_money) {
  bank.AddMoney(bill_to, amount_of_money);
  AddOperInHis("Add money", "-", std::to_string(bill_to), std::to_string(amount_of_money));
  std::cout << "Зачислено " << amount_of_money << "$ на счёт " << bill_to << std::endl;
}

void Account::WithdrawMoney(int bill_from, int amount_of_money) {
  if (bank.WithdrawMoney(bill_from, amount_of_money)) {
    std::cout << "Снято " << amount_of_money << "$ со счёт " << bill_from << std::endl;
    AddOperInHis("Withdraw money", std::to_string(bill_from), "-", std::to_string(amount_of_money));
  } else {
    std::cout << "Недостаточно средств для снятия или ваш счёт подозрительный" << std::endl;
  }
  
}*/