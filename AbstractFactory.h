#pragma once
#include "Bill.h"

struct AbstractFactory {
  static int bill_id;
};

struct DebitBillFactory : public AbstractFactory {
  DebitBill CreateDebit();
};

struct CreditBillFactory : public AbstractFactory {
  CreditBill CreateCredit();
};

struct DepositBillFactory : public AbstractFactory {
  DepositBill CreateDeposit();
};