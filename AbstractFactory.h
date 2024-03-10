#pragma once
#include <Bill.h>
struct AbstractFactory {
  DebitBill& CreateDebit();
  CreditBill& CreateCredit();
  DepositBill& CreateDeposit();
};

struct DebitBillFactory : public AbstractFactory {
  DebitBill& CreateDebit();
};

struct CreditBillFactory : public AbstractFactory {
  CreditBill& CreateCredit();
};

struct DepositBillFactory : public AbstractFactory {
  DepositBill& CreateDebit();
};