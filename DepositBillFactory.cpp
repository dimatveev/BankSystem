#include "DepositBillFactory.h"
#include "DepositBill.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>

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