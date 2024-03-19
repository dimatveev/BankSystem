#pragma once
#include "DepositBill.h"
#include "AbstractFactory.h"

struct DepositBillFactory : public AbstractFactory {
  DepositBill CreateDeposit();
};