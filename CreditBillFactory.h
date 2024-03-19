#pragma once
#include "CreditBill.h"
#include "AbstractFactory.h"

struct CreditBillFactory : public AbstractFactory {
  CreditBill CreateCredit();
};