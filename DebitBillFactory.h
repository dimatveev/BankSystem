#pragma once
#include "DebitBill.h"
#include "AbstractFactory.h"

struct DebitBillFactory : public AbstractFactory {
  DebitBill CreateDebit();
};