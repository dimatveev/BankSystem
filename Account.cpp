#include "Account.h"

enum BillType {credit, debit, deposit};

void Account::CreateBill(BillType type_of_bill) {
  if (!bank.CreateBill(type_of_bill, account_id)) {
    return;
  }
  if (type_of_bill == credit) {
    std::cout << "Создан кредитный счёт" << std::endl;
  } else if (type_of_bill == debit) {
    std::cout << "Создан дебетовый счёт" << std::endl;
  } else if (type_of_bill == deposit) {
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
