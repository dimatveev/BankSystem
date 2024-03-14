#include "AbstractFactory.h"
#include "Bill.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

int AbstractFactory::bill_id = 1;
//функции создающие счета
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

CreditBill CreditBillFactory::CreateCredit() {
  CreditBill newbill;
  newbill.money = 0;
  std::cout << "У вас " << newbill.money << "$ на вашем кредитном счете" << std::endl;
  newbill.limit_uncomfired = 0; // по идее его вообще нельзя создать если нет паспорта
  newbill.limit_confirmed = 100000; //можно вывести 100к, дальше пишет что нельзя тк много(можно переписать типо бесконечность)
  newbill.lowest_border = -10000; // даем кредит на 10000 максимум
  // Создание unique_id
  int64_t prefix = 14886957;
  int64_t suffix = bill_id++;
  newbill.unique_id = prefix * 100000000 + suffix;
  std::cout << "Ваш номер счета: " << newbill.unique_id << std::endl;
  newbill.Comission = 0.11;//11 процентов комса по кредиту
  std::cout << "Вам доступен кредит на сумму: " << newbill.limit_confirmed << "$" << std::endl;
  std::cout << "Процентная ставка вашего кредитного счета: " << newbill.Comission * 100 << "%" << std::endl;
  std::cout << std::endl;
  return newbill;
}

DepositBill DepositBillFactory::CreateDeposit() {
  DepositBill newbill;
  newbill.money = 0;
  std::cout << "У вас " << newbill.money << "$ на вашем депозитном счете" << std::endl;
  newbill.limit_uncomfired = 100; // по идее его вообще нельзя создать если нет паспорта
  newbill.limit_confirmed = 10000000; //можно вывести 10мл, дальше пишет что нельзя тк много(можно переписать типо бесконечность)
  newbill.lowest_border = 0;
  // Создание unique_id
  int64_t prefix = 14886957;
  int64_t suffix = bill_id++;
  newbill.unique_id = prefix * 100000000 + suffix;
  // Получаем текущее время в формате "год-месяц-день часы:минуты:секунды"
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(localtime(&in_time_t), "%Y-%m-%d %X");
  newbill.data_created = ss.str();
  // Установка периода действия депозита (например, в днях)
  newbill.period = 365; // Пример: 365 дней
  newbill.percent = 0.09;
  std::cout << "Ваш номер счета: " << newbill.unique_id << std::endl;
  std::cout << "Дата и время создания счета: " << newbill.data_created << std::endl;
  std::cout << "Период действия депозита: " << newbill.period << " дней" << std::endl;
  std::cout << "Процентная ставка по счету: " << newbill.percent * 100 << "%" << std::endl;
  std::cout << std::endl;
  return newbill;
}



int main() {
  DebitBillFactory df;
  CreditBillFactory cf;
  DepositBillFactory dpf;
  df.CreateDebit();
  cf.CreateCredit();
  dpf.CreateDeposit();
 // af.CreateDebit();
 // af.CreateDebit();
}