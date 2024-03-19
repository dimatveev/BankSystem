#include "DebitBillFactory.h"
#include "DebitBill.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

DebitBill DebitBillFactory::CreateDebit() {
  DebitBill newbill;
  newbill.money = 0;
  std::cout << "У вас " << newbill.money << "$ на вашем дебетовом счете" << std::endl;
  newbill.limit_uncomfired = 100; // можно вывести только 10$
  newbill.limit_confirmed = 1000000; //можно вывести 1 миллион, дальше пишет что нельзя тк много(можно переписать типо бесконечность)
  newbill.lowest_border = 0;
  // Создание unique_id
  int64_t prefix = 14886957;
  int64_t suffix = bill_id++;
  newbill.unique_id = prefix * 100000000 + suffix;
  std::cout << "Ваш номер счета: " << newbill.unique_id << std::endl;
  std::cout << std::endl;
  return newbill;
}