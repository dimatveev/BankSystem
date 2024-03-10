#pragma once
#include <time.h>
struct Bill {
  int money;
  int unique_id;
  int limit_confirmed;
  int limit_uncomfired;
  int lowest_border;
};

struct DebitBill : public Bill{
};

struct CreditBill : public Bill {
  double Comission;
};

struct DepositBill : public Bill {
  double percent;
  time_t data_created;
  time_t period;
};