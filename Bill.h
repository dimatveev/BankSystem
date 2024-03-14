#pragma once
#include <string>
struct Bill {
  int money;
  int64_t unique_id;
  int limit_confirmed;
  int limit_uncomfired;
  int lowest_border;
  Bill() = default;
};

struct DebitBill : public Bill{
};

struct CreditBill : public Bill {
  double Comission;
};

struct DepositBill : public Bill {
  double percent;
  std::string data_created;
  int period;
};