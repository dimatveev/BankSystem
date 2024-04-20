#pragma once
#include "Bill.h"
#include "DebitBill.h"
#include "CreditBill.h"
#include "DepositBill.h"

struct AbstractFactory {
  static int bill_id;
};
