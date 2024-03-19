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

/*
int main() {
  DebitBillFactory df;
  CreditBillFactory cf;
  DepositBillFactory dpf;
  df.CreateDebit();
  cf.CreateCredit();
  dpf.CreateDeposit();
 // af.CreateDebit();
 // af.CreateDebit();
}*/