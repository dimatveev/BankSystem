#pragma once
#include <string>
#include "Bill.h"

struct DepositBill : public Bill {
  double percent;
  std::string data_created;
  int period;
};