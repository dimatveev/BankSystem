#include "CreditBillFactory.h"
#include "CreditBill.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

CreditBill CreditBillFactory::CreateCredit() {
  CreditBill newbill;
  newbill.money = 0;
  std::cout << "У вас " << newbill.money << "$ на вашем кредитном счете" << std::endl;
  newbill.limit_uncomfired = 0; // по идее его вообще нельзя создать если нет паспорта
  newbill.limit_confirmed = 100000; //можно вывести 100к, дальше пишет что нельзя тк много(можно переписать типо бесконечность)
  newbill.lowest_border = -10000; // даем кредит на 10000 максимум
  // Создание unique_id
  int64_t prefix = 200757;
  int64_t suffix = bill_id++;
  newbill.unique_id = prefix + suffix;
  std::cout << "Ваш номер счета: " << newbill.unique_id << std::endl;
  newbill.Comission = 0.11;//11 процентов комса по кредиту
  std::cout << "Вам доступен кредит на сумму: " << newbill.limit_confirmed << "$" << std::endl;
  std::cout << "Процентная ставка вашего кредитного счета: " << newbill.Comission * 100 << "%" << std::endl;
  std::cout << std::endl;
  return newbill;
}